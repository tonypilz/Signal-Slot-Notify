#pragma once
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


int main_()
{
    //create instances
    TraficLight tl;
    Pedestrian p;

    //link
    tl.green.connect(p,&Pedestrian::wait);
    tl.red.connect(p,&Pedestrian::walk);

    //begin operation
    tl.switchToRed();
    tl.switchToGreen();

    return 0;
}

