#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

typedef struct  A
{
    char        A;
    short       a;
}               A;
// Constructor
A               *a()
{
    A       *a = LocalAlloc(LPTR, sizeof(A));

    if      (!a) ExitProcess(1);

    return  a;
}
A               *B(A *A, char B)
{
    A       = a();
    A->A    = B;

    return  A;
}
A               *b(A *A, short B)
{
    A       = a();
    A->a    = B;

    return  A;
}
// Overloading the comma operator
A               *C(A *a, A *B)
{
    fprintf_s(stdout, "Comma operator called: %d, %d\n", a->A, B->A);

    return      B;  // Return the right-hand operand
}
// Overloading the logical NOT operator (!)
bool            c(A *A) {return !A->A ? 1 : 0;} // Return true if 'A' is 0, else false
// Overloading the inequality operator (!=)
bool            D(A *a, A *B) {return a->A != B->A;}    // Compare the 'A' values for inequality
// Overloading the modulus operator (%)
A               *d(A *B, A *b)
{
    if      (!b->A)
    {
        fprintf_s(stdout, "Warning: Modulus by zero, returning original value.\n");

        return  B;  // Return original value to prevent error
    }

    A       *A = a();
    A->A    = B->A % b->A;

    return  A;  // Compute remainder and return new structure variable
}
// Overloading the modulus assignment operator (%=)
static void     E(A *a, A *B)
{
    if      (!B->A)
    {
        fprintf_s(stdout, "Warning: Modulus by zero, returning original value.\n");

        return; // Return original structure variable to prevent error
    }

    a->A    %= B->A;    // Compute and update 'A'
}
// Overloading the bitwise AND operator (&)
A               *e(A *B, A *b)
{
    A       *A = a();
    A->A    = B->A & b->A;

    return  A;  // Perform bitwise AND and return new structure variable
}
// Overloading the address-of operator (&)
A               *F(A *a)
{
    A   *B  = &*a;

    fprintf_s(stdout, "Address-of operator called on object with value: %d\n", B->A);

    return  B;  // Return pointer to the object itself
}
// Overloading the logical AND operator (&&)
bool            f(A *a, A *B) {return a->A && B->A;}    // Logical AND of 'A' values
// Overloading the bitwise AND assignment operator (&=)
static void     G(A *a, A *B) {a->A &= B->A;}   // Perform bitwise AND and update 'A'
// Overloading the function call operator ()
A               *g(A *a, A *B)
{
    short   C = a->A + B->A;
    
    fprintf_s(stdout, "Function call operator called: %d + %d = %d\n", a->A, B->A, C);

    a->a    = C;
    A       *A = NULL;
    A       = b(A, C);

    return  A;  // Return new structure variable with sum
}
// Overloading the multiplication operator (*)
A               *H(A *B, A *b)
{
    A       *A = a();
    A->a    = B->A * b->A;

    return  A;
}
// Overloading the multiplication assignment operator (*=)
static void     h(A *a, A *B) {a->a = a->A * B->A;}
// Overloading the addition operator (+)
A               *I(A *B, A *b)
{
    A       *A = a();
    A->a    = B->A + b->A;

    return  A;
}
// Overloading the unary plus operator (+)
A               *i(A *B)
{
    A           *A = a();
    A->A        = B->A;

    return      A;
}
// Overloading the pre-increment operator (++A)
static void     J(A *A)
{
    A->a    = A->A; // Update 'a' with the new value
    ++A->a; // Increment 'a' first
}
// Overloading the post-increment operator (A++)
A               *j(A *B)
{
    A       *b = a();

    memcpy(b, B, sizeof(A));    // Store original value
    
    b->a    = B->a; // Update 'a' with the new value
    B->a++; // Increment 'a'
    
    return  b;  // Return original value before increment
}
// Overloading the addition assignment operator (+=)
static void     K(A *a, A *B) {a->a = a->A + B->A;}
// Overloading the subtraction operator (-)
A               *k(A *B, A *b)
{
    A       *A = a();
    A->a    = B->A - b->A;

    return  A;
}
// Overloading the unary negation operator (-)
A               *L(A *B)
{
    A           *A = a();
    A->A        = -B->A;

    return      A;
}
// Overloading the pre-decrement operator (--A)
static void     l(A *A)
{
    A->a    = A->A; // Store current value in a
    --A->a; // Decrement a first
}
// Overloading the post-decrement operator (A--)
A               *M(A *B)
{
    A       *b = a();

    memcpy(b, B, sizeof(A));    // Store original value
    
    b->a    = B->a; // Update 'a' with the current value
    B->a--; // Decrement 'a'
    
    return  b;  // Return original value before decrement
}
// Overloading the subtraction assignment operator (-=)
static void     m(A *a, A *B) {a->a = a->A - B->A;}
// Overloading the division operator (/)
A               *N(A *B, A *b)
{
    if      (!b->A)
    {
        fprintf_s(stdout, "Warning: Division by zero, returning original value.\n");

        return  B;  // Return original structure variable to prevent error
    }

    A       *A = a();
    A->A    = B->A / b->A;

    return  A;  // Perform division and return new structure variable
}
A               *Destroy(A *A)
{
    LocalFree(A);

    return  NULL;
}
int             main()
{
    srand((unsigned int)time(0));

    A       *n = NULL, *O = NULL, *o = NULL;
    n       = B(n, (char)rand());
    O       = B(O, (char)rand());
    o       = B(o, (char)rand());
    A       *(*P[])(A *a, A *B) = {C, C};
    A       *p = (P[0](n, O), P[1](O, o));

    fprintf_s(stdout, "Result value: %d\n", p->A);
    fprintf_s(stdout, "Logical NOT of o: %s\n", c(p) ? "true" : "false");   // Will print true or false based on the value of p->A
    // Testing the inequality operator
    fprintf_s(stdout, "p != O: %s\n", D(p, O) ? "true" : "false");  // Will print true or false based on inequality of p->A and n->A

    // Testing the modulus operator
    A       *Q = d(p, O);
    
    fprintf_s(stdout, "p %% O: %d\n", Q->A);  // Print modulus result
    
    // Testing the modulus assignment operator (%=)
    E(p, O);

    fprintf_s(stdout, "p after p %%= O: %d\n", p->A);  // Print updated p->A after %=

    // Testing the bitwise AND operator (&)
    A       *q = e(p, O);

    fprintf_s(stdout, "p & O: %d\n", q->A);   // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *R = F(p);

    fprintf_s(stdout, "Memory address of o: %p\n", R);    // Print address of p
    // Testing the logical AND operator (&&)
    fprintf_s(stdout, "p && O: %s\n", f(p, O) ? "true" : "false");  // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    G(p, O);

    fprintf_s(stdout, "p after p &= O: %d\n", p->A);  // Print updated p->A after &=

    // Testing the function call operator ()
    A       *r = g(p, O);

    fprintf_s(stdout, "p(O): %d\n", r->a);  // Print function call result
    // Testing cast operators
    fprintf_s(stdout, "Casting P to int: %d\n", (int)p->A);
    fprintf_s(stdout, "Casting P to bool: %s\n", (bool)p->A ? "true" : "false");

    // Testing multiplication operator
    A       *S = H(p, O);
    
    fprintf_s(stdout, "p * O: %d\n", S->a);

    char    *s = &S->A;

    fprintf_s(stdout, "%d\n", *s);  // Dereferencing S
    
    // Testing multiplication assignment operator
    h(p, O);

    fprintf_s(stdout, "p after p *= O: %d\n", p->A);

    // Testing the addition operator
    A       *T = I(p, O);

    fprintf_s(stdout, "p + O: %d\n", T->a);

    // Testing the unary plus operator
    A       *t = i(p);

    fprintf_s(stdout, "Unary +p: %d\n", t->A);

    A       *U = NULL;
    U       = B(U, 5);

    fprintf_s(stdout, "Before pre-increment: %d\n", U->a);

    J(U);

    fprintf_s(stdout, "After pre-increment: %d\n", U->a);

    A       *u = j(U);

    fprintf_s(stdout, "After post-increment, u->a (original): %d\n", u->a);
    fprintf_s(stdout, "After post-increment, U->a (incremented): %d\n", U->a);

    // Testing the addition assignment operator
    K(p, O);

    fprintf_s(stdout, "p after p += O: %d\n", p->A);

    // Testing the subtraction operator
    A       *V = k(p, O);

    fprintf_s(stdout, "p - O: %d\n", V->a);

    // Testing the unary negation operator
    A       *v = L(p);

    fprintf_s(stdout, "Unary -p: %d\n", v->A);

    A       *W = NULL;
    W       = B(W, 5);

    fprintf_s(stdout, "Before pre-decrement: %d\n", W->a);

    l(W);

    fprintf_s(stdout, "After pre-decrement: %d\n", W->a);

    A       *w = M(W);

    fprintf_s(stdout, "After post-decrement, w->a (original): %d\n", w->a);
    fprintf_s(stdout, "After post-decrement, W->a (decremented): %d\n", W->a);

    // Testing the subtraction assignment operator
    m(p, O);

    fprintf_s(stdout, "p after p -= O: %d\n", p->A);

    A       *X = NULL;
    X       = B(X, 5);

    fprintf_s(stdout, "Value of X->a: %d\n", X->a);

    X->a    = 10;   // Modify a through the overloaded operator

    fprintf_s(stdout, "Updated value of X->a: %d\n", X->a);

    A       *x = a();
    A       **Y = &x;
    x->a    = 42;

    fprintf_s(stdout, "x->*a: %d\n", (*Y)->a);  // Outputs: 42

    A       *y = NULL, *Z = NULL;
    y       = B(y, 10);
    Z       = B(Z, 2);
    A       *z = N(y, Z);

    fprintf_s(stdout, "Result of y / Z: %d\n", z->A);

    n       = Destroy(n);
    O       = Destroy(O);
    o       = Destroy(o);
    Q       = Destroy(Q);
    q       = Destroy(q);
    r       = Destroy(r);
    T       = Destroy(T);
    t       = Destroy(t);
    U       = Destroy(U);
    u       = Destroy(u);
    V       = Destroy(V);
    v       = Destroy(v);
    W       = Destroy(W);
    w       = Destroy(w);
    X       = Destroy(X);
    x       = Destroy(x);
    y       = Destroy(y);
    Z       = Destroy(Z);
    z       = Destroy(z);

    ExitProcess(0);
}