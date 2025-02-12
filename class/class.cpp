#include <Windows.h>
#include <iomanip>
#include <iostream>

using namespace std;

/* This access control default is private.
Hierarchical inheritance into class a, class B, and class b. */
class           A
{
    /* Private member only can be accessed with class itself or friend */
    short   I;
    /* Public member can be accessed global */
    public:
        /* 
        Default constructor only declared from base class.
        Every class was created the constructor always auto called. */
        A()                                                     noexcept = default;
        /*
        Constructor with custom parameters.
        This explicit mean the parameters must be defined every calling this constructor.
        This function is overload polymorphism by define it with same name and different parameters. */
        explicit A(bool A, char a, unsigned char B, short b)    noexcept : G(A), H(a), h(B), I(b) {}
        /* Shallow copy constructor */
        explicit A(const A &A)                                  noexcept : G(A.G), H(A.H), h(A.h), I(A.I) {}
        /* Move constructor */
        explicit A(A &&A)                                       noexcept : G(std::move(A.G)), H(std::move(A.H)), h(std::move(A.h)), I(std::move(A.I)) {}
        /* Deep copy constructor.
        'this' pointer refer class itself. */
        A                                                       *f() noexcept {return new A(*this);}
        /* Copy assignment */
        A                                                       &operator=(A &a) noexcept
        {
            if      (this != &a)
            {
                A       *A = a.f();
                G       = A->G;
                H       = A->H;
                h       = A->h;
                I       = A->I;

                delete  A;
            }
            
            return  *this;
        }
        /* Move assignment */
        A                                                       &operator=(A &&a) noexcept
        {
            if      (this != &a)
            {
                A       *A = std::move(a.f());
                G       = std::move(A->G);
                H       = std::move(A->H);
                h       = std::move(A->h);
                I       = std::move(A->I);

                delete  A;
            }
            
            return  *this;
        }
        /*
        Every class was destroyed the destructor always auto called.
        This virtual polymorphism prevent undefined behavior destructor when class was derived. */
        virtual ~A()                                            noexcept = default;
        bool                                                    G;
        void                                                    g(char A, short a) noexcept {H = A, I = a;}
        void                                                    g() noexcept {cout << G << "\n" << static_cast<short>(H) << "\n" << static_cast<short>(h) << "\n" << I << "\n";}
    /* Protected member can only be accessed with class itself or derived and friend */
    protected:
        char            H;
        unsigned char   h;
};
/*
Single inheritance from public class A.
Public and protected member class A will be derived with same access control. */
class           a : virtual public A
{
    public:
        explicit a(bool a, char B, unsigned char b, short C)    noexcept : A(a, B, b, C) {}
        explicit a(const a &a)                                  noexcept : A(a) {}
        explicit a(a &&a)                                       noexcept : A(std::move(a)) {}
        a                                                       *i() noexcept {return new a(*this);}
        a                                                       &operator=(a &A) noexcept
        {
            if      (this != &A)
            {
                a       *B = A.i();

                A::operator=(*B);

                delete  B;
            }
            
            return  *this;
        }
        a                                                       &operator=(a &&A) noexcept
        {
            if      (this != &A)
            {
                a       *B = std::move(A.i());

                A::operator=(std::move(*B));

                delete  B;
            }
            
            return  *this;
        }
        virtual ~a()                                            noexcept = default;
        /* This static member must be defined in global */
        static unsigned short                                   J;
        static void                                             j() noexcept {cout << J << "\n";}
};
/*
Hybrid inheritance.
Multilevel inheritance from public class A.
Multiple inheritance from public class A and protected class a.
Public and protected member class a will be derived as protected member. */
unsigned short  a::J;
class           B : virtual public A, virtual protected a
{
    int k;
    public:
        explicit B(bool B, char b, unsigned char C, short c)    noexcept : A(B, b, C, c), a(B, b, C, c) {}
        explicit B(const B &B)                                  noexcept : A(B), a(B) {}
        explicit B(B &&B)                                       noexcept : A(std::move(B)), a(std::move(B)) {}
        B                                                       &operator=(B &A) noexcept
        {
            if      (this != &A)
            {
                A::operator=(A);
                a::operator=(A);
            }
            
            return  *this;
        }
        B                                                       &operator=(B &&A) noexcept
        {
            if      (this != &A)
            {
                A::operator=(std::move(A));
                a::operator=(std::move(A));
            }
            
            return  *this;
        }
    virtual ~B()                                                noexcept = default;
    /* Define pure virtual polymorphism function to create abstract class which can't be created directly and must be derived to override polymorphism this function */
    virtual void                                                K(int A) = 0;
    /* This final mean this function can't be override polymorphism anymore */
    virtual void                                                K(unsigned char A) noexcept final {h = A;}
    /* class b which not member this class will have all access control of this class */
    friend class                                                b;
};
/* Public and protected member class B will be derived as private member */
class               b : virtual public A, virtual protected a, B
{
    public:
        explicit b(bool b, char C, unsigned char c, short D)    noexcept : A(b, C, c, D), a(b, C, c, D), B(b, C, c, D) {}
        explicit b(const b &b)                                  noexcept : A(b), a(b), B(b) {}
        explicit b(b &&b)                                       noexcept : A(std::move(b)), a(std::move(b)), B(std::move(b)) {}
        b                                                       *L() noexcept {return new b(*this);}
        b                                                       &operator=(b &A) noexcept
        {
            if      (this != &A)
            {
                b       *B = A.L();

                A::operator=(*B);
                a::operator=(*B);
                B::operator=(*B);

                delete  B;
            }
            
            return  *this;
        }
        b                                                       &operator=(b &&A) noexcept
        {
            if      (this != &A)
            {
                b       *B = std::move(A.L());

                A::operator=(std::move(*B));
                a::operator=(std::move(*B));
                B::operator=(std::move(*B));

                delete  B;
            }
            
            return  *this;
        }
        virtual ~b()                                            noexcept = default;
        /* Override pure virtual polymorphism function */
        void                                                    K(int A) noexcept final override {k = A;}
        void                                                    l() noexcept {g();}
        void                                                    K() noexcept {cout << k << "\n";}
};
class               C
{
    public:
        C()             noexcept = default;
        ~C()            noexcept = default;
        virtual void    A(unsigned int A) noexcept final {e = A;}
        virtual void    A() noexcept final {cout << e << "\n";}
        unsigned int    e;
};
/* This access control default is public */
struct              c
{
    c()                                                                 noexcept = default;
    explicit c(long long A, unsigned long long a, float B, double b)    noexcept : m(A), n(a), O(B), o(b) {}
    explicit c(const c &A)                                              noexcept : m(A.m), n(A.n), O(A.O), o(A.o) {}
    explicit c(c &&A)                                                   noexcept : m(std::move(A.m)), n(std::move(A.n)), O(std::move(A.O)), o(std::move(A.o)) {}
    c                                                                   *M() noexcept {return new c(*this);}
    c                                                                   &operator=(c &A) noexcept
    {
        if      (this != &A)
        {
            c       *a = A.M();
            m       = a->m;
            n       = a->n;
            O       = a->O;
            o       = a->o;

            delete  a;
        }

        return  *this;
    }
    c                                                                   &operator=(c &&A) noexcept
    {
        if      (this != &A)
        {
            c       *a = std::move(A.M());
            m       = std::move(a->m);
            n       = std::move(a->n);
            O       = std::move(a->O);
            o       = std::move(a->o);

            delete  a;
        }

        return  *this;
    }
    virtual ~c()                                                        noexcept = default;
    long long                                                           m;
    void                                                                N(unsigned long long A, double a) noexcept {n = A, o = a;}
    void                                                                N() noexcept {cout << m << "\n" << n << "\n" << setprecision(6) << O << "\n" << setprecision(15) << o << "\n";}
    protected:
        unsigned long long  n;
        float               O;
    private:    double o;
};
struct              D : virtual b, virtual c
{
    explicit D(bool B, char C, unsigned char D, short d, long long E, unsigned long long e, float F, double f)  noexcept : A(B, C, D, d), a(B, C, D, d), b(B, C, D, d), c(E, e, F, f) {}
    explicit D(const D &B)                                                                                      noexcept : A(B), a(B), b(B), c(B) {}
    explicit D(D &&B)                                                                                           noexcept : A(std::move(B)), a(std::move(B)), b(std::move(B)), c(std::move(B)) {}
    D                                                                                                   *P() noexcept {return new D(*this);}
    D                                                                                                   &operator=(D &A) noexcept
    {
        if      (this != &A)
        {
            D       *a = A.P();

            A::operator=(*a);
            a::operator=(*a);
            b::operator=(*a);
            c::operator=(*a);

            delete  a;
        }

        return  *this;
    }
    D                                                                                                   &operator=(D &&A) noexcept
    {
        if      (this != &A)
        {
            D       *a = std::move(A.P());

            A::operator=(std::move(*a));
            a::operator=(std::move(*a));
            b::operator=(std::move(*a));
            c::operator=(std::move(*a));

            delete  a;
        }

        return  *this;
    }
    virtual ~D()                                                                                        noexcept = default;
};
struct              d : virtual D
{
    explicit d(bool B, char C, unsigned char d, short E, long long e, unsigned long long F, float f, double G)  noexcept : A(B, C, d, E), a(B, C, d, E), b(B, C, d, E), c(e, F, f, G), D(B, C, d, E, e, F, f, G) {}
    explicit d(const d &B)                                                                                      noexcept : A(B), a(B), b(B), c(B), D(B) {}
    explicit d(d &&B)                                                                                           noexcept : A(std::move(B)), a(std::move(B)), b(std::move(B)), c(std::move(B)), D(std::move(B)) {}
    d                                                                                                           *p() noexcept {return new d(*this);}
    d                                                                                                           &operator=(d &A) noexcept
    {
        if      (this != &A)
        {
            d       *a = A.p();

            A::operator=(*a);
            a::operator=(*a);
            b::operator=(*a);
            c::operator=(*a);
            D::operator=(*a);

            delete  a;
        }
        
        return  *this;
    }
    d                                                                                                           &operator=(d &&A) noexcept
    {
        if      (this != &A)
        {
            d       *a = std::move(A.p());

            A::operator=(std::move(*a));
            a::operator=(std::move(*a));
            b::operator=(std::move(*a));
            c::operator=(std::move(*a));
            D::operator=(std::move(*a));

            delete  a;
        }
        
        return  *this;
    }
    virtual ~d()                                                                                                noexcept = default;
    static class                                                                                                C *Q;
    static void                                                                                                 q(unsigned int A) noexcept {Q->A(A);}
    static void                                                                                                 q() noexcept {Q->A();}
};
C                   *d::Q;
struct              E
{
        E()             noexcept = default;
        ~E()            noexcept = default;
        union           A
        {
            char        A[16];
            short       a[8];
            int         B[4];
            long long   b[2];
        };
        A               a;
        virtual void    A(char A, char B) noexcept final {a.b[B] = A;}
        virtual void    A(short A, char B) noexcept final {a.b[B] = A;}
        virtual void    A(int A, char B) noexcept final {a.b[B] = A;}
        virtual void    A(long long A, char B) noexcept final {a.b[B] = A;}
        virtual void    A() noexcept final {cout << reinterpret_cast<char*>(&a.b);}
};
struct              e : virtual D, virtual protected d
{
    explicit e(bool B, char C, unsigned char E, short e, long long F, unsigned long long f, float G, double g)  noexcept : A(B, C, E, e), a(B, C, E, e), b(B, C, E, e), c(F, f, G, g), D(B, C, E, e, F, f, G, g), d(B, C, E, e, F, f, G, g) {}
    explicit e(const e &B)                                                                                      noexcept : A(B), a(B), b(B), c(B), D(B), d(B) {}
    explicit e(e &&B)                                                                                           noexcept : A(std::move(B)), a(std::move(B)), b(std::move(B)), c(std::move(B)), D(std::move(B)), d(std::move(B)) {}
    e                                                                                                           &operator=(e &A) noexcept
    {
        if      (this != &A)
        {
            A::operator=(A);
            a::operator=(A);
            b::operator=(A);
            c::operator=(A);
            D::operator=(A);
            d::operator=(A);
        }

        return  *this;
    }
    e                                                                                                           &operator=(e &&A) noexcept
    {
        if      (this != &A)
        {
            A::operator=(std::move(A));
            a::operator=(std::move(A));
            b::operator=(std::move(A));
            c::operator=(std::move(A));
            D::operator=(std::move(A));
            d::operator=(std::move(A));
        }

        return  *this;
    }
    virtual ~e()                                                                                                noexcept = default;
    virtual void                                                R(char A, char a) = 0;
    virtual void                                                R(short A, char a) = 0;
    virtual void                                                R(int A, char a) = 0;
    virtual void                                                R(long long A, char a) = 0;
    virtual void                                                R(float A) noexcept final {O = A;}
    friend class                                                F;
    private:    E r;
};
struct              F : virtual D, virtual protected d, private e
{
    explicit F(bool B, char C, unsigned char E, short F, long long f, unsigned long long G, float g, double H)  noexcept : A(B, C, E, F), a(B, C, E, F), b(B, C, E, F), c(f, G, g, H), D(B, C, E, F, f, G, g, H), d(B, C, E, F, f, G, g, H), e(B, C, E, F, f, G, g, H) {}
    explicit F(const F &B)                                                                                      noexcept : A(B), a(B), b(B), c(B), D(B), d(B), e(B) {}
    explicit F(F &&B)                                                                                           noexcept : A(std::move(B)), a(std::move(B)), b(std::move(B)), c(std::move(B)), D(std::move(B)), d(std::move(B)), e(std::move(B)) {}
    F                                                                                                           *S() noexcept {return new F(*this);}
    F                                                                                                           &operator=(F &A) noexcept
    {
        if      (this != &A)
        {
            F       *a = A.S();
            
            A::operator=(*a);
            a::operator=(*a);
            b::operator=(*a);
            c::operator=(*a);
            D::operator=(*a);
            d::operator=(*a);

            delete  a;
        }

        return  *this;
    }
    F                                                                                                           &operator=(F &&A) noexcept
    {
        if      (this != &A)
        {
            F       *a = std::move(A.S());
            
            A::operator=(std::move(*a));
            a::operator=(std::move(*a));
            b::operator=(std::move(*a));
            c::operator=(std::move(*a));
            D::operator=(std::move(*a));
            d::operator=(std::move(*a));

            delete  a;
        }

        return  *this;
    }
    void                                                                                                        R(char A, char a) noexcept final override {this->r.A(A, a);}
    void                                                                                                        R(short A, char a) noexcept final override {this->r.A(A, a);}
    void                                                                                                        R(int A, char a) noexcept final override {this->r.A(A, a);}
    void                                                                                                        R(long long A, char a) noexcept final override {this->r.A(A, a);}
    void                                                                                                        s() noexcept {N();}
    void                                                                                                        R() noexcept {this->r.A();}
    ~F()                                                                                                        noexcept = default;
};
int             main() noexcept
{
    /* Create class with explicit custom parameter */
    F       A(true, -128, 255, -32768, 0x8000000000000000, 0xffffffffffffffff, 0.999999f, 0.999999999999999);
    /* Shallow copy constructor */
    F       a(A);

    /* Deep copy constructor */
    F       *B = a.S();

    F       b(false, -128, 255, -32768, 1, 0xffffffffffffffff, 0.999999f, 0.999999999999999);
    
    /* Copy assignment */
    b       = *B;

    b.l();

    /* Define static member */
    a::J    = 65535;

    /* Call static function */
    a::j();

    b.K(-2147483648);
    b.K();

    d::Q    = new C();

    d::q(4294967295);
    d::q();
    
    b.s();

    b.R(6278066737626506568, 0);
    b.R(11138535027311, 1);
    b.R();

    F       C(false, 127, 0, 32767, 0x7fffffffffffffff, 0, 0.999999f, 0.999999999999999);
    /* Move constructor */
    F       c(std::move(C));

    F       *D = c.S();

    F       d(true, 127, 0, 32767, 0x7fffffffffffffff, 0, 0.999999f, 0.999999999999999);
    /* Move assignment */
    d       = std::move(*D);

    d.l();

    d.K(2147483647);
    d.K();
    
    d.s();

    d.R(6278066737626506568, 0);
    d.R(11138535027311, 1);
    d.R();

    /* Destroy class with calling destructor */
    delete  D;
    delete  d::Q;
    delete  B;

    ExitProcess(0);
}
