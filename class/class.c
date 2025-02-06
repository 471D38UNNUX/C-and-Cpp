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
/* This function as destructor */
static void     e(A *A[], size_t a) {for (size_t B = 0; B < a; B++) CoTaskMemFree(A[B]);}
static void     F(a *A) {fprintf(stdout, "%u\n", A->a);}
a               *f(A *A, bool B, char b, unsigned char C, short c)
{
    A       = E(A, B, b, C, c);

    a       *D = CoTaskMemAlloc(sizeof(a));

    if      (!D) ExitProcess(1);

    D->A    = A;
    D->B    = F;

    return  D;
}
static void     G(A *A[], size_t B, a *b[], size_t C)
{
    e(A, B);

    for (size_t c = 0; c < C; c++) CoTaskMemFree(b[c]);
}
static void     g(A *A, unsigned char a) {A->C = a;}
B               *H(A *A, a *a, bool b, char C, unsigned char c, short D)
{
    a       = f(A, b, C, c, D);

    B       *d= CoTaskMemAlloc(sizeof(B));

    if      (!d) ExitProcess(1);

    d->A    = a->A;
    d->a    = a;
    d->b    = g;

    return  d;
}
static void     h(A *A[], size_t b, a *C[], size_t c, B *D[], size_t d)
{
    G(A, b, C, c);

    for (size_t E = 0; E < d; E++) CoTaskMemFree(D[E]);
}
static void     I(struct B *A, int a) {A->C = a;}
static void     i(A *A) {A->B(A);}
static void     J(B *A) {fprintf(stdout, "%d\n", A->C);}
b               *j(A *A, a *a, B *B, bool C, char c, unsigned char D, short d)
{
    B       = H(A, a, C, c, D, d);

    b       *E = CoTaskMemAlloc(sizeof(b));

    if      (!E) ExitProcess(1);

    E->A    = B->a->A;
    E->a    = B->a;
    E->B    = B;
    /* Override polymorphism function pointer */
    E->B->B = E->b;
    E->b    = I;
    E->C    = i;
    E->c    = J;

    return  E;
}
static void     K(A *A[], size_t C, a *c[], size_t D, B *d[], size_t E, b *e[], size_t F)
{
    h(A, C, c, D, d, E);

    for (size_t f = 0; f < F; f++) CoTaskMemFree(e[f]);
}
static void     k(struct C *A, unsigned int a) {A->B = a;}
static void     L(struct C *A) {fprintf(stdout, "%u\n", A->B);}
C               *l()
{
    C       *A = CoTaskMemAlloc(sizeof(C));

    if      (!A) ExitProcess(1);
    
    A->A    = k;
    A->a    = L;

    return  A;
};
static void     M(C *A[], size_t a) {for (size_t B = 0; B < a; B++) CoTaskMemFree(A[B]);}
int             main()
{
    A       *A = NULL;
    a       *a = NULL;
    B       *B = NULL;
    /* Create struct with explicit custom parameter */
    b       *c = j(A, a, B, true, -128, 255, -32768);
    /* Shallow copy constructor */
    b       *D = c;
    /* Deep copy constructor */
    b       *d = CoTaskMemAlloc(sizeof(b));
    
    if      (!d) ExitProcess(1);
    
    /*
    Copy assignment.
    Shallow copy constructor. */
    memcpy_s(d, sizeof(b), D, sizeof(b));

    b       *E = j(A, a, B, false, -128, 255, -32768);
    
    /*
    Copy assignment.
    Deep copy constructor. */
    memcpy_s(E, sizeof(b), d, sizeof(b));

    E->C(E->A);
    
    E->a->a = 65535;
    
    E->a->B(E->a);
    
    E->b(E->B, -2147483648);
    
    E->c(E->B);

    C       *e = l();

    e->A(e, 4294967295);

    e->a(e);

    b       *F = j(A, a, B, false, 127, 0, 32767);
    /* Move constructor */
    b       *f = F;
    F       = NULL;
    b       *G = CoTaskMemAlloc(sizeof(b));
    
    if      (!G) ExitProcess(1);

    /* Move assignment */
    memcpy_s(G, sizeof(b), f, sizeof(b));

    f       = NULL;
    b       *g = j(A, a, B, true, 127, 0, 32767);

    /* Move assignment */
    memcpy_s(g, sizeof(b), G, sizeof(b));

    G       = NULL;

    g->C(g->A);
    
    g->a->a = 0;
    
    g->a->B(g->a);
    
    g->b(g->B, 2147483647);
    
    g->c(g->B);

    /* Destroy struct with calling destructor */
    
    struct A    *H[] = {A};
    struct a    *h[] = {a};
    struct B    *I[] = {B};
    struct b    *i[] = {c, d, E, g};
    struct C    *J[] = {e};

    K(H, sizeof(H) / sizeof(H[0]), h, sizeof(h) / sizeof(h[0]), I, sizeof(I) / sizeof(I[0]), i, sizeof(i) / sizeof(i[0]));

    M(J, sizeof(J) / sizeof(J[0]));

    ExitProcess(0);
}
