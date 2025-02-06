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
// Overloading the modulus operator (%)
A               *c(A *a, A *b)
{
    if      (!b->A)
    {
        fprintf_s(stdout, "Warning: Modulus by zero, returning original value.\n");

        return  a;  // Return original value to prevent error
    }

    A       *A = NULL;
    A       = B(A, a->A % b->A);

    return  A;  // Compute remainder and return new structure variable
}
// Overloading the modulus assignment operator (%=)
static void     D(A *a, A *B)
{
    if      (!B->A)
    {
        fprintf_s(stdout, "Warning: Modulus by zero, returning original value.\n");

        return; // Return original structure variable to prevent error
    }

    a->A    %= B->A;    // Compute and update 'A'
}
// Overloading the bitwise AND operator (&)
A               *d(A *a, A *b)
{
    A       *A = NULL;
    A       = B(A, a->A & b->A);

    return  A;  // Perform bitwise AND and return new structure variable
}
// Overloading the address-of operator (&)
A               *E(A *a)
{
    A   *B  = &*a;

    fprintf_s(stdout, "Address-of operator called on object with value: %d\n", B->A);

    return  B;  // Return pointer to the object itself
}
// Overloading the bitwise AND assignment operator (&=)
static void     e(A *a, A *B) {a->A &= B->A;}   // Perform bitwise AND and update 'A'
// Overloading the function call operator ()
A               *F(A *a, A *B)
{ 
    fprintf_s(stdout, "Function call operator called: %d + %d = %d\n", a->A, B->A, (short)(a->A + B->A));

    a->a    = (short)(a->A + B->A);
    A       *A = NULL;
    A       = b(A, a->A + B->A);

    return  A;  // Return new structure variable with sum
}
// Overloading the multiplication operator (*)
A               *f(A *a, A *B)
{
    A       *A = NULL;
    A       = b(A, a->A * B->A);

    return  A;
}
// Overloading the multiplication assignment operator (*=)
static void     G(A *a, A *B) {a->a = a->A * B->A;}
// Overloading the addition operator (+)
A               *g(A *a, A *B)
{
    A       *A = NULL;
    A       = b(A, a->A + B->A);

    return  A;
}
// Overloading the unary plus operator (+)
A               *H(A *a)
{
    A           *A = NULL;
    A           = B(A, +a->A);

    return      A;
}
// Overloading the pre-increment operator (++A)
static void     h(A *A)
{
    A->a    = A->A; // Update 'a' with the new value
    ++A->a; // Increment 'a' first
}
// Overloading the post-increment operator (A++)
A               *I(A *B)
{
    A       *b = a();

    memcpy_s(b, sizeof(A), B, sizeof(A));   // Store original value
    
    b->a    = B->a; // Update 'a' with the new value
    B->a++; // Increment 'a'
    
    return  b;  // Return original value before increment
}
// Overloading the addition assignment operator (+=)
static void     i(A *a, A *B) {a->a = a->A + B->A;}
// Overloading the subtraction operator (-)
A               *J(A *a, A *B)
{
    A       *A = NULL;
    A       = b(A, a->A - B->A);

    return  A;
}
// Overloading the unary negation operator (-)
A               *j(A *a)
{
    A           *A = NULL;
    A           = B(A, -a->A);

    return      A;
}
// Overloading the pre-decrement operator (--A)
static void     K(A *A)
{
    A->a    = A->A; // Store current value in a
    --A->a; // Decrement a first
}
// Overloading the post-decrement operator (A--)
A               *k(A *B)
{
    A       *b = a();

    memcpy_s(b, sizeof(A), B, sizeof(A));   // Store original value
    
    b->a    = B->a; // Update 'a' with the current value
    B->a--; // Decrement 'a'
    
    return  b;  // Return original value before decrement
}
// Overloading the subtraction assignment operator (-=)
static void     L(A *a, A *B) {a->a = a->A - B->A;}
// Overloading the division operator (/)
A               *l(A *a, A *b)
{
    if      (!b->A)
    {
        fprintf_s(stdout, "Warning: Division by zero, returning original value.\n");

        return  a;  // Return original structure variable to prevent error
    }

    A       *A = NULL;
    A       = B(A, a->A / b->A);

    return  A;  // Perform division and return new structure variable
}
// Overloading the division assignment operator (/=)
static void     M(A *a, A *B)
{
    if      (!B->A)
    {
        fprintf_s(stdout, "Warning: Division by zero, keeping original value.\n");

        return; // Keep original value to prevent error
    }

    a->A    /= B->A;    // Perform division and update 'A'
}
// Overloading the shift left operator (<<)
A               *m(A *a, int b)
{
    A       *A = NULL;
    A       = B(A, a->A << b);  // Perform bitwise left shift and return new structure variable

    return  A;
}
// Overloading the shift left assignment operator (<<=)
static void     N(A *A, int a) {A->A <<= a;}    // Perform bitwise left shift and update 'A'
static void     Destroy(A *A[], size_t a) {for (size_t B = 0; B < a; B++) LocalFree(A[B]);}
int             main()
{
    srand((unsigned int)time(0));

    A       *O = NULL, *o = NULL, *P = NULL;
    O       = B(O, (char)rand());
    o       = B(o, (char)rand());
    P       = B(P, (char)rand());
    A       *(*p[])(A *a, A *B) = {C, C};
    A       *Q = (p[0](O, o), p[1](o, P));

    fprintf_s(stdout, "Result value: %d\n", Q->A);
    fprintf_s(stdout, "Logical NOT of Q: %s\n", Q->A ? "true" : "false");   // Will print true or false based on the value of Q->A
    // Testing the inequality operator
    fprintf_s(stdout, "Q != o: %s\n", Q->A != o->A ? "true" : "false"); // Will print true or false based on inequality of Q->A and o->A

    // Testing the modulus operator
    A       *q = c(Q, o);
    
    fprintf_s(stdout, "Q %% o: %d\n", q->A);  // Print modulus result
    
    // Testing the modulus assignment operator (%=)
    D(Q, o);

    fprintf_s(stdout, "Q after Q %%= o: %d\n", Q->A);  // Print updated Q->A after %=

    // Testing the bitwise AND operator (&)
    A       *R = d(Q, o);

    fprintf_s(stdout, "Q & o: %d\n", R->A);   // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *r = E(Q);

    fprintf_s(stdout, "Memory address of o: %p\n", r);    // Print address of Q
    // Testing the logical AND operator (&&)
    fprintf_s(stdout, "Q && o: %s\n", Q->A && o->A ? "true" : "false");  // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    e(Q, o);

    fprintf_s(stdout, "Q after Q &= o: %d\n", Q->A);  // Print updated Q->A after &=

    // Testing the function call operator ()
    A       *S = F(Q, o);

    fprintf_s(stdout, "Q(O): %d\n", S->a);  // Print function call result
    // Testing cast operators
    fprintf_s(stdout, "Casting Q to int: %d\n", (int)Q->A);
    fprintf_s(stdout, "Casting Q to bool: %s\n", (bool)Q->A ? "true" : "false");

    // Testing multiplication operator
    A       *s = f(Q, o);
    
    fprintf_s(stdout, "Q * o: %d\n", s->a);

    char    *T = &s->A;

    fprintf_s(stdout, "Value of s: %d\n", *T);  // Dereferencing s
    
    // Testing multiplication assignment operator
    G(Q, o);

    fprintf_s(stdout, "Q after Q *= o: %d\n", Q->A);

    // Testing the addition operator
    A       *t = g(Q, o);

    fprintf_s(stdout, "Q + o: %d\n", t->a);

    // Testing the unary plus operator
    A       *U = H(Q);

    fprintf_s(stdout, "Unary +Q: %d\n", U->A);

    A       *u = NULL;
    u       = B(u, 5);

    fprintf_s(stdout, "Before pre-increment: %d\n", u->a);

    h(u);

    fprintf_s(stdout, "After pre-increment: %d\n", u->a);

    A       *V = I(u);

    fprintf_s(stdout, "After post-increment, V->a (original): %d\n", V->a);
    fprintf_s(stdout, "After post-increment, u->a (incremented): %d\n", u->a);

    // Testing the addition assignment operator
    i(Q, o);

    fprintf_s(stdout, "Q after Q += o: %d\n", Q->A);

    // Testing the subtraction operator
    A       *v = J(Q, o);

    fprintf_s(stdout, "Q - o: %d\n", v->a);

    // Testing the unary negation operator
    A       *W = j(Q);

    fprintf_s(stdout, "Unary -Q: %d\n", W->A);

    A       *w = NULL;
    w       = B(w, 5);

    fprintf_s(stdout, "Before pre-decrement: %d\n", w->a);

    K(w);

    fprintf_s(stdout, "After pre-decrement: %d\n", w->a);

    A       *X = k(w);

    fprintf_s(stdout, "After post-decrement, X->a (original): %d\n", X->a);
    fprintf_s(stdout, "After post-decrement, w->a (decremented): %d\n", w->a);

    // Testing the subtraction assignment operator
    L(Q, o);

    fprintf_s(stdout, "Q after Q -= o: %d\n", Q->A);

    A       *x = NULL;
    x       = B(x, 5);

    fprintf_s(stdout, "Value of x->a: %d\n", x->a);

    x->a    = 10;   // Modify a through the overloaded operator

    fprintf_s(stdout, "Updated value of x->a: %d\n", x->a);

    A       *Y = a();
    A       **y = &Y;
    Y->a    = 42;

    fprintf_s(stdout, "Y->*a: %d\n", (*y)->a);  // Outputs: 42

    A       *Z = NULL, *z = NULL;
    Z       = B(Z, 10);
    z       = B(z, 2);
    A       *AA = l(Z, z);

    fprintf_s(stdout, "Result of Z / z: %d\n", AA->A);

    A       *Aa = NULL, *AB = NULL;
    Aa      = B(Aa, 10);
    AB      = B(AB, 2);

    fprintf_s(stdout, "Before Aa /= AB: %d\n", Aa->A);

    M(Aa, AB);

    fprintf_s(stdout, "After Aa /= AB: %d\n", Aa->A);

    A       *Ab = NULL, *AC = NULL;
    Ab      = B(Ab, 10);
    AC      = B(AC, 15);

    fprintf_s(stdout, "Ab < AC: %s\n", Ab->A < AC->A ? "true" : "false");

    A       *Ac = NULL;
    Ac      = B(Ac, 5); // 5 in binary: 00000101
    A       *AD = m(Ac, 2); // Perform left shift by 2 bits, result is 20 (binary: 00010100)

    fprintf_s(stdout, "Ac: %d\n", AD->A);   // Output: 20

    A       *Ad = NULL;
    Ad      = B(Ad, 5); // 5 in binary: 00000101

    fprintf_s(stdout, "Before <<= : %d\n", Ad->A);

    N(Ad, 2);   // Left shift by 2 bits

    fprintf_s(stdout, "After <<= : %d\n", Ad->A);   // Output: 20 (binary: 00010100)

    A       *AE = NULL, *Ae = NULL;
    AE      = B(AE, 5);     // 5 in decimal
    Ae      = B(Ae, 10);    // 10 in decimal

    fprintf_s(stdout, "AE <= Ae: %s\n", AE->A <= Ae->A ? "true" : "false"); // Output: true

    A       *AF = NULL, *Af = NULL;
    AF      = B(AF, 5); // 5 in decimal
    Af      = B(Af, 10);    // 10 in decimal

    fprintf_s(stdout, "Before assignment: AF->a = %d\n", AF->A);    // Output: 5
    fprintf_s(stdout, "Before assignment: Af->a = %d\n", Af->A);    // Output: 10

    memcpy_s(AF, sizeof(A), Af, sizeof(A)); // Assign Af to AF

    fprintf_s(stdout, "After assignment: AF->a = %d\n", AF->A); // Output: 10

    A       *All[] = {O, o, P, q, R, S, t, U, u, V, W, w, X, x, Y, Z, z, AA, Aa, AB, Ab, AC, Ac, Ad, AE, Ae, AF, Af};

    Destroy(All, sizeof(All) / sizeof(All[0]));

    ExitProcess(0);
}