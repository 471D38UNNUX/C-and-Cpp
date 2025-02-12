#pragma comment(lib, "Ole32.lib")

#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

/* Hierarchical inheritance into struct a, struct B, and struct b */
typedef struct  A
{
    bool            A;
    /* Function pointer for define, overload polymorphism, and override polymorphism function inside struct */
    void            (*a)(struct A *A, char a, short B);
    void            (*B)(struct A *A);
    char            b;
    unsigned char   C;
    short           c;
}               A;
typedef struct  a
{
    /* Single inheritance from struct A */
    A               *A;
    unsigned short  a;
    void            (*B)(struct a *A);
}               a;
typedef struct  B
{
    /*
    Hybrid inheritance.
    Multilevel inheritance from struct A and struct a.
    Multiple inheritance from struct A and struct a. */
    A       *A;
    a       *a;
    void    (*B)(struct B *A, int a);
    void    (*b)(A *A, unsigned char a);
    int     C;
}               B;
typedef struct  b
{
    A       *A;
    a       *a;
    B       *B;
    void    (*b)(struct B *A, int a), (*C)(A *A), (*c)(B *A);
}               b;
typedef struct  C
{
    void            (*A)(struct C *A, unsigned int a), (*a)(struct C *A);
    unsigned int    B;
}               C;
static void     c(struct A *A, char a, short B) {A->b = a, A->c = B;}
/* This function as default constructor */
static void     D(struct A *A) {fprintf(stdout, "%d\n%d\n%u\n%d\n", A->A, A->b, A->C, A->c);}
A               *d()
{
    A       *a = CoTaskMemAlloc(sizeof(A));

    if      (!a) ExitProcess(1);

    /* Define function pointer for struct A */
    a->a    = c;
    a->B    = D;

    return  a;
}
/* This function as constructor with custom parameter */
A               *E(A *A, bool a, char B, unsigned char b, short c)
{
    A       = d();
    /* Shallow copy constructor */
    A->A    = a;
    A->b    = B;
    A->C    = b;
    A->c    = c;

    return  A;
}
static void     e(a *A) {fprintf(stdout, "%u\n", A->a);}
a               *F(A *A, bool B, char b, unsigned char C, short c)
{
    A       = E(A, B, b, C, c);

    a       *D = CoTaskMemAlloc(sizeof(a));

    if      (!D) ExitProcess(1);

    D->A    = A;
    D->B    = e;

    return  D;
}
/* This function as destructor */
static void     f(A *A, a *a)
{
    CoTaskMemFree(A);
    CoTaskMemFree(a);
}
static void     G(A *A, unsigned char a) {A->C = a;}
B               *g(A *A, a *a, bool b, char C, unsigned char c, short D)
{
    a       = F(A, b, C, c, D);

    B       *d= CoTaskMemAlloc(sizeof(B));

    if      (!d) ExitProcess(1);

    d->A    = a->A;
    d->a    = a;
    d->b    = G;

    return  d;
}
static void     H(A *A, a *a, B *B)
{
    f(A, a);

    CoTaskMemFree(B);
}
static void     h(struct B *A, int a) {A->C = a;}
static void     I(A *A) {A->B(A);}
static void     i(B *A) {fprintf(stdout, "%d\n", A->C);}
b               *J(A *A, a *a, B *B, bool C, char c, unsigned char D, short d)
{
    B       = g(A, a, C, c, D, d);

    b       *E = CoTaskMemAlloc(sizeof(b));

    if      (!E) ExitProcess(1);

    E->A    = B->a->A;
    E->a    = B->a;
    E->B    = B;
    /* Override polymorphism function pointer */
    E->B->B = E->b;
    E->b    = h;
    E->C    = I;
    E->c    = i;

    return  E;
}
static void     j(A *A, a *a, B *B, b *b[], size_t C)
{
    H(A, a, B);

    for (size_t c = 0; c < C; c++) CoTaskMemFree(b[c]);
}
static void     K(struct C *A, unsigned int a) {A->B = a;}
static void     k(struct C *A) {fprintf(stdout, "%u\n", A->B);}
C               *L()
{
    C       *A = CoTaskMemAlloc(sizeof(C));

    if      (!A) ExitProcess(1);
    
    A->A    = K;
    A->a    = k;

    return  A;
};
int             main()
{
    /* Create struct with explicit custom parameter */
    b       *A = J(NULL, NULL, NULL, true, -128, 255, -32768);
    /* Shallow copy constructor */
    b       *a = A;
    /* Deep copy constructor */
    b       *B = CoTaskMemAlloc(sizeof(b));
    
    if      (!B) ExitProcess(1);
    
    /*
    Copy assignment.
    Shallow copy constructor. */
    memcpy_s(B, sizeof(b), a, sizeof(b));

    b       *c = J(NULL, NULL, NULL, false, -128, 255, -32768);
    
    /*
    Copy assignment.
    Deep copy constructor. */
    memcpy_s(c, sizeof(b), B, sizeof(b));

    c->C(c->A);
    
    c->a->a = 65535;
    
    c->a->B(c->a);
    
    c->b(c->B, -2147483648);
    
    c->c(c->B);

    C       *D = L();

    D->A(D, 4294967295);

    D->a(D);

    b       *d = J(NULL, NULL, NULL, false, 127, 0, 32767);
    /* Move constructor */
    b       *E = d;
    d       = NULL;
    b       *e = CoTaskMemAlloc(sizeof(b));
    
    if      (!e) ExitProcess(1);

    /* Move assignment */
    memcpy_s(e, sizeof(b), E, sizeof(b));

    E       = NULL;
    b       *F = J(NULL, NULL, NULL, true, 127, 0, 32767);

    /* Move assignment */
    memcpy_s(g, sizeof(b), e, sizeof(b));

    e       = NULL;

    F->C(F->A);
    
    F->a->a = 0;
    
    F->a->B(F->a);
    
    F->b(F->B, 2147483647);
    
    F->c(F->B);

    /* Destroy struct with calling destructor */
    CoTaskMemFree(e);

    struct b    *i[] = {A, B, c, F};

    j(NULL, NULL, NULL, i, sizeof(i) / sizeof(i[0]));

    ExitProcess(0);
}
