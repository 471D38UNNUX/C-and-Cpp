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
// Overloading the right shift operator (>>)
A               *n(A *a, A *b)
{
    A       *A = NULL;
    A       = B(A, a->A >> b->A);   // Perform bitwise right shift

    return  A;
}
// Overloading the right shift assignment operator (>>=)
static void     O(A *a, A *B) {a->A >>= B->A;}  // Perform bitwise right shift and assign
static void     Destroy(A *A[], size_t a) {for (size_t B = 0; B < a; B++) LocalFree(A[B]);}
int             main()
{
    srand((unsigned int)_time64(0));

    A       *o = NULL, *P = NULL, *p = NULL;
    o       = B(o, (char)rand());
    P       = B(P, (char)rand());
    p       = B(p, (char)rand());
    A       *(*Q[])(A *a, A *B) = {C, C};
    A       *q = (Q[0](o, P), Q[1](P, p));

    fprintf_s(stdout, "Result value: %d\n", q->A);
    fprintf_s(stdout, "Logical NOT of q: %s\n", q->A ? "true" : "false");   // Will print true or false based on the value of q->A
    // Testing the inequality operator
    fprintf_s(stdout, "q != P: %s\n", q->A != P->A ? "true" : "false"); // Will print true or false based on inequality of q->A and P->A

    // Testing the modulus operator
    A       *R = c(q, P);
    
    fprintf_s(stdout, "q %% P: %d\n", q->A);  // Print modulus result
    
    // Testing the modulus assignment operator (%=)
    D(q, P);

    fprintf_s(stdout, "q after q %%= P: %d\n", q->A);  // Print updated q->A after %=

    // Testing the bitwise AND operator (&)
    A       *r = d(q, P);

    fprintf_s(stdout, "q & P: %d\n", r->A);   // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *S = E(q);

    fprintf_s(stdout, "Memory address of P: %p\n", r);    // Print address of q
    // Testing the logical AND operator (&&)
    fprintf_s(stdout, "q && P: %s\n", q->A && P->A ? "true" : "false");  // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    e(q, P);

    fprintf_s(stdout, "q after q &= P: %d\n", q->A);  // Print updated q->A after &=

    // Testing the function call operator ()
    A       *s = F(q, P);

    fprintf_s(stdout, "q(P): %d\n", s->a);  // Print function call result
    // Testing cast operators
    fprintf_s(stdout, "Casting q to int: %d\n", (int)q->A);
    fprintf_s(stdout, "Casting q to bool: %s\n", (bool)q->A ? "true" : "false");

    // Testing multiplication operator
    A       *T = f(q, P);
    
    fprintf_s(stdout, "q * P: %d\n", T->a);

    char    *t = &T->A;

    fprintf_s(stdout, "Value of s: %d\n", *t);  // Dereferencing T
    
    // Testing multiplication assignment operator
    G(q, P);

    fprintf_s(stdout, "q after q *= P: %d\n", q->A);

    // Testing the addition operator
    A       *U = g(q, P);

    fprintf_s(stdout, "q + P: %d\n", U->a);

    // Testing the unary plus operator
    A       *u = H(q);

    fprintf_s(stdout, "Unary +q: %d\n", u->A);

    A       *V = NULL;
    V       = B(V, 5);

    fprintf_s(stdout, "Before pre-increment: %d\n", V->a);

    h(V);

    fprintf_s(stdout, "After pre-increment: %d\n", V->a);

    A       *v = I(V);

    fprintf_s(stdout, "After post-increment, v->a (original): %d\n", v->a);
    fprintf_s(stdout, "After post-increment, V->a (incremented): %d\n", v->a);

    // Testing the addition assignment operator
    i(q, P);

    fprintf_s(stdout, "q after q += P: %d\n", q->A);

    // Testing the subtraction operator
    A       *W = J(q, P);

    fprintf_s(stdout, "q - P: %d\n", W->a);

    // Testing the unary negation operator
    A       *w = j(q);

    fprintf_s(stdout, "Unary -q: %d\n", w->A);

    A       *X = NULL;
    X       = B(X, 5);

    fprintf_s(stdout, "Before pre-decrement: %d\n", X->a);

    K(X);

    fprintf_s(stdout, "After pre-decrement: %d\n", X->a);

    A       *x = k(X);

    fprintf_s(stdout, "After post-decrement, x->a (original): %d\n", x->a);
    fprintf_s(stdout, "After post-decrement, X->a (decremented): %d\n", X->a);

    // Testing the subtraction assignment operator
    L(q, P);

    fprintf_s(stdout, "q after q -= P: %d\n", q->A);

    A       *Y = NULL;
    Y       = B(Y, 5);

    fprintf_s(stdout, "Value of Y->a: %d\n", Y->a);

    Y->a    = 10;   // Modify a through the overloaded operator

    fprintf_s(stdout, "Updated value of Y->a: %d\n", Y->a);

    A       *y = a();
    A       **Z = &y;
    y->a    = 42;

    fprintf_s(stdout, "y->*a: %d\n", (*Z)->a);  // Outputs: 42

    A       *z = NULL, *AA = NULL;
    z       = B(z, 10);
    AA      = B(AA, 2);
    A       *Aa = l(z, AA);

    fprintf_s(stdout, "Result of z / AA: %d\n", Aa->A);

    A       *AB = NULL, *Ab = NULL;
    AB      = B(AB, 10);
    Ab      = B(Ab, 2);

    fprintf_s(stdout, "Before AB /= Ab: %d\n", AB->A);

    M(AB, Ab);

    fprintf_s(stdout, "After AB /= Ab: %d\n", AB->A);

    A       *AC = NULL, *Ac = NULL;
    AC      = B(AC, 10);
    Ac      = B(Ac, 15);

    fprintf_s(stdout, "AC < Ac: %s\n", AC->A < Ac->A ? "true" : "false");

    A       *AD = NULL;
    AD      = B(AD, 5); // 5 in binary: 00000101
    A       *Ad = m(AD, 2); // Perform left shift by 2 bits, result is 20 (binary: 00010100)

    fprintf_s(stdout, "Ad->A: %d\n", Ad->A);   // Output: 20

    A       *AE = NULL;
    AE      = B(AE, 5); // 5 in binary: 00000101

    fprintf_s(stdout, "Before <<= : %d\n", AE->A);

    N(AE, 2);   // Left shift by 2 bits

    fprintf_s(stdout, "After <<= : %d\n", AE->A);   // Output: 20 (binary: 00010100)

    A       *Ae = NULL, *AF = NULL;
    Ae      = B(Ae, 5);     // 5 in decimal
    AF      = B(AF, 10);    // 10 in decimal

    fprintf_s(stdout, "Ae <= AF: %s\n", Ae->A <= AF->A ? "true" : "false"); // Output: true

    A       *Af = NULL, *AG = NULL;
    Af      = B(Af, 5); // 5 in decimal
    AG      = B(AG, 10);    // 10 in decimal

    fprintf_s(stdout, "Before assignment: Af->a = %d\n", Af->A);    // Output: 5
    fprintf_s(stdout, "Before assignment: AG->a = %d\n", AG->A);    // Output: 10

    memcpy_s(Af, sizeof(A), AG, sizeof(A)); // Assign AG to Af

    fprintf_s(stdout, "After assignment: Af->a = %d\n", Af->A); // Output: 10

    A       *Ag = NULL, *AH = NULL, *Ah = NULL;
    Ag      = B(Ag, 5); // 5 in decimal
    AH      = B(AH, 5); // 5 in decimal
    Ah      = B(Ah, 10);    // 10 in decimal

    fprintf_s(stdout, "Ag == AH: %s\n", Ag->A == AH->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "Ag == Ah: %s\n", Ag->A == Ah->A ? "true" : "false"); // Output: false

    A       *AI = NULL, *Ai = NULL;
    AI      = B(AI, 10);    // 10 in decimal
    Ai      = B(Ai, 5); // 5 in decimal

    fprintf_s(stdout, "AI > Ai: %s\n", AI->A > Ai->A ? "true" : "false");   // Output: true
    fprintf_s(stdout, "Ai > AI: %s\n", Ai->A > AI->A ? "true" : "false");   // Output: false

    A       *AJ = NULL, *Aj = NULL, *AK = NULL;
    AJ      = B(AJ, 10);    // 10 in decimal
    Aj      = B(Aj, 10);    // 10 in decimal
    AK      = B(AK, 5); // 5 in decimal

    fprintf_s(stdout, "AJ >= Aj: %s\n", AJ->A >= Aj->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "AJ >= AK: %s\n", AJ->A >= AK->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "AK >= AJ: %s\n", AK->A >= AJ->A ? "true" : "false"); // Output: false

    A       *Ak = NULL, *AL = NULL, *Al = NULL;
    Ak      = B(Ak, 16);    // 16 in decimal (0b10000)
    AL      = B(AL, 2); // Shift by 2 bits
    Al      = n(Ak, AL);

    fprintf_s(stdout, "16 >> 2 = %d\n", AL->A);
    // Output: 16 >> 2 = 4  (0b10000 >> 2 = 0b100)

    A       *AM = NULL, *Am = NULL;
    AM      = B(AM, 16);    // 16 in decimal (0b10000)
    Am      = B(Am, 2); // Shift by 2 bits

    O(AM, Am);

    fprintf_s(stdout, "16 >>= 2 = %d\n", AM->A);
    // Output: 16 >>= 2 = 4  (0b10000 >> 2 = 0b100)

    A       *AN = NULL;
    AN      = B(AN, 5); // A = 5, a = 0
    short   *An[] = {(short*)&AN->A, &AN->a};
    *An[1]  = 10;   // Set a to 10

    fprintf_s(stdout, "AN[0] = %d\n", *An[0] ? *An[0] : 0); // Access 'A'
    fprintf_s(stdout, "AN[1] = %d\n", *An[1] ? *An[1] : 0); // Access 'a'
    // Out-of-bounds access (returns 0)
    fprintf_s(stdout, "AN[2] = %d\n", *An[2] ? 0 : 0);

    A       *All[] = {o, P, p, R, r, s, U, u, V, W, w, X, x, Y, y, z, AA, Aa, AB, Ab, AC, Ac, AD, AE, Ae, AF, Af, AG, Ag, AH, Ah, AI, Ai, AJ, Aj, AK, Ak, AL, Al, AM, Am, AN};

    Destroy(All, sizeof(All) / sizeof(All[0]));

    ExitProcess(0);
}