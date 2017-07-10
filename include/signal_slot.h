#pragma once

#include <vector> //for containers
#include <algorithm> //for remove_if
#include <utility>  //for pair
#include <cassert>

namespace sisl {  // signal slot

namespace detail {



//==============types for customization===================

template <typename TInvokable>
struct SlotContainer {
    typedef std::vector<TInvokable> type;
};

template <typename TResult>
struct ReturnValueAggregateContainerType {
    typedef std::vector<TResult> type;
};

/**
 * @brief The LockingDisabled struct is a locking implementation
 * which does nothing which is the default synchronization behaviour.
 */
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






/**
 * @brief Instances of this struct represent the aggregated return values
 */
template <typename R>
struct ReturnValueAggregate {

    typedef typename ReturnValueAggregateContainerType<R>::type type;

    operator type() const { return out; }

    type out;
};

template <>
struct ReturnValueAggregate<void> {};



/**
 * @brief This interface represents an abstract call.
 */

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

struct Const{};
struct NonConst{};



/**
 * @brief This helper class defines the type of a member function specialized for const / non-const.
 */
template <typename TObj, typename Constness, typename R = void, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void>
struct MemberFunc;

template <typename TObj, typename R, typename A1, typename A2, typename A3, typename A4>
struct MemberFunc<TObj, NonConst, R, A1, A2, A3, A4> {
    typedef R (TObj::*type)(A1, A2, A3, A4);
};

template <typename TObj, typename R, typename A1, typename A2, typename A3>
struct MemberFunc<TObj, NonConst, R, A1, A2, A3> {
    typedef R (TObj::*type)(A1, A2, A3);
};

template <typename TObj, typename R, typename A1, typename A2>
struct MemberFunc<TObj, NonConst, R, A1, A2> {
    typedef R (TObj::*type)(A1, A2);
};

template <typename TObj, typename R, typename A1>
struct MemberFunc<TObj, NonConst, R, A1> {
    typedef R (TObj::*type)(A1);
};

template <typename R, typename TObj>
struct MemberFunc<TObj, NonConst, R> {
    typedef R (TObj::*type)();
};

template <typename TObj, typename R, typename A1, typename A2, typename A3, typename A4>
struct MemberFunc<TObj, Const, R, A1, A2, A3, A4> {
    typedef R (TObj::*type)(A1, A2, A3, A4) const;
};

template <typename TObj, typename R, typename A1, typename A2, typename A3>
struct MemberFunc<TObj, Const, R, A1, A2, A3> {
    typedef R (TObj::*type)(A1, A2, A3) const;
};

template <typename TObj, typename R, typename A1, typename A2>
struct MemberFunc<TObj, Const, R, A1, A2> {
    typedef R (TObj::*type)(A1, A2) const;
};

template <typename TObj, typename R, typename A1>
struct MemberFunc<TObj, Const, R, A1> {
    typedef R (TObj::*type)(A1) const;
};

template <typename R, typename TObj>
struct MemberFunc<TObj, Const, R> {
    typedef R (TObj::*type)() const;
};


struct Default{};
struct NonDefault{};
//==============struct CallableImpl===================

/**
 * @brief The struct CallableImpl contains conrcrete
 * implementations of the Invokable-inferface specializing void and non-void cases
 */
template <typename R>
struct InvokableImpl {

    typedef R R_;

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, typename isDefault = Default>
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

    template <typename isDefault>  // must have at least one template parameter to compile!
    struct GlobalFunction<void, void, void, void, void, isDefault> : public Invokable<R_> { //must be non-default!
        typedef GlobalFunction<void, void, void, void, void, isDefault> Classtype;
        typedef Invokable<R_> Superclass;
        typedef R_ (*Member)();
        virtual R_ operator()() { return m_member(); }
        GlobalFunction(Member member) : m_member(member) {}
        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}
    private:
        Member m_member;
    };




    //////////////////////////////////////////////////////////
    template <typename TObj, typename Constness, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
    struct MemberFunction;

    template <typename TObj, typename Constness, typename A1, typename A2, typename A3, typename A4>
    struct MemberFunction<TObj, Constness, A1, A2, A3, A4> : public Invokable<R_, A1, A2, A3, A4> {

        typedef MemberFunction<TObj, Constness, A1, A2, A3, A4> Classtype;
        typedef Invokable<R_, A1, A2, A3, A4> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_, A1, A2, A3, A4>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { return (m_obj.*m_member)(a1, a2, a3, a4); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };


    template <typename TObj, typename Constness, typename A1, typename A2, typename A3>
    struct MemberFunction<TObj, Constness, A1, A2, A3> : public Invokable<R_, A1, A2, A3> {

        typedef MemberFunction<TObj, Constness, A1, A2, A3> Classtype;
        typedef Invokable<R_, A1, A2, A3> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_, A1, A2, A3>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { return (m_obj.*m_member)(a1, a2, a3); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, typename Constness, typename A1, typename A2>
    struct MemberFunction<TObj, Constness, A1, A2> : public Invokable<R_, A1, A2> {

        typedef MemberFunction<TObj, Constness, A1, A2> Classtype;
        typedef Invokable<R_, A1, A2> Superclass;
        typedef typename MemberFunc<TObj, Constness, R_, A1, A2>::type Member;

        virtual R_ operator()(A1 a1, A2 a2) { return (m_obj.*m_member)(a1, a2); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, typename Constness, typename A1>
    struct MemberFunction<TObj, Constness, A1> : public Invokable<R_, A1> {

        typedef MemberFunction<TObj, Constness, A1> Classtype;
        typedef Invokable<R_, A1> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_, A1>::type Member;

        virtual R_ operator()(A1 a1) { return (m_obj.*m_member)(a1); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }
    private:

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, typename Constness>
    struct MemberFunction<TObj, Constness> : public Invokable<R_> {

        typedef MemberFunction<TObj, Constness> Classtype;
        typedef Invokable<R_> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_>::type Member;

        virtual R_ operator()() { return (m_obj.*m_member)(); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, typename isDefault = Default>
    struct BoundFunction;

    template <typename A1, typename A2, typename A3, typename A4>
    struct BoundFunction<A1, A2, A3, A4> {
        A1 a1;
        A2 a2;
        A3 a3;
        A4 a4;
        BoundFunction(A1 a1_, A2 a2_, A3 a3_, A4 a4_):a1(a1_),a2(a2_),a3(a3_),a4(a4_){}
        virtual R_ operator()(Invokable<R_,A1, A2, A3, A4>& invokable) { return invokable(a1,a2,a3,a4); }
    };

    template <typename A1, typename A2, typename A3>
    struct BoundFunction<A1, A2, A3> {
        A1 a1;
        A2 a2;
        A3 a3;
        BoundFunction(A1 a1_, A2 a2_, A3 a3_):a1(a1_),a2(a2_),a3(a3_){}
        virtual R_ operator()(Invokable<R_,A1, A2, A3>& invokable) { return invokable(a1,a2,a3); }
    };

    template <typename A1, typename A2>
    struct BoundFunction<A1, A2> {
        A1 a1;
        A2 a2;
        BoundFunction(A1 a1_, A2 a2_):a1(a1_),a2(a2_){}
        virtual R_ operator()(Invokable<R_,A1, A2>& invokable) { return invokable(a1,a2); }
    };

    template <typename A1>
    struct BoundFunction<A1> {
        A1 a1;
        BoundFunction(A1 a1_):a1(a1_){}
        virtual R_ operator()(Invokable<R_,A1>& invokable) { return invokable(a1); }
    };

    template<typename isDefault>  // must have at least one template parameter to compile!
    struct BoundFunction<void,void,void,void,void,isDefault> {
        BoundFunction(){}
        virtual R_ operator()(Invokable<R_>& invokable) { return invokable(); }
    };
};
template <>
struct InvokableImpl<void> {

    typedef void R_;

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, typename isDefault = Default>
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

    template <typename isDefault>  // must have at least one template parameter to compile!
    struct GlobalFunction<void, void, void, void, void, isDefault> : public Invokable<R_> { //must be nonDefault

        typedef GlobalFunction<void, void, void, void, void, isDefault> Classtype;
        typedef Invokable<R_> Superclass;

        typedef R_ (*Member)();

        virtual R_ operator()() { m_member(); }

        GlobalFunction(Member member) : m_member(member) {}

        bool isEqual(Classtype const& other)const{ return m_member == other.m_member;}

    private:
        Member m_member;
    };


    //////////////////////////////////////////////////////////


    template <typename TObj, typename Constness, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
    struct MemberFunction;

    template <typename TObj, typename Constness, typename A1, typename A2, typename A3, typename A4>
    struct MemberFunction<TObj, Constness, A1, A2, A3, A4> : public Invokable<R_, A1, A2, A3, A4> {

        typedef MemberFunction<TObj, Constness, A1, A2, A3, A4> Classtype;
        typedef Invokable<R_, A1, A2, A3, A4> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_, A1, A2, A3, A4>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { (m_obj.*m_member)(a1, a2, a3, a4); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, typename Constness, typename A1, typename A2, typename A3>
    struct MemberFunction<TObj, Constness, A1, A2, A3> : public Invokable<R_, A1, A2, A3> {

        typedef MemberFunction<TObj, Constness, A1, A2, A3> Classtype;
        typedef Invokable<R_, A1, A2, A3> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_, A1, A2, A3>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { (m_obj.*m_member)(a1, a2, a3); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, typename Constness, typename A1, typename A2>
    struct MemberFunction<TObj, Constness, A1, A2> : public Invokable<R_, A1, A2> {

        typedef MemberFunction<TObj, Constness, A1, A2> Classtype;
        typedef Invokable<R_, A1, A2> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_, A1, A2>::type Member;

        virtual R_ operator()(A1 a1, A2 a2) { (m_obj.*m_member)(a1, a2); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, typename Constness, typename A1>
    struct MemberFunction<TObj, Constness, A1> : public Invokable<R_, A1> {

        typedef MemberFunction<TObj, Constness, A1> Classtype;
        typedef Invokable<R_, A1> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_, A1>::type Member;

        virtual R_ operator()(A1 a1) { (m_obj.*m_member)(a1); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename TObj, typename Constness>
    struct MemberFunction<TObj, Constness> : public Invokable<R_> {

        typedef MemberFunction<TObj, Constness> Classtype;
        typedef Invokable<R_> Superclass;

        typedef typename MemberFunc<TObj, Constness, R_>::type Member;

        virtual R_ operator()() { (m_obj.*m_member)(); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        bool isEqual(Classtype const& other)const{
            return (&m_obj == &(other.m_obj)) && (m_member == other.m_member);
        }

    private:
        TObj& m_obj;
        Member m_member;
    };

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, typename isDefault = Default>
    struct BoundFunction;

    template <typename A1, typename A2, typename A3, typename A4>
    struct BoundFunction<A1, A2, A3, A4> {
        A1 a1;
        A2 a2;
        A3 a3;
        A4 a4;
        BoundFunction(A1 a1_, A2 a2_, A3 a3_, A4 a4_):a1(a1_),a2(a2_),a3(a3_),a4(a4_){}
        virtual R_ operator()(Invokable<R_,A1, A2, A3, A4>& invokable) { invokable(a1,a2,a3,a4); }
    };

    template <typename A1, typename A2, typename A3>
    struct BoundFunction<A1, A2, A3> {
        A1 a1;
        A2 a2;
        A3 a3;
        BoundFunction(A1 a1_, A2 a2_, A3 a3_):a1(a1_),a2(a2_),a3(a3_){}
        virtual R_ operator()(Invokable<R_,A1, A2, A3>& invokable) { invokable(a1,a2,a3); }
    };

    template <typename A1, typename A2>
    struct BoundFunction<A1, A2> {
        A1 a1;
        A2 a2;
        BoundFunction(A1 a1_, A2 a2_):a1(a1_),a2(a2_){}
        virtual R_ operator()(Invokable<R_,A1, A2>& invokable) { invokable(a1,a2); }
    };

    template <typename A1>
    struct BoundFunction<A1> {
        A1 a1;
        BoundFunction(A1 a1_):a1(a1_){}
        virtual R_ operator()(Invokable<R_,A1>& invokable) { invokable(a1); }
    };

    template<typename isDefault>  // must have at least one template parameter to compile!
    struct BoundFunction<void,void,void,void,void,isDefault> {
        BoundFunction(){}
        virtual R_ operator()(Invokable<R_>& invokable) { invokable(); }
    };
};

struct ScopedInversion{
    bool& target;
    const bool origValue;
    ScopedInversion(bool& target_):target(target_),origValue(target_){target = !target;}
    ~ScopedInversion(){target = origValue;}
};



typedef bool DisconnectionPending;
inline DisconnectionPending disconnectPending(){return true;}
inline DisconnectionPending connected(){return disconnectPending()==false;}


template<typename TInvokablePtr>
struct IsPendingDisconnect {

    typedef std::pair<TInvokablePtr,bool> Slot;

    bool operator()(Slot const& other)const{
        return other.second == disconnectPending();
    }
};


/**
 * @brief Comparing of 2 invokable instances
 */
template<typename TInvokable>
struct IsCaller {

    typedef std::pair<typename TInvokable::Superclass*,bool> Slot;

    IsCaller(TInvokable const& c):invokable(c){}
    TInvokable const& invokable;

    bool operator()(Slot const& other)const{
        TInvokable const* t = dynamic_cast<TInvokable const*>(other.first);
        return t!=NULL ? invokable.isEqual(*t) : false;
    }
};




/**
 * Removing a slot from the list of slots
 */
template<typename Slots>
void disconnectNow(Slots& slots){

    const IsPendingDisconnect<typename Slots::value_type::first_type> pred;

    typedef typename Slots::const_iterator It;
    for(It it = slots.begin(), end = slots.end();it!=end;++it)
        if (pred(*it))
            delete it->first;

    slots.erase(std::remove_if(slots.begin(),slots.end(), pred), slots.end());
}

template<typename Slots, typename TCaller>
void disconnectDelayed(Slots& slots, TCaller const& caller){

    const IsCaller<TCaller> pred(caller);

    typedef typename Slots::iterator It;
    for(It it = slots.begin(), end = slots.end();it!=end;++it)
        if (pred(*it))
            it->second = disconnectPending();

}


template<typename Slots, typename TCaller>
void disconnect(Slots& slots, bool isCurrentlyEmitting, TCaller const& caller){

    disconnectDelayed(slots,caller);

    if (!isCurrentlyEmitting)
        disconnectNow(slots);
}

/**
 * Removing a slot from the list of slots
 */


template<typename Slots>
void disconnectAll(Slots& slots){
    typedef typename Slots::const_iterator SlotsCIt;
    for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
        delete *it;
    slots.clear();
}

template<typename Slots>
void disconnectAllNow(Slots& slots){
    typedef typename Slots::const_iterator SlotsCIt;
    for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
        delete it->first;
    slots.clear();
}

template<typename Slots>
void disconnectAllDelayed(Slots& slots){
    typedef typename Slots::iterator SlotsCIt;
    for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
        it->second = disconnectPending();

}

template<typename Slots>
void disconnectAll(Slots& slots, bool isCurrentlyEmitting){
    if (isCurrentlyEmitting)
        disconnectAllDelayed(slots);
    else
        disconnectAllNow(slots);

}

template<typename OutType_, typename CallResult>
void aggregateReturnValue(OutType_& c, CallResult const& r) {
    c.out.push_back(r);
}

template <typename R>
struct ReturnValueAggregator {

    typedef R R_;

    template <typename Slots, typename Args>
    static void invokeAndAggregate(ReturnValueAggregate<R_>& r, Slots& slots, Args& args) {

        typedef typename Slots::const_iterator SlotsCIt;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it) {
             aggregateReturnValue(r,args(*(it->first)));
        }
    }
};

template <>
struct ReturnValueAggregator<void> {

    typedef void R_;

    template <typename Slots, typename Args>
    static void invokeAndAggregate(ReturnValueAggregate<R_>&, Slots& slots, Args& args) {

        typedef typename Slots::const_iterator SlotsCIt;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it) {
             args(*(it->first));
        }
    }
};


template<typename Slots, typename Invokable>
void connect(Slots& slots, Invokable invokable){
    slots.push_back(invokable);
}


template<typename Slots>
void connectPending(Slots& slots, Slots& pendingConnects){

    typedef typename Slots::const_iterator SlotsCIt;
    for (SlotsCIt it = pendingConnects.begin(), end = pendingConnects.end(); it != end; ++it)
         connect(slots,*it);

    pendingConnects.clear();
}

template<typename Slots>
void disconnectPending(Slots& slots){
    disconnectNow(slots);
}


} //namespace detail


/**
 * @brief Main class realizing signal slot behaviour.
 */
template <typename TFunc>
struct Signal;

template <typename R, typename A1, typename A2, typename A3,typename A4>
struct Signal<R(A1, A2, A3, A4)> {

    void connect(R (*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new GCaller(member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj const& obj, R (TObj::*member)(A1, A2, A3, A4) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    detail::ReturnValueAggregate<R> emit(A1 a1, A2 a2, A3 a3, A4 a4) {
        ScopedLock_ lock(slotsMutex);
        Args args(a1,a2,a3,a4);
        detail::ReturnValueAggregate<R> r;
        if (isCurrentlyEmitting) return r;
        detail::ScopedInversion inverter(isCurrentlyEmitting);
        detail::ReturnValueAggregator<R>::invokeAndAggregate(r, slots, args);
        detail::disconnectPending(slots);
        detail::connectPending(slots, pendingConnects);
        return r;
    }

    void disconnect(R (*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        detail::disconnect(slots, isCurrentlyEmitting, GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj const& obj, R (TObj::*member)(A1, A2, A3, A4) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
        detail::disconnectAll(slots, isCurrentlyEmitting);
    }

    ~Signal(){ assert(isCurrentlyEmitting==false); disconnectAll(); } //upon returning from dtor object is invalid so a pending emit()-call would be invalid too!

   private:
    typedef typename detail::InvokableImpl<R>::template BoundFunction<A1, A2, A3, A4> Args;
    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1, A2, A3, A4> GCaller;

    template <typename TObj, typename Constness>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, Constness, A1, A2, A3, A4> type; };

    typedef std::pair<detail::Invokable<R, A1, A2, A3, A4>*,detail::DisconnectionPending> Slot;
    typedef typename detail::SlotContainer<Slot>::type Slots;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    bool isCurrentlyEmitting = false;
    Slots pendingConnects;
    Slots slots;
    Mutex_ slotsMutex;
};

template <typename R, typename A1, typename A2, typename A3>
struct Signal<R(A1, A2, A3)> {

    void connect(R (*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new GCaller(member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj const& obj, R (TObj::*member)(A1, A2, A3) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    detail::ReturnValueAggregate<R> emit(A1 a1, A2 a2, A3 a3) {
        ScopedLock_ lock(slotsMutex);
        Args args(a1,a2,a3);
        detail::ReturnValueAggregate<R> r;
        if (isCurrentlyEmitting) return r;
        detail::ScopedInversion inverter(isCurrentlyEmitting);
        detail::ReturnValueAggregator<R>::invokeAndAggregate(r, slots, args);
        detail::disconnectPending(slots);
        detail::connectPending(slots, pendingConnects);
        return r;
    }

    void disconnect(R (*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        detail::disconnect(slots, isCurrentlyEmitting, GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2, A3)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj const& obj, R (TObj::*member)(A1, A2, A3) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
        detail::disconnectAll(slots, isCurrentlyEmitting);
    }

    ~Signal(){ assert(isCurrentlyEmitting==false); disconnectAll(); } //upon returning from dtor object is invalid so a pending emit()-call would be invalid too!

   private:
    typedef typename detail::InvokableImpl<R>::template BoundFunction<A1, A2, A3> Args;
    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1, A2, A3> GCaller;

    template <typename TObj, typename Constness>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, Constness, A1, A2, A3> type; };

    typedef std::pair<detail::Invokable<R, A1, A2, A3>*,detail::DisconnectionPending> Slot;
    typedef typename detail::SlotContainer<Slot>::type Slots;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    bool isCurrentlyEmitting = false;
    Slots pendingConnects;
    Slots slots;
    Mutex_ slotsMutex;
};



template <typename R, typename A1, typename A2>
struct Signal<R(A1, A2)> {

    void connect(R (*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new GCaller(member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj const& obj, R (TObj::*member)(A1, A2) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    detail::ReturnValueAggregate<R> emit(A1 a1, A2 a2) {
        ScopedLock_ lock(slotsMutex);
        Args args(a1,a2);
        detail::ReturnValueAggregate<R> r;
        if (isCurrentlyEmitting) return r;
        detail::ScopedInversion inverter(isCurrentlyEmitting);
        detail::ReturnValueAggregator<R>::invokeAndAggregate(r, slots, args);
        detail::disconnectPending(slots);
        detail::connectPending(slots, pendingConnects);
        return r;
    }

    void disconnect(R (*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        detail::disconnect(slots, isCurrentlyEmitting, GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1, A2)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj const& obj, R (TObj::*member)(A1, A2) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
        detail::disconnectAll(slots, isCurrentlyEmitting);
    }

    ~Signal(){ assert(isCurrentlyEmitting==false); disconnectAll(); } //upon returning from dtor object is invalid so a pending emit()-call would be invalid too!

   private:
    typedef typename detail::InvokableImpl<R>::template BoundFunction<A1, A2> Args;
    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1, A2> GCaller;

    template <typename TObj, typename Constness>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, Constness, A1, A2> type; };

    typedef std::pair<detail::Invokable<R, A1, A2>*,detail::DisconnectionPending> Slot;
    typedef typename detail::SlotContainer<Slot>::type Slots;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    bool isCurrentlyEmitting = false;
    Slots pendingConnects;
    Slots slots;
    Mutex_ slotsMutex;
};



template <typename R, typename A1>
struct Signal<R(A1)> {

    void connect(R (*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new GCaller(member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj const& obj, R (TObj::*member)(A1) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    detail::ReturnValueAggregate<R> emit(A1 a1) {
        ScopedLock_ lock(slotsMutex);
        Args args(a1);
        detail::ReturnValueAggregate<R> r;
        if (isCurrentlyEmitting) return r;
        detail::ScopedInversion inverter(isCurrentlyEmitting);
        detail::ReturnValueAggregator<R>::invokeAndAggregate(r, slots, args);
        detail::disconnectPending(slots);
        detail::connectPending(slots, pendingConnects);
        return r;
    }

    void disconnect(R (*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        detail::disconnect(slots, isCurrentlyEmitting, GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)(A1)) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj const& obj, R (TObj::*member)(A1) const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
        detail::disconnectAll(slots, isCurrentlyEmitting);
    }

    ~Signal(){ assert(isCurrentlyEmitting==false); disconnectAll(); } //upon returning from dtor object is invalid so a pending emit()-call would be invalid too!

   private:
    typedef typename detail::InvokableImpl<R>::template BoundFunction<A1> Args;
    typedef typename detail::InvokableImpl<R>::template GlobalFunction<A1> GCaller;

    template <typename TObj, typename Constness>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, Constness, A1> type; };

    typedef std::pair<detail::Invokable<R, A1>*,detail::DisconnectionPending> Slot;
    typedef typename detail::SlotContainer<Slot>::type Slots;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    bool isCurrentlyEmitting = false;
    Slots pendingConnects;
    Slots slots;
    Mutex_ slotsMutex;
};



template <typename R>
struct Signal<R()> {

    void connect(R (*member)()) {
        ScopedLock_ lock(slotsMutex);
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new GCaller(member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)()) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    template <typename TObj>
    void connect(TObj const& obj, R (TObj::*member)() const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::connect(isCurrentlyEmitting ? pendingConnects : slots, Slot(new MCaller_(obj, member),detail::connected()));
    }

    detail::ReturnValueAggregate<R> emit() {
        ScopedLock_ lock(slotsMutex);
        Args args;
        detail::ReturnValueAggregate<R> r;
        if (isCurrentlyEmitting) return r;
        detail::ScopedInversion inverter(isCurrentlyEmitting);
        detail::ReturnValueAggregator<R>::invokeAndAggregate(r, slots, args);
        detail::disconnectPending(slots);
        detail::connectPending(slots, pendingConnects);
        return r;
    }

    void disconnect(R (*member)()) {
        ScopedLock_ lock(slotsMutex);
        detail::disconnect(slots, isCurrentlyEmitting, GCaller(member));
    }

    template <typename TObj>
    void disconnect(TObj& obj, R (TObj::*member)()) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<TObj,detail::NonConst>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    template <typename TObj>
    void disconnect(TObj const& obj, R (TObj::*member)() const) {
        ScopedLock_ lock(slotsMutex);
        typedef typename MCaller<const TObj,detail::Const>::type MCaller_;
        detail::disconnect(slots, isCurrentlyEmitting, MCaller_(obj,member));
    }

    void disconnectAll(){
        ScopedLock_ lock(slotsMutex);
        detail::disconnectAll(slots, isCurrentlyEmitting);
    }

    ~Signal(){ assert(isCurrentlyEmitting==false); disconnectAll(); } //upon returning from dtor object is invalid so a pending emit()-call would be invalid too!

   private:
    typedef typename detail::InvokableImpl<R>::template BoundFunction<void, void, void, void, void, detail::NonDefault> Args;
    typedef typename detail::InvokableImpl<R>::template GlobalFunction<void, void, void, void, void, detail::NonDefault> GCaller;

    template <typename TObj, typename Constness>
    struct MCaller{ typedef typename detail::InvokableImpl<R>::template MemberFunction<TObj, Constness> type; };

    typedef std::pair<detail::Invokable<R>*,detail::DisconnectionPending> Slot;
    typedef typename detail::SlotContainer<Slot>::type Slots;

    typedef detail::Mutex::type Mutex_;
    typedef detail::ScopedLock::type ScopedLock_;

    bool isCurrentlyEmitting = false;
    Slots pendingConnects;
    Slots slots;
    Mutex_ slotsMutex;
};






}  // namespace sisl
