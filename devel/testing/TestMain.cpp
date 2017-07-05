#include "TestMain.h"

#include <include/signal_slot.h>

#include <iostream>

namespace sisl {
namespace test {

struct Type {};

typedef int A1;
typedef double A2;
typedef std::string A3;
typedef Type* A4;
typedef int R;

R r = 9999;

namespace globf {

int id = -1;

void fun0() {
    id += 0;
}

void fun1(A1 a1) {
    id += 2;
}

void fun2(A1 a1, A2 a2) {
    id += 4;
}

void fun3(A1 a1, A2 a2, A3 a3) {
    id += 6;
}

void fun4(A1 a1, A2 a2, A3 a3, A4 a4) {
    id += 8;
}

R nvoid_fun0() {
    id += 10;
    return r;
}

R nvoid_fun1(A1 a1) {
    id += 12;
    return r;
}

R nvoid_fun2(A1 a1, A2 a2) {
    id += 14;
    return r;
}

R nvoid_fun2(A1 const& a1, A2 a2) {
    id += 14;
    return r;
}

R nvoid_fun3(A1 a1, A2 a2, A3 a3) {
    id += 16;
    return r;
}

R nvoid_fun4(A1 a1, A2 a2, A3 a3, A4 a4) {
    id += 18;
    return r;
}
}

namespace gobj {
int id = -1;
}

struct Obj {
    int id = -1;

    static void smember0() { gobj::id = -55; }

    void member0() { id = 0; }

    void member0c() const { gobj::id = 1; }

    void member1(A1 a1) { id = 2; }

    void member1c(A1 a1) const { gobj::id = 3; }

    void member2(A1 a1, A2 a2) { id = 4; }

    void member2c(A1 a1, A2 a2) const { gobj::id = 5; }

    void member3(A1 a1, A2 a2, A3 a3) { id = 6; }

    void member3c(A1 a1, A2 a2, A3 a3) const { gobj::id = 7; }

    void member4(A1 a1, A2 a2, A3 a3, A4 a4) { id = 8; }

    void member4c(A1 a1, A2 a2, A3 a3, A4 a4) const { gobj::id = 9; }

    R nvoid_member0() {
        id = 10;
        return r;
    }

    R nvoid_member0c() const {
        gobj::id = 11;
        return r;
    }

    R nvoid_member1(A1 a1) {
        id = 12;
        return r;
    }

    R nvoid_member1c(A1 a1) const {
        gobj::id = 13;
        return r;
    }

    R nvoid_member2(A1 const& a1, A2 a2) {
        id = 14;
        return r;
    }

    R nvoid_member2(A1 a1, A2 a2) {
        id = 14;
        return r;
    }

    R nvoid_member2c(A1 const& a1, A2 a2) const {
        gobj::id = 15;
        return r;
    }

    R nvoid_member2c(A1 a1, A2 a2) const {
        gobj::id = 15;
        return r;
    }

    R nvoid_member3(A1 a1, A2 a2, A3 a3) {
        id = 16;
        return r;
    }

    R nvoid_member3c(A1 a1, A2 a2, A3 a3) const {
        gobj::id = 17;
        return r;
    }

    R nvoid_member4(A1 a1, A2 a2, A3 a3, A4 a4) {
        id = 18;
        return r;
    }

    R nvoid_member4c(A1 a1, A2 a2, A3 a3, A4 a4) const {
        gobj::id = 19;
        return r;
    }
};

TestMain::TestMain() {
    using namespace test;

    using namespace sisl;

    // const args, ref args, volatile args, const ptr

    {
        Signal<R, A1, A2, A3, A4> c;

        Obj obj;

        c.connect(obj, &Obj::nvoid_member4);

        c.connect(obj, &Obj::nvoid_member4c);

        c.connect(&globf::nvoid_fun4);

        std::vector<int> res = c.emit(2, 3.5, "hello", NULL);
    }

    {
        Signal<R, A1, A2, A3> c;

        Obj obj;

        c.connect(obj, &Obj::nvoid_member3);

        c.connect(obj, &Obj::nvoid_member3c);

        c.connect(&globf::nvoid_fun3);

        std::vector<int> res = c.emit(2, 3.5, "hhh");
    }

    {
        Signal<R, A1, A2> c;

        Obj obj;

        c.connect(obj, &Obj::nvoid_member2);

        c.connect(obj, &Obj::nvoid_member2c);

        c.connect(&globf::nvoid_fun2);

        std::vector<int> res = c.emit(2, 3.5);
    }

    {
        Signal<R, A1> c;

        Obj obj;

        c.connect(obj, &Obj::nvoid_member1);

        c.connect(obj, &Obj::nvoid_member1c);

        c.connect(&globf::nvoid_fun1);

        std::vector<int> res = c.emit(2);
    }

    {
        Signal<R> c;

        Obj obj;

        c.connect(obj, &Obj::nvoid_member0);

        c.connect(obj, &Obj::nvoid_member0c);

        c.connect(&globf::nvoid_fun0);

        std::vector<int> res = c.emit();
    }

    /////////////////////////

    {
        Signal<void, A1, A2, A3, A4> c;

        Obj obj;

        c.connect(obj, &Obj::member4);

        c.connect(obj, &Obj::member4c);

        c.connect(&globf::fun4);

        c.emit(2, 3.5, "hello", NULL);
    }

    {
        Signal<void, A1, A2, A3> c;

        Obj obj;

        c.connect(obj, &Obj::member3);

        c.connect(obj, &Obj::member3c);

        c.connect(&globf::fun3);

        c.emit(2, 3.5, "hhh");
    }

    {
        Signal<void, A1, A2> c;

        Obj obj;

        c.connect(obj, &Obj::member2);

        c.connect(obj, &Obj::member2c);

        c.connect(&globf::fun2);

        c.emit(2, 3.5);
    }

    {
        Signal<void, A1> c;

        Obj obj;

        c.connect(obj, &Obj::member1);

        c.connect(obj, &Obj::member1c);

        c.connect(&globf::fun1);

        c.emit(2);
    }

    {
        Signal<void> c;

        Obj obj;

        c.connect(obj, &Obj::member0);

        c.connect(obj, &Obj::member0c);

        c.connect(&globf::fun0);

        c.emit();
    }

    /////////////////////////

    {
        Signal<R, const A1, A2> c;

        Obj obj;

        c.connect(obj, &Obj::nvoid_member2);

        c.connect(obj, &Obj::nvoid_member2c);

        c.connect(&globf::nvoid_fun2);

        std::vector<int> res = c.emit(2, 3.5);
    }

    {
        Signal<R, const A1&, A2> c;

        Obj obj;

        c.connect(obj, &Obj::nvoid_member2);

        c.connect(obj, &Obj::nvoid_member2c);

        c.connect(&globf::nvoid_fun2);

        std::vector<int> res = c.emit(2, 3.5);
    }

    {
        Signal<void> c;

        c.connect(&Obj::smember0);

        c.emit();
    }

    std::cout << "test finished" << std::endl;


}



}
}

