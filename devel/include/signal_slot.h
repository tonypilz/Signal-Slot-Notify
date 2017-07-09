#pragma once

#include <vector>
#include <algorithm>

namespace sisl {  // signal slot

namespace detail {



//==============types for customization===================

template <typename TInvokable>
struct SlotContainer {
    typedef std::vector<TInvokable> type;
};

template <typename TResult>
struct ResultContainerType {
    typedef std::vector<TResult> type;
};

struct LockingDisabled{
    struct Mutex{};
    struct ScopedLock{ScopedLock(Mutex const&){}};
};


struct ScopedLock{
    typedef LockingDisabled::ScopedLock type;
};

struct Mutex{
    typedef LockingDisabled::Mutex type;
};






//==============struct OutType===================

template <typename R>
struct OutType {

    typedef typename ResultContainerType<R>::type type;

    operator type() const { return out; }

    type out;
};

template <>
struct OutType<void> {};


//==============struct Invokable===================

template <typename R = void, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
struct Invokable;

template <typename R, typename A1, typename A2, typename A3, typename A4>
struct Invokable<R, A1, A2, A3, A4> {
    virtual R operator()(A1, A2, A3, A4) = 0;
    virtual ~Invokable() {}
};

template <typename R, typename A1, typename A2, typename A3>
struct Invokable<R, A1, A2, A3> {
    virtual R operator()(A1, A2, A3) = 0;
    virtual ~Invokable() {}
};

template <typename R, typename A1, typename A2>
struct Invokable<R, A1, A2> {
    virtual R operator()(A1, A2) = 0;
    virtual ~Invokable() {}
};

template <typename R, typename A1>
struct Invokable<R, A1> {
    virtual R operator()(A1) = 0;
    virtual ~Invokable() {}
};

template <typename R>
struct Invokable<R> {
    virtual R operator()() = 0;
    virtual ~Invokable() {}
};



//==============struct MemberFunc===================

static const bool Const = true;
static const bool NotConst = false;

template <typename TObj, bool IsConst, typename R = void, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void>
struct MemberFunc;

template <typename TObj, typename R, typename A1, typename A2, typename A3, typename A4>
struct MemberFunc<TObj, false, R, A1, A2, A3, A4> {
    typedef R (TObj::*type)(A1, A2, A3, A4);
};

template <typename TObj, typename R, typename A1, typename A2, typename A3>
struct MemberFunc<TObj, false, R, A1, A2, A3> {
    typedef R (TObj::*type)(A1, A2, A3);
};

template <typename TObj, typename R, typename A1, typename A2>
struct MemberFunc<TObj, false, R, A1, A2> {
    typedef R (TObj::*type)(A1, A2);
};

template <typename TObj, typename R, typename A1>
struct MemberFunc<TObj, false, R, A1> {
    typedef R (TObj::*type)(A1);
};

template <typename R, typename TObj>
struct MemberFunc<TObj, false, R> {
    typedef R (TObj::*type)();
};

template <typename TObj, typename R, typename A1, typename A2, typename A3, typename A4>
struct MemberFunc<TObj, true, R, A1, A2, A3, A4> {
    typedef R (TObj::*type)(A1, A2, A3, A4) const;
};

template <typename TObj, typename R, typename A1, typename A2, typename A3>
struct MemberFunc<TObj, true, R, A1, A2, A3> {
    typedef R (TObj::*type)(A1, A2, A3) const;
};

template <typename TObj, typename R, typename A1, typename A2>
struct MemberFunc<TObj, true, R, A1, A2> {
    typedef R (TObj::*type)(A1, A2) const;
};

template <typename TObj, typename R, typename A1>
struct MemberFunc<TObj, true, R, A1> {
    typedef R (TObj::*type)(A1) const;
};

template <typename R, typename TObj>
struct MemberFunc<TObj, true, R> {
    typedef R (TObj::*type)() const;
};




//==============struct CallableImpl===================

template <typename R>
struct InvokableImpl {
    static const bool dummy = true;
    typedef R R_;

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, bool Dummy = dummy>
    struct GlobalFunction;

    template <typename A1, typename A2, typename A3, typename A4>
    struct GlobalFunction<A1, A2, A3, A4> : public Invokable<R_, A1, A2, A3, A4> {
        typedef GlobalFunction<A1, A2, A3, A4> Classtype;
        typedef Invokable<R_, A1, A2, A3, A4> Superclass;
        typedef R_ (*Member)(A1, A2, A3, A4);
        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { return m_member(a1, a2, a3, a4); }
        GlobalFunction(Member member) : m_member(member) {}
        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}
    private:
        Member m_member;
    };

    template <typename A1, typename A2, typename A3>
    struct GlobalFunction<A1, A2, A3> : public Invokable<R_, A1, A2, A3> {
        typedef GlobalFunction<A1, A2, A3> Classtype;
        typedef Invokable<R_, A1, A2, A3> Superclass;
        typedef R_ (*Member)(A1, A2, A3);
        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { return m_member(a1, a2, a3); }
        GlobalFunction(Member member) : m_member(member) {}
        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}
    private:
        Member m_member;
    };

    template <typename A1, typename A2>
    struct GlobalFunction<A1, A2> : public Invokable<R_, A1, A2> {
        typedef GlobalFunction<A1, A2> Classtype;
        typedef Invokable<R_, A1, A2> Superclass;
        typedef R_ (*Member)(A1, A2);
        virtual R_ operator()(A1 a1, A2 a2) { return m_member(a1, a2); }
        GlobalFunction(Member member) : m_member(member) {}
        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}
    private:
        Member m_member;
    };

    template <typename A1>
    struct GlobalFunction<A1> : public Invokable<R_, A1> {
        typedef GlobalFunction<A1> Classtype;
        typedef Invokable<R_, A1> Superclass;
        typedef R_ (*Member)(A1);
        virtual R_ operator()(A1 a1) { return m_member(a1); }
        GlobalFunction(Member member) : m_member(member) {}
        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}
    private:
        Member m_member;
    };

    template <bool Dummy>  // must have at least one template parameter to compile!
    struct GlobalFunction<void, void, void, void, void, Dummy> : public Invokable<R_> {
        typedef GlobalFunction<void, void, void, void, void, Dummy> Classtype;
        typedef Invokable<R_> Superclass;
        typedef R_ (*Member)();
        virtual R_ operator()() { return m_member(); }
        GlobalFunction(Member member) : m_member(member) {}
        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}
    private:
        Member m_member;
    };




    //////////////////////////////////////////////////////////
    template <typename TObj, bool IsConst, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
    struct MemberFunction;

    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3, typename A4>
    struct MemberFunction<TObj, IsConst, A1, A2, A3, A4> : public Invokable<R_, A1, A2, A3, A4> {

        typedef MemberFunction<TObj, IsConst, A1, A2, A3, A4> Classtype;
        typedef Invokable<R_, A1, A2, A3, A4> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3, A4>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { return (m_obj.*m_member)(a1, a2, a3, a4); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };


    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3>
    struct MemberFunction<TObj, IsConst, A1, A2, A3> : public Invokable<R_, A1, A2, A3> {

        typedef MemberFunction<TObj, IsConst, A1, A2, A3> Classtype;
        typedef Invokable<R_, A1, A2, A3> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { return (m_obj.*m_member)(a1, a2, a3); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst, typename A1, typename A2>
    struct MemberFunction<TObj, IsConst, A1, A2> : public Invokable<R_, A1, A2> {

        typedef MemberFunction<TObj, IsConst, A1, A2> Classtype;
        typedef Invokable<R_, A1, A2> Superclass;
        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2>::type Member;

        virtual R_ operator()(A1 a1, A2 a2) { return (m_obj.*m_member)(a1, a2); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst, typename A1>
    struct MemberFunction<TObj, IsConst, A1> : public Invokable<R_, A1> {

        typedef MemberFunction<TObj, IsConst, A1> Classtype;
        typedef Invokable<R_, A1> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_, A1>::type Member;

        virtual R_ operator()(A1 a1) { return (m_obj.*m_member)(a1); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst>
    struct MemberFunction<TObj, IsConst> : public Invokable<R_> {

        typedef MemberFunction<TObj, IsConst> Classtype;
        typedef Invokable<R_> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_>::type Member;

        virtual R_ operator()() { return (m_obj.*m_member)(); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };
};
template <>
struct InvokableImpl<void> {

    static const bool dummy = true;
    typedef void R_;

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, bool Dummy = dummy>
    struct GlobalFunction;

    template <typename A1, typename A2, typename A3, typename A4>
    struct GlobalFunction<A1, A2, A3, A4> : public Invokable<R_, A1, A2, A3, A4> {

        typedef GlobalFunction<A1, A2, A3, A4> Classtype;
        typedef Invokable<R_, A1, A2, A3, A4> Superclass;

        typedef R_ (*Member)(A1, A2, A3, A4);

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { m_member(a1, a2, a3, a4); }

        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}

        GlobalFunction(Member member) : m_member(member) {}

    private:
        Member m_member;
    };

    template <typename A1, typename A2, typename A3>
    struct GlobalFunction<A1, A2, A3> : public Invokable<R_, A1, A2, A3> {

        typedef GlobalFunction<A1, A2, A3> Classtype;
        typedef Invokable<R_, A1, A2, A3> Superclass;

        typedef R_ (*Member)(A1, A2, A3);

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { m_member(a1, a2, a3); }

        GlobalFunction(Member member) : m_member(member) {}

        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}

    private:
        Member m_member;
    };
    template <typename A1, typename A2>
    struct GlobalFunction<A1, A2> : public Invokable<R_, A1, A2> {

        typedef GlobalFunction<A1, A2> Classtype;
        typedef Invokable<R_, A1, A2> Superclass;

        typedef R_ (*Member)(A1, A2);

        virtual R_ operator()(A1 a1, A2 a2) { m_member(a1, a2); }

        GlobalFunction(Member member) : m_member(member) {}

        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}

    private:
        Member m_member;

    };

    template <typename A1>
    struct GlobalFunction<A1> : public Invokable<R_, A1> {

        typedef GlobalFunction<A1> Classtype;
        typedef Invokable<R_, A1> Superclass;

        typedef R_ (*Member)(A1);

        virtual R_ operator()(A1 a1) { m_member(a1); }

        GlobalFunction(Member member) : m_member(member) {}

        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}

    private:
        Member m_member;
    };

    template <bool Dummy>  // must have at least one template parameter to compile!
    struct GlobalFunction<void, void, void, void, void, Dummy> : public Invokable<R_> {

        typedef GlobalFunction<void, void, void, void, void, Dummy> Classtype;
        typedef Invokable<R_> Superclass;

        typedef R_ (*Member)();

        virtual R_ operator()() { m_member(); }

        GlobalFunction(Member member) : m_member(member) {}

        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}

    private:
        Member m_member;
    };


    //////////////////////////////////////////////////////////


    template <typename TObj, bool IsConst, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
    struct MemberFunction;

    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3, typename A4>
    struct MemberFunction<TObj, IsConst, A1, A2, A3, A4> : public Invokable<R_, A1, A2, A3, A4> {

        typedef MemberFunction<TObj, IsConst, A1, A2, A3, A4> Classtype;
        typedef Invokable<R_, A1, A2, A3, A4> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3, A4>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { (m_obj.*m_member)(a1, a2, a3, a4); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3>
    struct MemberFunction<TObj, IsConst, A1, A2, A3> : public Invokable<R_, A1, A2, A3> {

        typedef MemberFunction<TObj, IsConst, A1, A2, A3> Classtype;
        typedef Invokable<R_, A1, A2, A3> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { (m_obj.*m_member)(a1, a2, a3); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, bool IsConst, typename A1, typename A2>
    struct MemberFunction<TObj, IsConst, A1, A2> : public Invokable<R_, A1, A2> {

        typedef MemberFunction<TObj, IsConst, A1, A2> Classtype;
        typedef Invokable<R_, A1, A2> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2>::type Member;

        virtual R_ operator()(A1 a1, A2 a2) { (m_obj.*m_member)(a1, a2); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (m_obj == other.m_obj) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, bool IsConst, typename A1>
    struct MemberFunction<TObj, IsConst, A1> : public Invokable<R_, A1> {

        typedef MemberFunction<TObj, IsConst, A1> Classtype;
        typedef Invokable<R_, A1> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_, A1>::type Member;

        virtual R_ operator()(A1 a1) { (m_obj.*m_member)(a1); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, bool IsConst>
    struct MemberFunction<TObj, IsConst> : public Invokable<R_> {

        typedef MemberFunction<TObj, IsConst> Classtype;
        typedef Invokable<R_> Superclass;

        typedef typename MemberFunc<TObj, IsConst, R_>::type Member;

        virtual R_ operator()() { (m_obj.*m_member)(); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };
};


//==============struct OutType===================

template<typename TCaller>
struct IsEqual {

    IsEqual(TCaller const& c):caller(c){}
    TCaller const& caller;

    bool operator()(typename TCaller::Superclass const* other){
        TCaller const* t = dynamic_cast<TCaller const*>(other);
        return t!=NULL ? caller.isEqual(*t) : false;
    }
};



//==============remove impl===================

template<typename Slots, typename TCaller>
void remove(Slots& slots, TCaller const& caller){
    typedef typename Slots::iterator It;

    IsEqual<TCaller> pred(caller);

    Slots toDelete;


    for(It it = slots.begin(), end = slots.end();it!=end;++it)
        if (pred(*it))
            toDelete.push_back(*it);


    slots.erase(std::remove_if(slots.begin(),slots.end(), IsEqual<TCaller>(caller)), slots.end());

    for(It it = toDelete.begin(), end = toDelete.end();it!=end;++it)
        delete *it;
}





//==============struct Collector===================

template<typename OutType_, typename CallResult>
void collectReturnValue(OutType_& c, CallResult const& r) {
    c.out.push_back(r);
}


template <typename R>
struct ReturnValueCollector {

    typedef R R_;

    template <typename A1, typename A2, typename A3, typename A4>
    static void callAndCollect(OutType<R_>& r, Invokable<R_, A1, A2, A3, A4>* c, A1 a1, A2 a2, A3 a3, A4 a4) {
        collectReturnValue(r,c->operator()(a1, a2, a3, a4));
    }

    template <typename A1, typename A2, typename A3>
    static void callAndCollect(OutType<R_>& r, Invokable<R_, A1, A2, A3>* c, A1 a1, A2 a2, A3 a3) {
        collectReturnValue(r,c->operator()(a1, a2, a3));
    }

    template <typename A1, typename A2>
    static void callAndCollect(OutType<R_>& r, Invokable<R_, A1, A2>* c, A1 a1, A2 a2) {
        collectReturnValue(r,c->operator()(a1, a2));
    }

    template <typename A1>
    static void callAndCollect(OutType<R_>& r, Invokable<R_, A1>* c, A1 a1) {
        collectReturnValue(r,c->operator()(a1));
    }

    static void callAndCollect(OutType<R_>& r, Invokable<R_>* c) {
        collectReturnValue(r,c->operator()());
    }
};

template <>
struct ReturnValueCollector<void> {

    typedef void R_;

    template <typename A1, typename A2, typename A3, typename A4>
    static void callAndCollect(OutType<R_>&, Invokable<R_, A1, A2, A3, A4>* c, A1 a1, A2 a2, A3 a3, A4 a4) {
        c->operator()(a1, a2, a3, a4);
    }

    template <typename A1, typename A2, typename A3>
    static void callAndCollect(OutType<R_>&, Invokable<R_, A1, A2, A3>* c, A1 a1, A2 a2, A3 a3) {
        c->operator()(a1, a2, a3);
    }

    template <typename A1, typename A2>
    static void callAndCollect(OutType<R_>&, Invokable<R_, A1, A2>* c, A1 a1, A2 a2) {
        c->operator()(a1, a2);
    }

    template <typename A1>
    static void callAndCollect(OutType<R_>&, Invokable<R_, A1>* c, A1 a1) {
        c->operator()(a1);
    }

    static void callAndCollect(OutType<R_>&, Invokable<R_>* c) {
        c->operator()();
    }
};


} //namespace detail

//==============struct Signal===================

template <typename TFunc>
struct Signal;

template <typename R, typename A1, typename A2, typename A3,typename A4>
struct Signal<R(A1, A2, A3, A4)> {




    void connect(R (*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        slots.push_back(new GCaller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }


    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }

    detail::OutType<R> emit(A1 a1, A2 a2, A3 a3, A4 a4) {
        ScopedLock_ lock(slotsMutex);
        detail::OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            detail::ReturnValueCollector<R>::template callAndCollect<A1, A2, A3, A4>(r, *it, a1, a2, a3, a4);
        return r;
    }

    void disconnect(R (*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        detail::remove(slots,GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
         for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
             delete *it;
         slots.clear();
    }

    ~Signal(){ disconnectAll(); }

   private:

    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1, A2, A3, A4> GCaller;

    template <typename TObj, bool IsConst>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, IsConst, A1, A2, A3, A4> type; };

    typedef detail::Invokable<R, A1, A2, A3, A4> Slot;
    typedef typename detail::SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    Slots slots;
    Mutex_ slotsMutex;
};

template <typename R, typename A1, typename A2, typename A3>
struct Signal<R(A1, A2, A3)> {


    void connect(R (*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        slots.push_back(new GCaller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }


    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }

    detail::OutType<R> emit(A1 a1, A2 a2, A3 a3) {
        ScopedLock_ lock(slotsMutex);
        detail::OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            detail::ReturnValueCollector<R>::template callAndCollect<A1, A2, A3>(r, *it, a1, a2, a3);
        return r;
    }

    void disconnect(R (*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        detail::remove(slots,GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2, A3) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
         for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
             delete *it;
         slots.clear();
    }

    ~Signal(){ disconnectAll(); }

   private:

    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1, A2, A3> GCaller;

    template <typename TObj, bool IsConst>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, IsConst, A1, A2, A3> type; };

    typedef detail::Invokable<R, A1, A2, A3> Slot;
    typedef typename detail::SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    Slots slots;
    Mutex_ slotsMutex;
};


template <typename R, typename A1, typename A2>
struct Signal<R(A1, A2)> {


    void connect(R (*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        slots.push_back(new GCaller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }


    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }

    detail::OutType<R> emit(A1 a1, A2 a2) {
        ScopedLock_ lock(slotsMutex);
        detail::OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            detail::ReturnValueCollector<R>::template callAndCollect<A1, A2>(r, *it, a1, a2);
        return r;
    }

    void disconnect(R (*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        detail::remove(slots,GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
         for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
             delete *it;
         slots.clear();
    }

    ~Signal(){ disconnectAll(); }

   private:

    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1, A2> GCaller;

    template <typename TObj, bool IsConst>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, IsConst, A1, A2> type; };

    typedef detail::Invokable<R, A1, A2> Slot;
    typedef typename detail::SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    Slots slots;
    Mutex_ slotsMutex;
};


template <typename R, typename A1>
struct Signal<R(A1)> {


    void connect(R (*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        slots.push_back(new GCaller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }


    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }

    detail::OutType<R> emit(A1 a1) {
        ScopedLock_ lock(slotsMutex);
        detail::OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            detail::ReturnValueCollector<R>::template callAndCollect<A1>(r, *it, a1);
        return r;
    }

    void disconnect(R (*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        detail::remove(slots,GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
         for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
             delete *it;
         slots.clear();
    }

    ~Signal(){ disconnectAll(); }

   private:

    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1> GCaller;

    template <typename TObj, bool IsConst>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, IsConst, A1> type; };

    typedef detail::Invokable<R, A1> Slot;
    typedef typename detail::SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    Slots slots;
    Mutex_ slotsMutex;
};


template <typename R>
struct Signal<R()> {


    void connect(R (*member)()) {
        ScopedLock_ lock(slotsMutex);
        slots.push_back(new GCaller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)()) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }


    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)() const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        slots.push_back(new MCaller_(obj, member));
    }

    detail::OutType<R> emit() {
        ScopedLock_ lock(slotsMutex);
        detail::OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            detail::ReturnValueCollector<R>::callAndCollect(r, *it);
        return r;
    }

    void disconnect(R (*member)()) {
        ScopedLock_ lock(slotsMutex);
        detail::remove(slots,GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)()) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NotConst>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)() const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::Const>::type MCaller_;
        detail::remove(slots,MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
         for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
             delete *it;
         slots.clear();
    }

    ~Signal(){ disconnectAll(); }

   private:

    static const bool dummy = false;
    typedef typename detail::InvokableImpl<R>::template GlobalFunction<void, void, void, void, void, dummy> GCaller;

    template <typename TObj, bool IsConst>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, IsConst > type; };

    typedef detail::Invokable<R> Slot;
    typedef typename detail::SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    Slots slots;
    Mutex_ slotsMutex;
};






}  // namespace sisl
