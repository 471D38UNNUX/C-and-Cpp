#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

typedef struct  A
{
    char    A;
    short   a;
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
A               *Destroy(A *A)
{
    LocalFree(A);

    return  NULL;
}
int             main()
{
    srand((unsigned int)time(0));

    A       *N = NULL, *n = NULL, *O = NULL;
    N       = B(N, (char)rand());
    n       = B(n, (char)rand());
    O       = B(O, (char)rand());
    A       *(*o[])(A *a, A *B) = {C, C};
    A       *P = (o[0](N, n), o[1](n, O));

    fprintf_s(stdout, "Result value: %d\n", P->A);
    fprintf_s(stdout, "Logical NOT of o: %s\n", c(n) ? "true" : "false");   // Will print true or false based on the value of P->A
    // Testing the inequality operator
    fprintf_s(stdout, "P != n: %s\n", D(P, n) ? "true" : "false");  // Will print true or false based on inequality of P->A and n->A

    // Testing the modulus operator
    A       *p = d(P, n);
    
    fprintf_s(stdout, "P %% n: %d\n", p->A);  // Print modulus result
    
    // Testing the modulus assignment operator (%=)
    E(P, n);

    fprintf_s(stdout, "P after P %%= n: %d\n", P->A);  // Print updated P->A after %=

    // Testing the bitwise AND operator (&)
    A       *Q = e(P, n);

    fprintf_s(stdout, "P & n: %d\n", Q->A);   // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *q = F(P);

    fprintf_s(stdout, "Memory address of o: %p\n", q);    // Print address of P
    // Testing the logical AND operator (&&)
    fprintf_s(stdout, "P && n: %s\n", f(P, n) ? "true" : "false");  // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    G(P, n);

    fprintf_s(stdout, "P after P &= n: %d\n", P->A);  // Print updated P->A after &=

    // Testing the function call operator ()
    A       *R = g(P, n);

    fprintf_s(stdout, "P(N): %d\n", R->a);  // Print function call result
    // Testing cast operators
    fprintf_s(stdout, "Casting o to int: %d\n", (int)P->A);
    fprintf_s(stdout, "Casting o to bool: %s\n", (bool)P->A ? "true" : "false");

    // Testing multiplication operator
    A       *r = H(P, n);
    
    fprintf_s(stdout, "P * n: %d\n", r->a);

    char    *S = &r->A;

    fprintf_s(stdout, "%d\n", *S);  // Dereferencing r
    
    // Testing multiplication assignment operator
    h(P, n);

    fprintf_s(stdout, "P after P *= n: %d\n", P->A);

    // Testing the addition operator
    A       *s = I(P, n);

    fprintf_s(stdout, "P + n: %d\n", s->a);

    // Testing the unary plus operator
    A       *T = i(P);

    fprintf_s(stdout, "Unary +P: %d\n", T->A);

    A       *t = NULL;
    t       = B(t, 5);

    fprintf_s(stdout, "Before pre-increment: %d\n", t->a);

    J(t);

    fprintf_s(stdout, "After pre-increment: %d\n", t->a);

    A       *U = j(t);

    fprintf_s(stdout, "After post-increment, U->a (original): %d\n", U->a);
    fprintf_s(stdout, "After post-increment, t->a (incremented): %d\n", t->a);

    // Testing the addition assignment operator
    K(P, n);

    fprintf_s(stdout, "P after P += n: %d\n", P->A);

    // Testing the subtraction operator
    A       *u = k(P, n);

    fprintf_s(stdout, "P - n: %d\n", u->a);

    // Testing the unary negation operator
    A       *V = L(P);

    fprintf_s(stdout, "Unary -P: %d\n", V->A);

    A       *v = NULL;
    v       = B(v, 5);

    fprintf_s(stdout, "Before pre-decrement: %d\n", v->a);

    l(v);

    fprintf_s(stdout, "After pre-decrement: %d\n", v->a);

    A       *W = M(v);

    fprintf_s(stdout, "After post-decrement, W->a (original): %d\n", W->a);
    fprintf_s(stdout, "After post-decrement, v->a (decremented): %d\n", v->a);

    // Testing the subtraction assignment operator
    m(P, n);

    fprintf_s(stdout, "P after P -= n: %d\n", P->A);

    N       = Destroy(N);
    n       = Destroy(n);
    O       = Destroy(O);
    p       = Destroy(p);
    Q       = Destroy(Q);
    R       = Destroy(R);
    s       = Destroy(s);
    T       = Destroy(T);
    t       = Destroy(t);
    U       = Destroy(U);
    u       = Destroy(u);
    V       = Destroy(V);
    v       = Destroy(v);
    W       = Destroy(W);

    ExitProcess(0);
}