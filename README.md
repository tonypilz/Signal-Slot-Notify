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

# Features
 - Simple to use
 - Single header file only
 - Const-Correct
 - Recursion-Correct
 - Customizable synchronization primitives (mutex/scopedLock)
 - Customizable handling of return values(1) 
 - Tested
 
(1) Currently a std::vector of all return values is returned.
 
# Limitations
 - Currently up to 4 function arguments are supported. If more are required one can use structs or extend the header file to support more. 
 - Default arguments of slots cannot be used. To make use of them separate functions (with and without arguments) must be provided.

# Comparision to Oberserver-Pattern

Employing the observer pattern, the example from the [first paragraph](#signal-slot-notify) would look something like:

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
The following disadvantages compared to Signal/Slots can be found:
 - Stronger coupling than necessary between parent and derived classes due to inheritance (fat interfaces) 
 - Inheritance causes more complex type-hierarchy (readability, changability)
 - Deriving from TraficLight might induce virtual inheritance which has possibly unexpected behaviour eg on ctor-calls (error prone)
 - Deriving from Pedestrian might break Pedestrian::notify() (fragile)
 - A switch statement is (usually) required in the observer class (error prone, readability)
 - Event ids (usually) required which must be in sync between obersver and observed (error prone)
 - Deriving from TraficLight might require management of additional event ids (error prone) 
 - Only one notifyAll() for all situations might not be suitable TraficLight (extra workaround code)
 - Passing arguments requires callbacks to TraficLight which means stronger coupling (readability, changability)
