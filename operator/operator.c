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
A               *Destroy(A *A)
{
    LocalFree(A);

    return  NULL;
}
int             main()
{
    srand((unsigned int)time(0));

    A       *l = NULL, *M = NULL, *m = NULL;
    l       = B(l, (char)rand());
    M       = B(M, (char)rand());
    m       = B(m, (char)rand());
    A       *(*N[])(A *a, A *B) = {C, C};
    A       *n = (N[0](l, M), N[1](M, m));

    fprintf_s(stdout, "Result value: %d\n", n->A);
    fprintf_s(stdout, "Logical NOT of n: %s\n", c(n) ? "true" : "false");   // Will print true or false based on the value of n->A
    // Testing the inequality operator
    fprintf_s(stdout, "n != M: %s\n", D(n, M) ? "true" : "false");  // Will print true or false based on inequality of n->A and M->A

    // Testing the modulus operator
    A       *O = d(n, M);
    
    fprintf_s(stdout, "n %% M: %d\n", O->A);  // Print modulus result
    
    // Testing the modulus assignment operator (%=)
    E(n, M);

    fprintf_s(stdout, "n after n %%= M: %d\n", n->A);  // Print updated n->A after %=

    // Testing the bitwise AND operator (&)
    A       *o = e(n, M);

    fprintf_s(stdout, "n & M: %d\n", o->A);   // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *P = F(n);

    fprintf_s(stdout, "Memory address of n: %p\n", P);    // Print address of n
    // Testing the logical AND operator (&&)
    fprintf_s(stdout, "n && M: %s\n", f(n, M) ? "true" : "false");  // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    G(n, M);

    fprintf_s(stdout, "n after n &= M: %d\n", n->A);  // Print updated n->A after &=

    // Testing the function call operator ()
    A       *p = g(n, M);

    fprintf_s(stdout, "n(M): %d\n", p->a);  // Print function call result
    // Testing cast operators
    fprintf_s(stdout, "Casting n to int: %d\n", (int)n->A);
    fprintf_s(stdout, "Casting n to bool: %s\n", (bool)n->A ? "true" : "false");

    // Testing multiplication operator
    A       *Q = H(n, M);
    
    fprintf_s(stdout, "n * M: %d\n", Q->a);

    char    *q = &Q->A;

    fprintf_s(stdout, "%d\n", *q);  // Dereferencing Q
    
    // Testing multiplication assignment operator
    h(n, M);

    fprintf_s(stdout, "n after n *= M: %d\n", n->a);

    // Testing the addition operator
    A       *R = I(n, M);

    fprintf_s(stdout, "n + M: %d\n", R->a);

    // Testing the unary plus operator
    A       *r = i(n);

    fprintf_s(stdout, "Unary +n: %d\n", r->A);

    A       *S = NULL;
    S       = B(S, 5);

    fprintf_s(stdout, "Before pre-increment: %d\n", S->a);

    J(S);

    fprintf_s(stdout, "After pre-increment: %d\n", S->a);

    A       *s = j(S);

    fprintf_s(stdout, "After post-increment, s->a (original): %d\n", s->a);
    fprintf_s(stdout, "After post-increment, S->a (incremented): %d\n", S->a);

    // Testing the addition assignment operator
    K(n, M);

    fprintf_s(stdout, "n after n += M: %d\n", n->a);

    // Testing the subtraction operator
    A       *T = k(n, M);

    fprintf_s(stdout, "n - M: %d\n", T->a);

    // Testing the unary negation operator
    A       *t = L(n);

    fprintf_s(stdout, "Unary -n: %d\n", t->A);

    l       = Destroy(l);
    M       = Destroy(M);
    m       = Destroy(m);
    O       = Destroy(O);
    o       = Destroy(o);
    p       = Destroy(p);
    R       = Destroy(R);
    r       = Destroy(r);
    S       = Destroy(S);
    s       = Destroy(s);
    T       = Destroy(T);
    t       = Destroy(t);

    ExitProcess(0);
}