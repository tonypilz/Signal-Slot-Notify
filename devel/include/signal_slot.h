#include <vector>

namespace sisl {  // signal slot



//==============types===================

template <typename TCallable>
struct SlotContainer {
    typedef std::vector<TCallable> type;
};

template <typename TResult>
struct ResultContainerType {
    typedef std::vector<TResult> type;
};




//==============Callable===================

template <typename R = void, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
struct Callable;

template <typename R, typename A1, typename A2, typename A3, typename A4>
struct Callable<R, A1, A2, A3, A4> {
    virtual R operator()(A1, A2, A3, A4) = 0;
    virtual ~Callable() {}
};

template <typename R, typename A1, typename A2, typename A3>
struct Callable<R, A1, A2, A3> {
    virtual R operator()(A1, A2, A3) = 0;
    virtual ~Callable() {}
};

template <typename R, typename A1, typename A2>
struct Callable<R, A1, A2> {
    virtual R operator()(A1, A2) = 0;
    virtual ~Callable() {}
};

template <typename R, typename A1>
struct Callable<R, A1> {
    virtual R operator()(A1) = 0;
    virtual ~Callable() {}
};

template <typename R>
struct Callable<R> {
    virtual R operator()() = 0;
    virtual ~Callable() {}
};



//==============MemberFunc===================

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




//==============CallableImpl===================

template <typename R>
struct CallableImpl {
    static const bool dummy = true;
    typedef R R_;

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, bool Dummy = dummy>
    struct GlobalFunction;

    template <typename A1, typename A2, typename A3, typename A4>
    struct GlobalFunction<A1, A2, A3, A4> : public Callable<R_, A1, A2, A3, A4> {
        typedef R_ (*Member)(A1, A2, A3, A4);
        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { return m_member(a1, a2, a3, a4); }
        GlobalFunction(Member member) : m_member(member) {}
        Member m_member;
    };

    template <typename A1, typename A2, typename A3>
    struct GlobalFunction<A1, A2, A3> : public Callable<R_, A1, A2, A3> {
        typedef R_ (*Member)(A1, A2, A3);
        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { return m_member(a1, a2, a3); }
        GlobalFunction(Member member) : m_member(member) {}
        Member m_member;
    };

    template <typename A1, typename A2>
    struct GlobalFunction<A1, A2> : public Callable<R_, A1, A2> {
        typedef R_ (*Member)(A1, A2);
        virtual R_ operator()(A1 a1, A2 a2) { return m_member(a1, a2); }
        GlobalFunction(Member member) : m_member(member) {}
        Member m_member;
    };

    template <typename A1>
    struct GlobalFunction<A1> : public Callable<R_, A1> {
        typedef R_ (*Member)(A1);
        virtual R_ operator()(A1 a1) { return m_member(a1); }
        GlobalFunction(Member member) : m_member(member) {}
        Member m_member;
    };

    template <bool Dummy>  // must have at least one template parameter to compile!
    struct GlobalFunction<void, void, void, void, void, Dummy> : public Callable<R_> {
        typedef R_ (*Member)();
        virtual R_ operator()() { return m_member(); }
        GlobalFunction(Member member) : m_member(member) {}
        Member m_member;
    };




    //////////////////////////////////////////////////////////
    template <typename TObj, bool IsConst, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
    struct MemberFunction;

    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3, typename A4>
    struct MemberFunction<TObj, IsConst, A1, A2, A3, A4> : public Callable<R_, A1, A2, A3, A4> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3, A4>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { return (m_obj.*m_member)(a1, a2, a3, a4); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };


    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3>
    struct MemberFunction<TObj, IsConst, A1, A2, A3> : public Callable<R_, A1, A2, A3> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { return (m_obj.*m_member)(a1, a2, a3); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst, typename A1, typename A2>
    struct MemberFunction<TObj, IsConst, A1, A2> : public Callable<R_, A1, A2> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2>::type Member;

        virtual R_ operator()(A1 a1, A2 a2) { return (m_obj.*m_member)(a1, a2); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst, typename A1>
    struct MemberFunction<TObj, IsConst, A1> : public Callable<R_, A1> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1>::type Member;

        virtual R_ operator()(A1 a1) { return (m_obj.*m_member)(a1); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst>
    struct MemberFunction<TObj, IsConst> : public Callable<R_> {

        typedef typename MemberFunc<TObj, IsConst, R_>::type Member;

        virtual R_ operator()() { return (m_obj.*m_member)(); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
};
template <>
struct CallableImpl<void> {

    static const bool dummy = true;
    typedef void R_;

    template <typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void, bool Dummy = dummy>
    struct GlobalFunction;

    template <typename A1, typename A2, typename A3, typename A4>
    struct GlobalFunction<A1, A2, A3, A4> : public Callable<R_, A1, A2, A3, A4> {

        typedef R_ (*Member)(A1, A2, A3, A4);

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { m_member(a1, a2, a3, a4); }

        GlobalFunction(Member member) : m_member(member) {}

        Member m_member;
    };

    template <typename A1, typename A2, typename A3>
    struct GlobalFunction<A1, A2, A3> : public Callable<R_, A1, A2, A3> {

        typedef R_ (*Member)(A1, A2, A3);

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { m_member(a1, a2, a3); }

        GlobalFunction(Member member) : m_member(member) {}

        Member m_member;
    };
    template <typename A1, typename A2>
    struct GlobalFunction<A1, A2> : public Callable<R_, A1, A2> {

        typedef R_ (*Member)(A1, A2);

        virtual R_ operator()(A1 a1, A2 a2) { m_member(a1, a2); }

        GlobalFunction(Member member) : m_member(member) {}

        Member m_member;

    };

    template <typename A1>
    struct GlobalFunction<A1> : public Callable<R_, A1> {

        typedef R_ (*Member)(A1);

        virtual R_ operator()(A1 a1) { m_member(a1); }

        GlobalFunction(Member member) : m_member(member) {}

        Member m_member;
    };

    template <bool Dummy>  // must have at least one template parameter to compile!
    struct GlobalFunction<void, void, void, void, void, Dummy> : public Callable<R_> {

        typedef R_ (*Member)();

        virtual R_ operator()() { m_member(); }

        GlobalFunction(Member member) : m_member(member) {}

        Member m_member;
    };
    //////////////////////////////////////////////////////////
    template <typename TObj, bool IsConst, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
    struct MemberFunction;

    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3, typename A4>
    struct MemberFunction<TObj, IsConst, A1, A2, A3, A4> : public Callable<R_, A1, A2, A3, A4> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3, A4>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3, A4 a4) { (m_obj.*m_member)(a1, a2, a3, a4); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst, typename A1, typename A2, typename A3>
    struct MemberFunction<TObj, IsConst, A1, A2, A3> : public Callable<R_, A1, A2, A3> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2, A3>::type Member;

        virtual R_ operator()(A1 a1, A2 a2, A3 a3) { (m_obj.*m_member)(a1, a2, a3); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst, typename A1, typename A2>
    struct MemberFunction<TObj, IsConst, A1, A2> : public Callable<R_, A1, A2> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1, A2>::type Member;

        virtual R_ operator()(A1 a1, A2 a2) { (m_obj.*m_member)(a1, a2); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst, typename A1>
    struct MemberFunction<TObj, IsConst, A1> : public Callable<R_, A1> {

        typedef typename MemberFunc<TObj, IsConst, R_, A1>::type Member;

        virtual R_ operator()(A1 a1) { (m_obj.*m_member)(a1); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
    template <typename TObj, bool IsConst>
    struct MemberFunction<TObj, IsConst> : public Callable<R_> {

        typedef typename MemberFunc<TObj, IsConst, R_>::type Member;

        virtual R_ operator()() { (m_obj.*m_member)(); }

        MemberFunction(TObj& obj, Member member) : m_obj(obj), m_member(member) {}

        TObj& m_obj;
        Member m_member;
    };
};




//==============OutType===================

template <typename R>
struct OutType {

    typedef typename ResultContainerType<R>::type type;

    operator type() const { return out; }

    type out;
};

template <>
struct OutType<void> {};


//==============Collector===================

template <typename R>
struct Collector {

    typedef R R_;

    template <typename A1, typename A2, typename A3, typename A4>
    static void callAndCollect(OutType<R_>& r, Callable<R_, A1, A2, A3, A4>* c, A1 a1, A2 a2, A3 a3, A4 a4) {
        r.out.push_back(c->operator()(a1, a2, a3, a4));
    }

    template <typename A1, typename A2, typename A3>
    static void callAndCollect(OutType<R_>& r, Callable<R_, A1, A2, A3>* c, A1 a1, A2 a2, A3 a3) {
        r.out.push_back(c->operator()(a1, a2, a3));
    }

    template <typename A1, typename A2>
    static void callAndCollect(OutType<R_>& r, Callable<R_, A1, A2>* c, A1 a1, A2 a2) {
        r.out.push_back(c->operator()(a1, a2));
    }

    template <typename A1>
    static void callAndCollect(OutType<R_>& r, Callable<R_, A1>* c, A1 a1) {
        r.out.push_back(c->operator()(a1));
    }

    static void callAndCollect(OutType<R_>& r, Callable<R_>* c) { r.out.push_back(c->operator()()); }
};

template <>
struct Collector<void> {

    typedef void R_;

    template <typename A1, typename A2, typename A3, typename A4>
    static void callAndCollect(OutType<R_>&, Callable<R_, A1, A2, A3, A4>* c, A1 a1, A2 a2, A3 a3, A4 a4) {
        c->operator()(a1, a2, a3, a4);
    }

    template <typename A1, typename A2, typename A3>
    static void callAndCollect(OutType<R_>&, Callable<R_, A1, A2, A3>* c, A1 a1, A2 a2, A3 a3) {
        c->operator()(a1, a2, a3);
    }

    template <typename A1, typename A2>
    static void callAndCollect(OutType<R_>&, Callable<R_, A1, A2>* c, A1 a1, A2 a2) {
        c->operator()(a1, a2);
    }

    template <typename A1>
    static void callAndCollect(OutType<R_>&, Callable<R_, A1>* c, A1 a1) {
        c->operator()(a1);
    }

    static void callAndCollect(OutType<R_>&, Callable<R_>* c) { c->operator()(); }
};


//==============Collector===================

template <typename R = void, typename A1 = void, typename A2 = void, typename A3 = void, typename A4 = void, typename A5 = void>
struct Signal;

template <typename R, typename A1, typename A2, typename A3, typename A4>
struct Signal<R, A1, A2, A3, A4> {

    void connect(R (*member)(A1, A2, A3, A4)) {
        typedef typename CallableImpl<R>::template GlobalFunction<A1, A2, A3, A4> Caller;
        slots.push_back(new Caller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4)) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, NotConst, A1, A2, A3, A4> Caller;
        slots.push_back(new Caller(obj, member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3, A4) const) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, Const, A1, A2, A3, A4> Caller;
        slots.push_back(new Caller(obj, member));
    }

    OutType<R> emit(A1 a1, A2 a2, A3 a3, A4 a4) {
        OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            Collector<R>::template callAndCollect<A1, A2, A3, A4>(r, *it, a1, a2, a3, a4);
        return r;
    }

   private:

    typedef Callable<R, A1, A2, A3, A4> Slot;
    typedef typename SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    Slots slots;
};

template <typename R, typename A1, typename A2, typename A3>
struct Signal<R, A1, A2, A3> {

    void connect(R (*member)(A1, A2, A3)) {
        typedef typename CallableImpl<R>::template GlobalFunction<A1, A2, A3> Caller;
        slots.push_back(new Caller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3)) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, NotConst, A1, A2, A3> Caller;
        slots.push_back(new Caller(obj, member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2, A3) const) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, Const, A1, A2, A3> Caller;
        slots.push_back(new Caller(obj, member));
    }

    OutType<R> emit(A1 a1, A2 a2, A3 a3) {
        OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            Collector<R>::template callAndCollect<A1, A2, A3>(r, *it, a1, a2, a3);
        return r;
    }

   private:

    typedef Callable<R, A1, A2, A3> Slot;
    typedef typename SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    Slots slots;
};

template <typename R, typename A1, typename A2>
struct Signal<R, A1, A2> {

    void connect(R (*member)(A1, A2)) {
        typedef typename CallableImpl<R>::template GlobalFunction<A1, A2> Caller;
        slots.push_back(new Caller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2)) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, NotConst, A1, A2> Caller;
        slots.push_back(new Caller(obj, member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1, A2) const) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, Const, A1, A2> Caller;
        slots.push_back(new Caller(obj, member));
    }

    OutType<R> emit(A1 a1, A2 a2) {
        OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            Collector<R>::template callAndCollect<A1, A2>(r, *it, a1, a2);
        return r;
    }

   private:

    typedef Callable<R, A1, A2> Slot;
    typedef typename SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    Slots slots;
};

template <typename R, typename A1>
struct Signal<R, A1> {

    void connect(R (*member)(A1)) {
        typedef typename CallableImpl<R>::template GlobalFunction<A1> Caller;
        slots.push_back(new Caller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1)) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, NotConst, A1> Caller;
        slots.push_back(new Caller(obj, member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)(A1) const) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, Const, A1> Caller;
        slots.push_back(new Caller(obj, member));
    }

    OutType<R> emit(A1 a1) {
        OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            Collector<R>::template callAndCollect<A1>(r, *it, a1);
        return r;
    }

   private:

    typedef Callable<R, A1> Slot;
    typedef typename SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    Slots slots;
};

template <typename R>
struct Signal<R> {

    void connect(R (*member)()) {
        static const bool dummy = false;
        typedef typename CallableImpl<R>::template GlobalFunction<void, void, void, void, void, dummy> Caller;  // special calse
        slots.push_back(new Caller(member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)()) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, NotConst> Caller;
        slots.push_back(new Caller(obj, member));
    }

    template <typename TObj>
    void connect(TObj& obj, R (TObj::*member)() const) {
        typedef typename CallableImpl<R>::template MemberFunction<TObj, Const> Caller;
        slots.push_back(new Caller(obj, member));
    }

    OutType<R> emit() {
        OutType<R> r;
        for (SlotsCIt it = slots.begin(), end = slots.end(); it != end; ++it)
            Collector<R>::callAndCollect(r, *it);  // special calse
        return r;
    }

   private:

    typedef Callable<R> Slot;
    typedef typename SlotContainer<Slot*>::type Slots;
    typedef typename Slots::iterator SlotsIt;
    typedef typename Slots::const_iterator SlotsCIt;

    Slots slots;
};
}  // namespace sisl
