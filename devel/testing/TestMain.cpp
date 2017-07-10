#include "TestMain.h"

#include <include/signal_slot.h>
#include <cassert>

#include <iostream>

namespace sisl {
namespace test {

struct Type {};

typedef volatile int A1;
typedef double A2;
typedef std::string A3;
typedef Type const* A4;
typedef int R;

typedef detail::ReturnValueAggregateContainerType<R>::type RAggr;

class Obj;

namespace state {


int id = -1;
R r;
A1 a1;
A2 a2;
A3 a3;
A4 a4;

Obj const* obj;

const Type someT;

const int id_default = 13;
const int id_default_sqr_pp = id_default*id_default + id_default;
const R r_default = 9999;
const A1 a1_default = -999;
const A2 a2_default = -999.2;
const A3 a3_default = "999";
const A4 a4_default = &someT;


const A1 a1_ndefault = -99;
const A2 a2_ndefault = -99.2;
const A3 a3_ndefault = "99";
const A4 a4_ndefault = NULL;

void reset(){
    obj = NULL;
    id = id_default;
    r = r_default;
    a1 = a1_default;
    a2 = a2_default;
    a3 = a3_default;
    a4 = a4_default;

}

bool isReset(){
    return
            obj == NULL &&
            id == id_default &&
            r == r_default &&
            a1 == a1_default &&
            a2 == a2_default &&
            a3 == a3_default &&
            a4 == a4_default;
}

const int nvoid_id = 772;
const int arg_const_id = 552;
const int static_id = 125;
const int func_const_id = 123456;
}

namespace pureFunctions {

const int offset = 134;


void fun0() {
    state::id += state::id*state::id + offset +  0;
}

void fun1(A1 a1) {
    state::id += state::id*state::id + offset +  1;
    state::a1 = a1;
}

void fun2(A1 a1, A2 a2) {
    state::id += state::id*state::id + offset +  2;
    state::a1 = a1;
    state::a2 = a2;
}

void fun3(A1 a1, A2 a2, A3 a3) {
    state::id += state::id*state::id + offset +  3;
    state::a1 = a1;
    state::a2 = a2;
    state::a3 = a3;
}

void fun4(A1 a1, A2 a2, A3 a3, A4 a4) {
    state::id += state::id*state::id + offset + 4;
    state::a1 = a1;
    state::a2 = a2;
    state::a3 = a3;
    state::a4 = a4;
}

R nvoid_fun0() {
    state::id += state::id*state::id + offset + 0 + state::nvoid_id;
    return state::r;
}

R nvoid_fun1(A1 a1) {
    state::id += state::id*state::id + offset + 1 + state::nvoid_id;
    state::a1 = a1;
    return state::r;
}

R nvoid_fun2(A1 a1, A2 a2) {
    state::id += state::id*state::id + offset + 2 + state::nvoid_id;
    state::a1 = a1;
    state::a2 = a2;
    return state::r;
}

R nvoid_fun2(A1 const& a1, A2 a2) {
    state::id += state::id*state::id + offset + 2 + state::nvoid_id + state::arg_const_id;
    state::a1 = a1;
    state::a2 = a2;
    return state::r;
}

R nvoid_fun3(A1 a1, A2 a2, A3 a3) {
    state::id += state::id*state::id + offset + 3 + state::nvoid_id;
    state::a1 = a1;
    state::a2 = a2;
    state::a3 = a3;
    return state::r;
}

R nvoid_fun4(A1 a1, A2 a2, A3 a3, A4 a4) {
    state::id += state::id*state::id + offset + 4 + state::nvoid_id;
    state::a1 = a1;
    state::a2 = a2;
    state::a3 = a3;
    state::a4 = a4;
    return state::r;
}

} //state




struct Obj {
    static const int offset = 5555;

    static void smember() {
        state::id += state::id*state::id + offset +  state::static_id;
    }

    //nonconst member

    void fun0() {
        state::id += state::id*state::id + offset +  0;
        state::obj = this;
    }

    void fun1(A1 a1) {
        state::id += state::id*state::id + offset +  1;
        state::obj = this;
        state::a1 = a1;
    }

    void fun2(A1 a1, A2 a2) {
        state::id += state::id*state::id + offset +  2;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
    }

    void fun3(A1 a1, A2 a2, A3 a3) {
        state::id += state::id*state::id + offset +  3;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
    }

    void fun4(A1 a1, A2 a2, A3 a3, A4 a4) {
        state::id += state::id*state::id + offset + 4;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
        state::a4 = a4;
    }

    R nvoid_fun0() {
        state::id += state::id*state::id + offset + 0 + state::nvoid_id;
        state::obj = this;
        return state::r;
    }

    R nvoid_fun1(A1 a1) {
        state::id += state::id*state::id + offset + 1 + state::nvoid_id;
        state::obj = this;
        state::a1 = a1;
        return state::r;
    }

    R nvoid_fun2(A1 a1, A2 a2) {
        state::id += state::id*state::id + offset + 2 + state::nvoid_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        return state::r;
    }

    R nvoid_fun2(A1 const& a1, A2 a2) {
        state::id += state::id*state::id + offset + 2 + state::nvoid_id + state::arg_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        return state::r;
    }

    R nvoid_fun3(A1 a1, A2 a2, A3 a3) {
        state::id += state::id*state::id + offset + 3 + state::nvoid_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
        return state::r;
    }

    R nvoid_fun4(A1 a1, A2 a2, A3 a3, A4 a4) {
        state::id += state::id*state::id + offset + 4 + state::nvoid_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
        state::a4 = a4;
        return state::r;
    }

    //const member

    void fun0() const {
        state::id += state::id*state::id + offset +  0 + state::func_const_id;
        state::obj = this;
    }

    void fun1(A1 a1) const {
        state::id += state::id*state::id + offset +  1 + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
    }

    void fun2(A1 a1, A2 a2) const{
        state::id += state::id*state::id + offset +  2 + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
    }

    void fun3(A1 a1, A2 a2, A3 a3) const {
        state::id += state::id*state::id + offset +  3 + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
    }

    void fun4(A1 a1, A2 a2, A3 a3, A4 a4) const {
        state::id += state::id*state::id + offset + 4 + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
        state::a4 = a4;
    }

    R nvoid_fun0() const {
        state::id += state::id*state::id + offset + 0 + state::nvoid_id + state::func_const_id;
        state::obj = this;
        return state::r;
    }

    R nvoid_fun1(A1 a1) const {
        state::id += state::id*state::id + offset + 1 + state::nvoid_id + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        return state::r;
    }

    R nvoid_fun2(A1 a1, A2 a2) const {
        state::id += state::id*state::id + offset + 2 + state::nvoid_id + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        return state::r;
    }

    R nvoid_fun2(A1 const& a1, A2 a2) const {
        state::id += state::id*state::id + offset + 2 + state::nvoid_id + state::arg_const_id + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        return state::r;
    }

    R nvoid_fun3(A1 a1, A2 a2, A3 a3) const {
        state::id += state::id*state::id + offset + 3 + state::nvoid_id + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
        return state::r;
    }

    R nvoid_fun4(A1 a1, A2 a2, A3 a3, A4 a4) const {
        state::id += state::id*state::id + offset + 4 + state::nvoid_id + state::func_const_id;
        state::obj = this;
        state::a1 = a1;
        state::a2 = a2;
        state::a3 = a3;
        state::a4 = a4;
        return state::r;
    }

};

void testInvokableGlobalFunctions_nvoid_overload(){
    {
        const int fid = 2;
        detail::InvokableImpl<R>::GlobalFunction<A1 const&,A2> f(pureFunctions::nvoid_fun2);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid + state::nvoid_id + state::arg_const_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
}

void testInvokableMemberFunctions_nvoid_overload(){
    {
        const int fid = 2;
        Obj obj;
        detail::InvokableImpl<R>::MemberFunction<Obj,detail::NonConst,A1 const&,A2> f(obj,&Obj::nvoid_fun2);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid + state::nvoid_id + state::arg_const_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

}

void testInvokableMemberFunctions_nvoid_const_member_overload(){
    {
        const int fid = 2;
        Obj obj;
        detail::InvokableImpl<R>::MemberFunction<Obj,detail::Const,A1,A2> f(obj,&Obj::nvoid_fun2);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid + state::nvoid_id + state::func_const_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

}

void testInvokableGlobalFunctions_nvoid(){
    {
        const int fid = 4;
        detail::InvokableImpl<R>::GlobalFunction<A1,A2,A3,A4> f(pureFunctions::nvoid_fun4);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault, state::a4_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 == state::a4_ndefault);
    }

    {
        const int fid = 3;
        detail::InvokableImpl<R>::GlobalFunction<A1,A2,A3> f(pureFunctions::nvoid_fun3);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

    {
        const int fid = 2;
        detail::InvokableImpl<R>::GlobalFunction<A1,A2> f(pureFunctions::nvoid_fun2);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

    {
        const int fid = 1;
        detail::InvokableImpl<R>::GlobalFunction<A1> f(pureFunctions::nvoid_fun1);
        state::reset();
        R r = f(state::a1_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

    {
        const int fid = 0;
        detail::InvokableImpl<R>::GlobalFunction<void, void, void, void, void, detail::NonDefault> f(pureFunctions::nvoid_fun0);
        state::reset();
        R r = f();
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 != state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

}
void testInvokableGlobalFunctions_void(){

    {
        const int fid = 4;
        detail::InvokableImpl<void>::GlobalFunction<A1,A2,A3,A4> f(pureFunctions::fun4);
        state::reset();
        f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault, state::a4_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid );
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 == state::a4_ndefault);
    }

    {
        const int fid = 3;
        detail::InvokableImpl<void>::GlobalFunction<A1,A2,A3> f(pureFunctions::fun3);
        state::reset();
        f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid );
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

    {
        const int fid = 2;
        detail::InvokableImpl<void>::GlobalFunction<A1,A2> f(pureFunctions::fun2);
        state::reset();
        f(state::a1_ndefault, state::a2_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid );
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

    {
        const int fid = 1;
        detail::InvokableImpl<void>::GlobalFunction<A1> f(pureFunctions::fun1);
        state::reset();
        f(state::a1_ndefault);
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid );
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }

    {
        const int fid = 0;
        detail::InvokableImpl<void>::GlobalFunction<void, void, void, void, void, detail::NonDefault> f(pureFunctions::fun0);
        state::reset();
        f();
        assert(state::id == state::id_default_sqr_pp + pureFunctions::offset + fid );
        assert(state::a1 != state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
}



void testInvokableMemberFunctions_nvoid(){
    {
        const int fid = 4;
        Obj obj;
        detail::InvokableImpl<R>::MemberFunction<Obj,detail::NonConst,A1,A2,A3,A4> f(obj,&Obj::nvoid_fun4);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault, state::a4_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 == state::a4_ndefault);
    }
    {
        const int fid = 3;
        Obj obj;
        detail::InvokableImpl<R>::MemberFunction<Obj,detail::NonConst,A1,A2,A3> f(obj,&Obj::nvoid_fun3);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
    {
        const int fid = 2;
        Obj obj;
        detail::InvokableImpl<R>::MemberFunction<Obj,detail::NonConst,A1,A2> f(obj,&Obj::nvoid_fun2);
        state::reset();
        R r = f(state::a1_ndefault, state::a2_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
    {
        const int fid = 1;
        Obj obj;
        detail::InvokableImpl<R>::MemberFunction<Obj,detail::NonConst,A1> f(obj,&Obj::nvoid_fun1);
        state::reset();
        R r = f(state::a1_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
    {
        const int fid = 0;
        Obj obj;
        detail::InvokableImpl<R>::MemberFunction<Obj,detail::NonConst> f(obj,&Obj::nvoid_fun0);
        state::reset();
        R r = f();
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid + state::nvoid_id);
        assert(r == state::r_default);
        assert(state::a1 != state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
}
void testInvokableMemberFunctions_void(){

    {
        const int fid = 4;
        Obj obj;
        detail::InvokableImpl<void>::MemberFunction<Obj,detail::NonConst,A1,A2,A3,A4> f(obj,&Obj::fun4);
        state::reset();
        f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault, state::a4_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid);

        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 == state::a4_ndefault);
    }
    {
        const int fid = 3;
        Obj obj;
        detail::InvokableImpl<void>::MemberFunction<Obj,detail::NonConst,A1,A2,A3> f(obj,&Obj::fun3);
        state::reset();
        f(state::a1_ndefault, state::a2_ndefault, state::a3_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid);

        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 == state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
    {
        const int fid = 2;
        Obj obj;
        detail::InvokableImpl<void>::MemberFunction<Obj,detail::NonConst,A1,A2> f(obj,&Obj::fun2);
        state::reset();
        f(state::a1_ndefault, state::a2_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid);

        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 == state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
    {
        const int fid = 1;
        Obj obj;
        detail::InvokableImpl<void>::MemberFunction<Obj,detail::NonConst,A1> f(obj,&Obj::fun1);
        state::reset();
        f(state::a1_ndefault);
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid);

        assert(state::a1 == state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
    {
        const int fid = 0;
        Obj obj;
        detail::InvokableImpl<void>::MemberFunction<Obj,detail::NonConst> f(obj,&Obj::fun0);
        state::reset();
        f();
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid);

        assert(state::a1 != state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
}

void testInvokableStaticMemberFunctions_void(){

    {
        const int fid = 0;
        detail::InvokableImpl<void>::GlobalFunction<void, void, void, void, void, detail::NonDefault> f(Obj::smember);
        state::reset();
        f();
        assert(state::id == state::id_default_sqr_pp + Obj::offset + fid +  state::static_id);

        assert(state::a1 != state::a1_ndefault);
        assert(state::a2 != state::a2_ndefault);
        assert(state::a3 != state::a3_ndefault);
        assert(state::a4 != state::a4_ndefault);
    }
}

void testInvokable(){

    testInvokableGlobalFunctions_nvoid_overload();
    testInvokableGlobalFunctions_nvoid();
    testInvokableGlobalFunctions_void();

    testInvokableMemberFunctions_nvoid_overload();
    testInvokableMemberFunctions_nvoid_const_member_overload();
    testInvokableMemberFunctions_nvoid();
    testInvokableMemberFunctions_void();

    testInvokableStaticMemberFunctions_void();
}

void assertRes(int expectedSize, R expectedVal, RAggr const& aggr){

    assert(expectedSize==(int)aggr.size());

    for(RAggr::const_iterator it = aggr.begin(), end = aggr.end();it!=end;++it)
        assert(*it==expectedVal);

}

struct DObj {
    typedef DObj Superclass;
    static int deletecount;

    DObj(int i):id(i){}

    bool isEqual(DObj const& other)const {return id==other.id;}

    ~DObj(){
        deletecount++;
    }

    int id;
};

int DObj::deletecount = 0;

void testDeleteOnRemove(){

    typedef std::pair<DObj*,bool> P;
    std::vector<P> v;

    v.push_back(P(new DObj(1),false));
    v.push_back(P(new DObj(2),false));

    assert(DObj::deletecount==0);
    assert((int)(v.size())==2);
    assert(v.front().first->id==1);

    const DObj dobj_1(1);
    const DObj dobj_2(2);

    detail::disconnect(v,false, dobj_1);

    assert(DObj::deletecount==1);
    assert((int)(v.size())==1);
    assert(v.front().first->id==2);

    detail::disconnect(v,false, dobj_1);

    assert(DObj::deletecount==1);
    assert((int)(v.size())==1);
    assert(v.front().first->id==2);

    detail::disconnect(v,false, dobj_2);

    assert(DObj::deletecount==2);
    assert((int)(v.size())==0);

    detail::disconnect(v,false, dobj_2);

    assert(DObj::deletecount==2);
    assert((int)(v.size())==0);



}

void testConstCorrectness_nvoid(){

    {
        const int fid = 4;
        Signal<R(A1, A2, A3, A4)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::nvoid_fun4);
        c.connect(cobj, &Obj::nvoid_fun4);

        c.disconnect(obj , &Obj::nvoid_fun4);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault,state::a4_ndefault);
        assertRes(1,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id  + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }

    {
        const int fid = 3;
        Signal<R(A1, A2, A3)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::nvoid_fun3);
        c.connect(cobj, &Obj::nvoid_fun3);

        c.disconnect(obj , &Obj::nvoid_fun3);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault);
        assertRes(1,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id  + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }


    {
        const int fid = 2;
        Signal<R(A1, A2)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::nvoid_fun2);
        c.connect(cobj, &Obj::nvoid_fun2);

        c.disconnect(obj , &Obj::nvoid_fun2);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault,state::a2_ndefault);
        assertRes(1,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id  + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }

    {
        const int fid = 1;
        Signal<R(A1)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::nvoid_fun1);
        c.connect(cobj, &Obj::nvoid_fun1);

        c.disconnect(obj , &Obj::nvoid_fun1);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault);
        assertRes(1,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id  + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }

    {
        const int fid = 0;
        Signal<R()> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::nvoid_fun0);
        c.connect(cobj, &Obj::nvoid_fun0);

        c.disconnect(obj , &Obj::nvoid_fun0);

        state::reset();
        RAggr aggr = c.emit();
        assertRes(1,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id  + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }
}


void testConstCorrectness_void(){

    {
        const int fid = 4;
        Signal<void(A1, A2, A3, A4)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::fun4);
        c.connect(cobj, &Obj::fun4);

        c.disconnect(obj , &Obj::fun4);

        state::reset();
        c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault,state::a4_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }

    {
        const int fid = 3;
        Signal<void(A1, A2, A3)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::fun3);
        c.connect(cobj, &Obj::fun3);

        c.disconnect(obj , &Obj::fun3);

        state::reset();
        c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }


    {
        const int fid = 2;
        Signal<void(A1, A2)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::fun2);
        c.connect(cobj, &Obj::fun2);

        c.disconnect(obj , &Obj::fun2);

        state::reset();
        c.emit(state::a1_ndefault,state::a2_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }

    {
        const int fid = 1;
        Signal<void(A1)> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::fun1);
        c.connect(cobj, &Obj::fun1);

        c.disconnect(obj , &Obj::fun1);

        state::reset();
        c.emit(state::a1_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }

    {
        const int fid = 0;
        Signal<void()> c;

        Obj obj;
        Obj const& cobj(obj);

        c.connect(obj , &Obj::fun0);
        c.connect(cobj, &Obj::fun0);

        c.disconnect(obj , &Obj::fun0);

        state::reset();
        c.emit();


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::func_const_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));
    }
}
void testSignal_remove_double_entry(){

    {

        Signal<void(A1, A2, A3, A4)> c;

        c.connect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);

        c.disconnect(&pureFunctions::fun4);

        state::reset();
        c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault,state::a4_ndefault);

        assert(state::id == state::id_default);

    }
}


void testSignal_correct_call_seq_void(){

    {
        const int fid = 4;
        Signal<void(A1, A2, A3, A4)> c;
        Obj obj;
        c.connect(&pureFunctions::fun4);
        c.connect(obj, &Obj::fun4);
        c.disconnect(&pureFunctions::fun4);
        c.connect(&pureFunctions::fun4);

        state::reset();
        c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault,state::a4_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid ;
        rid +=  rid*rid + pureFunctions::offset + fid ;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }

    {
        const int fid = 3;
        Signal<void(A1, A2, A3)> c;
        Obj obj;
        c.connect(&pureFunctions::fun3);
        c.connect(obj, &Obj::fun3);
        c.disconnect(&pureFunctions::fun3);
        c.connect(&pureFunctions::fun3);

        state::reset();
        c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid ;
        rid +=  rid*rid + pureFunctions::offset + fid ;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }


    {
        const int fid = 2;
        Signal<void(A1, A2)> c;
        Obj obj;
        c.connect(&pureFunctions::fun2);
        c.connect(obj, static_cast<void (Obj::*)(A1,A2) const>(&Obj::fun2));
        c.disconnect(&pureFunctions::fun2);
        c.connect(&pureFunctions::fun2);

        state::reset();
        c.emit(state::a1_ndefault,state::a2_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid   + state::func_const_id;
        rid +=  rid*rid + pureFunctions::offset + fid ;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }
    {
        const int fid = 1;
        Signal<void(A1)> c;
        Obj obj;
        c.connect(&pureFunctions::fun1);
        c.connect(obj, &Obj::fun1);
        c.disconnect(&pureFunctions::fun1);
        c.connect(&pureFunctions::fun1);

        state::reset();
        c.emit(state::a1_ndefault);


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid ;
        rid +=  rid*rid + pureFunctions::offset + fid ;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }
    {
        const int fid = 0;
        Signal<void()> c;
        Obj obj;
        c.connect(&pureFunctions::fun0);
        c.connect(obj, &Obj::fun0);
        c.disconnect(&pureFunctions::fun0);
        c.connect(&pureFunctions::fun0);

        state::reset();
        c.emit();


        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid ;
        rid +=  rid*rid + pureFunctions::offset + fid ;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }

}

void testSignal_correct_call_seq_nvoid(){

    {
        const int fid = 4;
        Signal<R(A1, A2, A3, A4)> c;
        Obj obj;
        c.connect(&pureFunctions::nvoid_fun4);
        c.connect(obj, &Obj::nvoid_fun4);
        c.disconnect(&pureFunctions::nvoid_fun4);
        c.connect(&pureFunctions::nvoid_fun4);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault,state::a4_ndefault);
        assertRes(2,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id;
        rid +=  rid*rid + pureFunctions::offset + fid + state::nvoid_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }

    {
        const int fid = 3;
        Signal<R(A1, A2, A3)> c;
        Obj obj;
        c.connect(&pureFunctions::nvoid_fun3);
        c.connect(obj, &Obj::nvoid_fun3);
        c.disconnect(&pureFunctions::nvoid_fun3);
        c.connect(&pureFunctions::nvoid_fun3);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault,state::a2_ndefault,state::a3_ndefault);
        assertRes(2,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id;
        rid +=  rid*rid + pureFunctions::offset + fid + state::nvoid_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }


    {
        const int fid = 2;
        Signal<R(A1, A2)> c;
        Obj obj;
        c.connect(&pureFunctions::nvoid_fun2);
        c.connect(obj, static_cast<R (Obj::*)(A1,A2) const>(&Obj::nvoid_fun2));
        c.disconnect(&pureFunctions::nvoid_fun2);
        c.connect(&pureFunctions::nvoid_fun2);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault,state::a2_ndefault);
        assertRes(2,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id  + state::func_const_id;
        rid +=  rid*rid + pureFunctions::offset + fid + state::nvoid_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }
    {
        const int fid = 1;
        Signal<R(A1)> c;
        Obj obj;
        c.connect(&pureFunctions::nvoid_fun1);
        c.connect(obj, &Obj::nvoid_fun1);
        c.disconnect(&pureFunctions::nvoid_fun1);
        c.connect(&pureFunctions::nvoid_fun1);

        state::reset();
        RAggr aggr = c.emit(state::a1_ndefault);
        assertRes(2,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id;
        rid +=  rid*rid + pureFunctions::offset + fid + state::nvoid_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }
    {
        const int fid = 0;
        Signal<R()> c;
        Obj obj;
        c.connect(&pureFunctions::nvoid_fun0);
        c.connect(obj, &Obj::nvoid_fun0);
        c.disconnect(&pureFunctions::nvoid_fun0);
        c.connect(&pureFunctions::nvoid_fun0);

        state::reset();
        RAggr aggr = c.emit();
        assertRes(2,state::r_default,aggr);

        int rid = state::id_default;
        rid += rid*rid + Obj::offset + fid + state::nvoid_id;
        rid +=  rid*rid + pureFunctions::offset + fid + state::nvoid_id;

        assert(state::id == rid);
        assert(state::obj == (&obj));

    }

}

void incrementReference(int& intRef){ ++intRef;}
void incrementReference(int& intRef1, std::string& sref1){ ++intRef1; sref1.append("s");}
void incrementReference(int& intRef1, std::string& sref1, int& intRef2){ ++intRef1; sref1.append("s"); ++intRef2; }
void incrementReference(int& intRef1, std::string& sref1, int& intRef2, std::string& sref2){ ++intRef1; sref1.append("s"); ++intRef2; sref2.append("t");}

int nvoid_incrementReference(int& intRef){ ++intRef;}
int nvoid_incrementReference(int& intRef1, std::string& sref1){ ++intRef1; sref1.append("s");}
int nvoid_incrementReference(int& intRef1, std::string& sref1, int& intRef2){ ++intRef1; sref1.append("s"); ++intRef2; }
int nvoid_incrementReference(int& intRef1, std::string& sref1, int& intRef2, std::string& sref2){ ++intRef1; sref1.append("s"); ++intRef2; sref2.append("t");}

void testSignal_refrence_test_nvoid(){

    {
        Signal<int(int&,std::string&,int&,std::string&)> c;
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);

        int i1 = 7;
        int i2 = 17;
        std::string s1("x");
        std::string s2("y");

        c.emit(i1,s1,i2,s2);

        assert(i1==10);
        assert(s1=="xsss");
        assert(i2==20);
        assert(s2=="yttt");
    }
    {
        Signal<int(int&,std::string&,int&)> c;
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);

        int i1 = 7;
        int i2 = 17;
        std::string s1("x");


        c.emit(i1,s1,i2);

        assert(i1==10);
        assert(s1=="xsss");
        assert(i2==20);
    }

    {
        Signal<int(int&,std::string&)> c;
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);

        int i1 = 7;
        std::string s1("x");

        c.emit(i1,s1);

        assert(i1==10);
        assert(s1=="xsss");
    }

    {
        Signal<int(int&)> c;
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);
        c.connect(&nvoid_incrementReference);

        int i1 = 7;

        c.emit(i1);

        assert(i1==10);
    }


}

void testSignal_refrence_test_void(){

    {
        Signal<void(int&,std::string&,int&,std::string&)> c;
        c.connect(&incrementReference);
        c.connect(&incrementReference);
        c.connect(&incrementReference);

        int i1 = 7;
        int i2 = 17;
        std::string s1("x");
        std::string s2("y");

        c.emit(i1,s1,i2,s2);

        assert(i1==10);
        assert(s1=="xsss");
        assert(i2==20);
        assert(s2=="yttt");
    }
    {
        Signal<void(int&,std::string&,int&)> c;
        c.connect(&incrementReference);
        c.connect(&incrementReference);
        c.connect(&incrementReference);

        int i1 = 7;
        int i2 = 17;
        std::string s1("x");


        c.emit(i1,s1,i2);

        assert(i1==10);
        assert(s1=="xsss");
        assert(i2==20);
    }

    {
        Signal<void(int&,std::string&)> c;
        c.connect(&incrementReference);
        c.connect(&incrementReference);
        c.connect(&incrementReference);

        int i1 = 7;
        std::string s1("x");

        c.emit(i1,s1);

        assert(i1==10);
        assert(s1=="xsss");
    }

    {
        Signal<void(int&)> c;
        c.connect(&incrementReference);
        c.connect(&incrementReference);
        c.connect(&incrementReference);

        int i1 = 7;

        c.emit(i1);

        assert(i1==10);
    }


}


template<typename R>
struct RObj4 {


    Signal<R(A1,A2,A3,A4)> s;

    typedef RObj4<R> Classtype;

    typedef typename detail::MemberFunc<Classtype, detail::NonConst, R, A1,A2,A3,A4>::type Func;

    Func member;

    int connectCalled = 0;
    int disconnectCalled = 0;
    int callingCalled = 0;

    R connectMember(A1,A2,A3,A4) {
        ++connectCalled;
        s.connect(*this, &Classtype::callingMember);
    }


    R disconnectMember(A1,A2,A3,A4) {
        ++disconnectCalled;
        s.disconnect(*this, &Classtype::callingMember);
    }

    R callingMember(A1 a1,A2 a2,A3 a3 ,A4 a4) {
        ++callingCalled;
        Classtype& c(*this);
        (c.*member)(a1, a2, a3, a4);
    }

    R emit(A1 a1,A2 a2,A3 a3 ,A4 a4) {
        s.emit(a1,a2,a3,a4);
    }

};

template<typename R>
struct RObj3 {


    Signal<R(A1,A2,A3)> s;

    typedef RObj3<R> Classtype;

    typedef typename detail::MemberFunc<Classtype, detail::NonConst, R, A1,A2,A3>::type Func;

    Func member;

    int connectCalled = 0;
    int disconnectCalled = 0;
    int callingCalled = 0;

    R connectMember(A1,A2,A3) {
        ++connectCalled;
        s.connect(*this, &Classtype::callingMember);
    }


    R disconnectMember(A1,A2,A3) {
        ++disconnectCalled;
        s.disconnect(*this, &Classtype::callingMember);
    }

    R callingMember(A1 a1,A2 a2,A3 a3) {
        ++callingCalled;
        Classtype& c(*this);
        (c.*member)(a1, a2, a3);
    }

    R emit(A1 a1,A2 a2,A3 a3) {
        s.emit(a1,a2,a3);
    }

};

template<typename R>
struct RObj2 {


    Signal<R(A1,A2)> s;

    typedef RObj2<R> Classtype;

    typedef typename detail::MemberFunc<Classtype, detail::NonConst, R, A1,A2>::type Func;

    Func member;

    int connectCalled = 0;
    int disconnectCalled = 0;
    int callingCalled = 0;

    R connectMember(A1,A2) {
        ++connectCalled;
        s.connect(*this, &Classtype::callingMember);
    }


    R disconnectMember(A1,A2) {
        ++disconnectCalled;
        s.disconnect(*this, &Classtype::callingMember);
    }

    R callingMember(A1 a1,A2 a2) {
        ++callingCalled;
        Classtype& c(*this);
        (c.*member)(a1, a2);
    }

    R emit(A1 a1,A2 a2) {
        s.emit(a1,a2);
    }

};

template<typename R>
struct RObj1 {


    Signal<R(A1)> s;

    typedef RObj1<R> Classtype;

    typedef typename detail::MemberFunc<Classtype, detail::NonConst, R, A1>::type Func;

    Func member;

    int connectCalled = 0;
    int disconnectCalled = 0;
    int callingCalled = 0;

    R connectMember(A1) {
        ++connectCalled;
        s.connect(*this, &Classtype::callingMember);
    }


    R disconnectMember(A1) {
        ++disconnectCalled;
        s.disconnect(*this, &Classtype::callingMember);
    }

    R callingMember(A1 a1) {
        ++callingCalled;
        Classtype& c(*this);
        (c.*member)(a1);
    }

    R emit(A1 a1) {
        s.emit(a1);
    }

};

template<typename R>
struct RObj0 {


    Signal<R()> s;

    typedef RObj0<R> Classtype;

    typedef typename detail::MemberFunc<Classtype, detail::NonConst, R>::type Func;

    Func member;

    int connectCalled = 0;
    int disconnectCalled = 0;
    int callingCalled = 0;

    R connectMember() {
        ++connectCalled;
        s.connect(*this, &Classtype::callingMember);
    }


    R disconnectMember() {
        ++disconnectCalled;
        s.disconnect(*this, &Classtype::callingMember);
    }

    R callingMember() {
        ++callingCalled;
        Classtype& c(*this);
        (c.*member)();
    }

    R emit() {
        s.emit();
    }

};

template<typename R>
void testSignal_recursive_behaviour_connect(){


    {
        typedef RObj4<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::connectMember;
        obj.s.emit(state::a1_default,state::a2_default,state::a3_default,state::a4_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 1);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default,state::a2_default,state::a3_default,state::a4_default);

        assert(obj.callingCalled == 3);
        assert(obj.connectCalled == 3);
        assert(obj.disconnectCalled == 0);
    }

    {
        typedef RObj3<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::connectMember;
        obj.s.emit(state::a1_default,state::a2_default,state::a3_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 1);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default,state::a2_default,state::a3_default);

        assert(obj.callingCalled == 3);
        assert(obj.connectCalled == 3);
        assert(obj.disconnectCalled == 0);
    }

    {
        typedef RObj2<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::connectMember;
        obj.s.emit(state::a1_default,state::a2_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 1);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default,state::a2_default);

        assert(obj.callingCalled == 3);
        assert(obj.connectCalled == 3);
        assert(obj.disconnectCalled == 0);
    }

    {
        typedef RObj1<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::connectMember;
        obj.s.emit(state::a1_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 1);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default);

        assert(obj.callingCalled == 3);
        assert(obj.connectCalled == 3);
        assert(obj.disconnectCalled == 0);
    }

    {
        typedef RObj0<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::connectMember;
        obj.s.emit();

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 1);
        assert(obj.disconnectCalled == 0);

        obj.s.emit();

        assert(obj.callingCalled == 3);
        assert(obj.connectCalled == 3);
        assert(obj.disconnectCalled == 0);
    }
}

template<typename R>
void testSignal_recursive_behaviour_disconnect(){

    {
        typedef RObj4<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::disconnectMember;
        obj.s.emit(state::a1_default,state::a2_default,state::a3_default,state::a4_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);

        obj.s.emit(state::a1_default,state::a2_default,state::a3_default,state::a4_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);
    }

    {
        typedef RObj3<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::disconnectMember;
        obj.s.emit(state::a1_default,state::a2_default,state::a3_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);

        obj.s.emit(state::a1_default,state::a2_default,state::a3_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);
    }

    {
        typedef RObj2<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::disconnectMember;
        obj.s.emit(state::a1_default,state::a2_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);

        obj.s.emit(state::a1_default,state::a2_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);
    }

    {
        typedef RObj1<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::disconnectMember;
        obj.s.emit(state::a1_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);

        obj.s.emit(state::a1_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);
    }

    {
        typedef RObj0<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::disconnectMember;
        obj.s.emit();

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);

        obj.s.emit();

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 1);
    }
}

template<typename R>
void testSignal_recursive_behaviour_emit(){

    {
        typedef RObj4<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::emit;
        obj.s.emit(state::a1_default,state::a2_default,state::a3_default,state::a4_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default,state::a2_default,state::a3_default,state::a4_default);

        assert(obj.callingCalled == 2);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);
    }
    {
        typedef RObj3<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::emit;
        obj.s.emit(state::a1_default,state::a2_default,state::a3_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default,state::a2_default,state::a3_default);

        assert(obj.callingCalled == 2);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);
    }

    {
        typedef RObj2<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::emit;
        obj.s.emit(state::a1_default,state::a2_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default,state::a2_default);

        assert(obj.callingCalled == 2);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);
    }

    {
        typedef RObj1<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::emit;
        obj.s.emit(state::a1_default);

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);

        obj.s.emit(state::a1_default);

        assert(obj.callingCalled == 2);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);
    }

    {
        typedef RObj0<R> Obj;
        Obj obj;
        obj.s.connect(obj, &Obj::callingMember);
        obj.member = &Obj::emit;
        obj.s.emit();

        assert(obj.callingCalled == 1);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);

        obj.s.emit();

        assert(obj.callingCalled == 2);
        assert(obj.connectCalled == 0);
        assert(obj.disconnectCalled == 0);
    }

}
void testSignal(){

    testSignal_recursive_behaviour_connect<int>();
    testSignal_recursive_behaviour_connect<void>();

    testSignal_recursive_behaviour_disconnect<int>();
    testSignal_recursive_behaviour_disconnect<void>();

    testSignal_recursive_behaviour_emit<int>();
    testSignal_recursive_behaviour_emit<void>();

    testSignal_refrence_test_void();
    testSignal_refrence_test_nvoid();

    testSignal_correct_call_seq_void();
    testSignal_correct_call_seq_nvoid();
    testSignal_remove_double_entry();
}



TestMain::TestMain() {


    testInvokable();
    testSignal();
    testDeleteOnRemove();
    testConstCorrectness_nvoid();
    testConstCorrectness_void();

    std::cout << "test finished" << std::endl;

    //manual: check scoped lock count (=40)
    //        check test pass with std::list
}



} // namespace test
} // namespace sisl

