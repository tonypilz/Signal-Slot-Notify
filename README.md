# Signal-Slot-Notify

This library provides a signal/slot mechanism for (possibly embedded) c++98 applications without depending on any other library like qt or boost. Its simple, without macros, single header filed and tested. The following example illustrates the use:

```cpp
#include <include/signal_slot.h>
#include <iostream>
using namespace sisl;

struct TraficLight{

    Signal<void()> green;
    Signal<void()> red;

    void switchToGreen(){
        std::cout<<"===switching to green===\n";
        green.emit();
    }
    void switchToRed(){
        std::cout<<"===switching to red===\n";
        red.emit();
    }
};

struct Pedestrian{
    void walk(){std::cout<<"Pedestrian walk\n";}
    void wait(){std::cout<<"Pedestrian wait\n";}
};

int main()
{
    //create instances
    TraficLight l;
    Pedestrian p;

    //link
    l.green.connect(p,&Pedestrian::wait);
    l.red.connect(p,&Pedestrian::walk);

    //begin operation
    l.switchToRed();
    l.switchToGreen();
}
```
The output would be
```
===switching to red===
Pedestrian walk
===switching to green===
Pedestrian wait
```

The example can be played with on [ideone](http://ideone.com/2ooa64).

## Tested on
 - gcc-5.3.0

## Compiles Under
 - icc-13, icc-16, icc-17
 - gcc-7.1 .. gcc-4.4
 - clang 4.0 .. clang 3.4
 
# Contents
- [Signal-Slot-Notify](#signal-slot-notify)
  - [Tested on](#tested-on)
  - [Compiles Under](#compiles-under)
- [Contents](#contents)
- [Features](#features)
- [Limitations](#limitations)
- [Comparison to Oberserver-Pattern](#comparison-to-oberserver-pattern)
- [Notes for embedded use](#notes-for-embedded-use)

# Features
 - Simple to use
 - Single header file only
 - Const-Correct
 - Recursion-Correct
 - Customizable synchronization (mutex/scopedLock)
 - Customizable handling of return values(1) 
 - Tested
 
(1) Currently a std::vector of all returned values is returned.
 
# Limitations
 - Currently up to 4 function arguments are supported. If more are required one can use structs or extend the header file to support more. 
 - Default function-arguments of slots cannot be used so separate functions (with and without arguments) must be provided.

# Comparison to Oberserver-Pattern

Using the observer pattern, the example from the [first paragraph](#signal-slot-notify) might look like this:

```cpp
#include <include/signal_slot.h>
#include <iostream>
using namespace sisl;

struct TraficLight : public Observable{

    void switchToGreen(){
        std::cout<<"===switching to green===\n";
        notifyAll(1);
    }
    void switchToRed(){
        std::cout<<"===switching to red===\n";
        notifyAll(2);
    }
};

struct Pedestrian : public Observer{

    virtual void notify(int event){
        switch(event) {
        case 1: walk(); return;
        case 2: wait(); return;
        default: break;
        }
    }
    void walk(){std::cout<<"Pedestrian walk\n";}
    void wait(){std::cout<<"Pedestrian wait\n";}
};

int main()
{
    //create instances
    TraficLight tl;
    Pedestrian p;

    //link
    tl.registerObserver(&p);

    //begin operation
    tl.switchToRed();
    tl.switchToGreen();

    return 0;
}
```
This approach contains the following disadvantages compared to the Signal/Slots:


## Event-IDs

If an observer is notified by different observables some form of sender-id must (1) be transfered which is evaluated by the observer in a swich-like statement to identify the observable instance. This form of control flow is error prone, harder to read and maintain and doesnt scale well.

(1) Other mechanisms exists, but they are usually worse.

## Fat Interfaces

Since the notifyAll()-method is beeing used for all notifications it must transmit maximum amount of information an observer could possibly need which is why it provides too much information for average observer. An example would be the event-id which is only used by observers which are observing multiple observables. 

## Complexer Type Hierachy

Observable and observerd must inherit from base-classes. Therefore the type hierarchy is more complex than necessary. 

## Virtual Inheritance

A typical project has usually quite a couple of obervable classes. Therefore chances are that they will inherit from each other producing virtual inheritance, which is considered harmeful. 

## Data transfer via callback 

If data is to be transfered during a notification it must be transfered via a callback mechanism. This induces a more complex control flow, induces stronger coupling between observable and observed class and also introduces additional state which must be taken special care of eg in multithreading environments. Efficiancy also suffers.

## Fragile
 
If an observer derives from another observer it will break the other observers observation if it forgets to call the other observers notify()-method. This is also true if the observer uses (by accident) event-ids used by the other observer.


# Notes for embedded use

By default the operator new/delete is invoked on:
 1. calls to connect(),
 2. calls to disconnect(),
 3. calls to emit(), iff the function signature has a non-void return value and return value aggreation in a container (=default) is used 
 
 Invoking new/delete can be avoided if non-allocating / non-deallocating container-types are used (eg stack buffers).
