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
 - Customizable synchronization primitives (mutex/scopedLock)
 - Customizable handling of return values(1) 
 - Tested
 
(1) Currently a std::vector of all returned values is returned.
 
# Limitations
 - Currently up to 4 function arguments are supported. If more are required one can use structs or extend the header file to support more. 
 - Default arguments of slots cannot be used. To make use of them separate functions (with and without arguments) must be used.

# Comparison to Oberserver-Pattern

After employing the observer pattern, the example from the [first paragraph](#signal-slot-notify) might look like this:

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
This approach contains the following disadvantages compared to the Signal/Slots

## Fat Interfaces

Since the notifyAll()-method and therefore the notify()-method must be used for all kinds of notifications they are very likely to provide the maximum amount of information on all notification paths and therefore become fat. An typical example would be to provide if a bool to indicate if some state of the notifier has changed. And since not everyone is interested in the interface is to wide. Also the event-id information is sometimes not necessary and therefore widens also the interface.

## Complexer Type Hierachy

Since observee and observerd must inherit from other classes the type hierarchy is more complex than in the signal slot mechanism. This impairs readability, refacorizablity and also the amount of documentation. 

## Virtual Inheritance

Since a typical project has quite some the obervable classes, chances are that those observable classes will also inherit from each other producing virtual inheritance, which is considered not ideal (see eg. ctor call sequence). 

## Event-IDs

If an observer is notified by different observables some form of id is usually (1) transfered to identify the caller. This id must then be evaluated by the observer in a switch-like statement. This form of control flow is error prone, harder to read and harder to maintain then just calling different slots.

(1) Other mechanisms exists, but they are even harder to read and maintain.

## Data transfer via callback 

If arguments are to be transfered during a notification they must be transfered via callback. This induces a more complex control flow, requires stronger coupling between observable and observed and also introduces additional state which must be taken special care of in eg multithreading environments. Efficiancy might also suffer.

## Fragile on inheritance
 
Deriving from an observing class and extending the notification-behaviour might break the parents notification behavior. So extra care must be exerted in this kind of situations (also with respect to event-ids) which makes the obsever-pattern more fragile in this respect.


# Notes for embedded use

The operator new/delete is used in the following situations:
 1. calls to connect()
 2. calls to disconnect()
 3. calls to emit(), if the function signature has a non-void return value and return value aggreation in a container (=default) is used 
 
 The calls can be avoided if non-allocating / non-deallocating container-types are used (eg stack buffers).
