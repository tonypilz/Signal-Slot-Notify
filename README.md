# Signal-Slot-Notify

This library provides a signal/slot mechanism for (possibly embedded) c++98 applications without requirering other librarys eg like qt or boost. Its simple, without macros, a single header file only and well tested. The following example illustrates the use:

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
- [Signal-Slot-Notify](#units)
  - [Tested on](#tested-on)
  - [Compiles Under](#compiles-under)
- [Contents](#contents)
- [Features](#features)
- [Limitations](#limitations)

# Features
 - Simple to use
 - Single header only
 - Const-Correct
 - Prepared for use with custom synchronization primitives (mutex/scopedLock)
 - Customizable handling of non-void return values (currently a std::vector of all results is returned)
 - Well tested
 
# Limitations
 - Currently up to 4 function arguments are supported. If more are required one can use structs or extend the header file to support more. 
 - Default arguments of slots cannot be used. To make use of them separate functions (with and without arguments) must be used.

