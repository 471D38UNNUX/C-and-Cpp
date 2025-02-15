#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

typedef struct  A
{
    char        A;
    short       a;
    int         B;
}               A;
// Constructor
A               *a()
{
    A       *a = LocalAlloc(LPTR, sizeof(A));

    if      (!a) ExitProcess(1);

    fprintf_s(stdout, "operator new called, size: %lld\n", sizeof(A));

    return  a;  // Directly calling global operator new
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
A               *C(A *A, int B)
{
    A       = a();
    A->B    = B;

    return  A;
}
// Overloading the comma operator
A               *c(A *a, A *B)
{
    fprintf_s(stdout, "Comma operator called: %d, %d\n", a->A, B->A);

    return      B;  // Return the right-hand operand
}
// Overloading the modulus operator (%)
A               *D(A *a, A *b)
{
    if      (!b->A)
    {
        fprintf_s(stdout, "Warning: Modulus by zero, returning original value.\n");

        return  a;  // Return original value to prevent error
    }

    return  B(NULL, a->A % b->A);   // Compute remainder and return new structure variable
}
// Overloading the modulus assignment operator (%=)
static void     d(A *a, A *B)
{
    if      (!B->A)
    {
        fprintf_s(stdout, "Warning: Modulus by zero, returning original value.\n");

        return; // Return original structure variable to prevent error
    }

    a->A    %= B->A;    // Compute and update 'A'
}
// Overloading the address-of operator (&)
A               *E(A *a)
{
    A   *B  = &*a;

    fprintf_s(stdout, "Address-of operator called on object with value: %d\n", B->A);

    return  B;  // Return pointer to the object itself
}
// Overloading the function call operator ()
A               *e(A *a, A *B)
{ 
    fprintf_s(stdout, "Function call operator called: %d + %d = %d\n", a->A, B->A, (short)(a->A + B->A));

    a->a    = (short)(a->A + B->A);

    return  b(NULL, a->A + B->A);   // Return new structure variable with sum
}
// Overloading the pre-increment operator (++A)
static void     F(A *A)
{
    A->a    = A->A; // Update 'a' with the new value
    ++A->a; // Increment 'a' first
}
// Overloading the post-increment operator (A++)
A               *f(A *B)
{
    A       *b = a();

    memcpy_s(b, sizeof(A), B, sizeof(A));   // Store original value
    
    b->a    = B->a; // Update 'a' with the new value
    B->a++; // Increment 'a'
    
    return  b;  // Return original value before increment
}
// Overloading the pre-decrement operator (--A)
static void     G(A *A)
{
    A->a    = A->A; // Store current value in a
    --A->a; // Decrement a first
}
// Overloading the post-decrement operator (A--)
A               *g(A *B)
{
    A       *b = a();

    memcpy_s(b, sizeof(A), B, sizeof(A));   // Store original value
    
    b->a    = B->a; // Update 'a' with the current value
    B->a--; // Decrement 'a'
    
    return  b;  // Return original value before decrement
}
// Overloading the division operator (/)
A               *H(A *a, A *b)
{
    if      (!b->A)
    {
        fprintf_s(stdout, "Warning: Division by zero, returning original value.\n");

        return  a;  // Return original structure variable to prevent error
    }

    return  B(NULL, a->A / b->A);   // Perform division and return new structure variable
}
// Overloading the division assignment operator (/=)
static void     h(A *a, A *B)
{
    if      (!B->A)
    {
        fprintf_s(stdout, "Warning: Division by zero, keeping original value.\n");

        return; // Keep original value to prevent error
    }

    a->A    /= B->A;    // Perform division and update 'A'
}
static void     I(A *A[], size_t a)
{
    for (size_t B = 0; B < a; B++)
    {
        fprintf_s(stdout, "operator delete called\n");

        LocalFree(A[B]);    // Directly calling global operator delete
    }
}
// Implicit conversion to int
static int      i(A *A)
{
    fprintf(stdout, "Converting to int\n");

    return  A->B;
}
// Explicit conversion to double
static double   J(A *A)
{
    fprintf(stdout, "Converting to double\n");

    return  (double)A->B + 0.5;
}
// Conversion to void* (pointer)
static void     *j(A *A)
{
    fprintf(stdout, "Converting to void*\n");

    return  (void*)A;
}
int             main()
{
    srand((unsigned int)_time64(0));

    A       *K = B(NULL, (char)rand());
    A       *k = B(NULL, (char)rand());
    A       *L = B(NULL, (char)rand());
    A       *(*l[])(A *a, A *B) = {c, c};
    A       *M = (l[0](K, k), l[1](k, L));

    fprintf_s(stdout, "Result value: %d\n", M->A);
    fprintf_s(stdout, "Logical NOT of M: %s\n", M->A ? "true" : "false");   // Will print true or false based on the value of M->A
    // Testing the inequality operator
    fprintf_s(stdout, "M != k: %s\n", M->A != K->A ? "true" : "false"); // Will print true or false based on inequality of M->A and k->A

    // Testing the modulus operator
    A       *m = D(M, k);
    
    fprintf_s(stdout, "M %% k: %d\n", m->A);  // Print modulus result
    
    // Testing the modulus assignment operator (%=)
    d(M, k);

    fprintf_s(stdout, "M after M %%= k: %d\n", M->A);  // Print updated M->A after %=

    // Testing the bitwise AND operator (&)
    A       *N = B(NULL, M->A & k->A);;

    fprintf_s(stdout, "M & k: %d\n", N->A);   // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *n = E(M);

    fprintf_s(stdout, "Memory address of k: %p\n", n);    // Print address of M
    // Testing the logical AND operator (&&)
    fprintf_s(stdout, "M && k: %s\n", M->A && K->A ? "true" : "false");  // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    M->A    &= k->A;

    fprintf_s(stdout, "M after M &= k: %d\n", M->A);  // Print updated M->A after &=

    // Testing the function call operator ()
    A       *O = e(M, k);

    fprintf_s(stdout, "M(k): %d\n", O->a);  // Print function call result
    // Testing cast operators
    fprintf_s(stdout, "Casting M to int: %d\n", (int)M->A);
    fprintf_s(stdout, "Casting M to bool: %s\n", (bool)M->A ? "true" : "false");

    // Testing multiplication operator
    A       *o = b(NULL, M->A * k->A);
    
    fprintf_s(stdout, "M * k: %d\n", o->a);

    char    *P = &o->A;

    fprintf_s(stdout, "Value of n: %d\n", *P);  // Dereferencing o
    
    // Testing multiplication assignment operator
    M->a    *= k->A;

    fprintf_s(stdout, "M after M *= k: %d\n", M->A);

    // Testing the addition operator
    A       *p = b(NULL, M->A + k->A);

    fprintf_s(stdout, "M + k: %d\n", p->a);

    // Testing the unary plus operator
    A       *Q = B(NULL, +M->A);

    fprintf_s(stdout, "Unary +M: %d\n", Q->A);

    A       *q = B(NULL, 5);

    fprintf_s(stdout, "Before pre-increment: %d\n", q->a);

    F(q);

    fprintf_s(stdout, "After pre-increment: %d\n", q->a);

    A       *R = f(q);

    fprintf_s(stdout, "After post-increment, R->a (original): %d\n", R->a);
    fprintf_s(stdout, "After post-increment, q->a (incremented): %d\n", R->a);

    // Testing the addition assignment operator
    M->a    += k->A;

    fprintf_s(stdout, "M after M += k: %d\n", M->A);

    // Testing the subtraction operator
    A       *r = b(NULL, M->A - k->A);

    fprintf_s(stdout, "M - k: %d\n", r->a);

    // Testing the unary negation operator
    A       *S = B(NULL, -M->A);

    fprintf_s(stdout, "Unary -M: %d\n", S->A);

    A       *s = B(NULL, 5);

    fprintf_s(stdout, "Before pre-decrement: %d\n", s->a);

    G(s);

    fprintf_s(stdout, "After pre-decrement: %d\n", s->a);

    A       *T = g(s);

    fprintf_s(stdout, "After post-decrement, T->a (original): %d\n", T->a);
    fprintf_s(stdout, "After post-decrement, s->a (decremented): %d\n", s->a);

    // Testing the subtraction assignment operator
    M->a    -= k->A;

    fprintf_s(stdout, "M after M -= k: %d\n", M->A);

    A       *t = B(NULL, 5);

    fprintf_s(stdout, "Value of t->a: %d\n", t->a);

    t->a    = 10;   // Modify a through the overloaded operator

    fprintf_s(stdout, "Updated value of t->a: %d\n", t->a);

    A       *U = a();
    A       **u = &U;
    U->a    = 42;

    fprintf_s(stdout, "U->*a: %d\n", (*u)->a);  // Outputs: 42

    A       *V = B(NULL, 10);
    A       *v = B(NULL, 2);
    A       *W = H(V, v);

    fprintf_s(stdout, "Result of V / v: %d\n", W->A);

    A       *w = B(NULL, 10);
    A       *X = B(NULL, 2);

    fprintf_s(stdout, "Before w /= X: %d\n", w->A);

    h(w, X);

    fprintf_s(stdout, "After w /= X: %d\n", w->A);

    A       *x = B(NULL, 10);
    A       *Y = B(NULL, 15);

    fprintf_s(stdout, "x < Y: %s\n", x->A < Y->A ? "true" : "false");

    A       *y = B(NULL, 5);    // 5 in binary: 00000101
    A       *Z = B(NULL, y->A << 2);    // Perform left shift by 2 bits, result is 20 (binary: 00010100)

    fprintf_s(stdout, "Z->A: %d\n", Z->A);   // Output: 20

    A       *z = B(NULL, 5);    // 5 in binary: 00000101

    fprintf_s(stdout, "Before <<= : %d\n", z->A);

    z->A    <<= 2;    // Left shift by 2 bits

    fprintf_s(stdout, "After <<= : %d\n", z->A);    // Output: 20 (binary: 00010100)

    A       *AA = B(NULL, 5);   // 5 in decimal
    A       *Aa = B(NULL, 10);  // 10 in decimal

    fprintf_s(stdout, "AA <= Aa: %s\n", AA->A <= Aa->A ? "true" : "false"); // Output: true

    A       *AB = B(NULL, 5);   // 5 in decimal
    A       *Ab = B(NULL, 10);  // 10 in decimal

    fprintf_s(stdout, "Before assignment: AB->a = %d\n", AB->A);    // Output: 5
    fprintf_s(stdout, "Before assignment: Ab->a = %d\n", Ab->A);    // Output: 10

    memcpy_s(AB, sizeof(A), Ab, sizeof(A));  // Assign Ab to AB

    fprintf_s(stdout, "After assignment: AB->a = %d\n", AB->A); // Output: 10

    A       *AC = B(NULL, 5);   // 5 in decimal
    A       *Ac = B(NULL, 5);   // 5 in decimal
    A       *AD = B(NULL, 10);  // 10 in decimal

    fprintf_s(stdout, "AC == Ac: %s\n", AC->A == Ac->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "AC == AD: %s\n", AC->A == AD->A ? "true" : "false"); // Output: false

    A       *Ad = B(NULL, 10);  // 10 in decimal
    A       *AE = B(NULL, 5);   // 5 in decimal

    fprintf_s(stdout, "Ad > AE: %s\n", Ad->A > AE->A ? "true" : "false");   // Output: true
    fprintf_s(stdout, "AE > Ad: %s\n", AE->A > Ad->A ? "true" : "false");   // Output: false

    A       *Ae = B(NULL, 10);  // 10 in decimal
    A       *AF = B(NULL, 10);  // 10 in decimal
    A       *Af = B(NULL, 5);   // 5 in decimal

    fprintf_s(stdout, "Ae >= AF: %s\n", Ae->A >= AF->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "Ae >= Af: %s\n", Ae->A >= Af->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "Af >= Ae: %s\n", Af->A >= Ae->A ? "true" : "false"); // Output: false

    A       *AG = B(NULL, 16);  // 16 in decimal (0b10000)
    A       *Ag = B(NULL, 2);   // Shift by 2 bits
    A       *AH = B(NULL, AG->A >> Ag->A);

    fprintf_s(stdout, "16 >> 2 = %d\n", AH->A);
    // Output: 16 >> 2 = 4  (0b10000 >> 2 = 0b100)

    A       *Ah = B(NULL, 16);    // 16 in decimal (0b10000)
    A       *AI = B(NULL, 2); // Shift by 2 bits

    Ah->A   >>= AI->A;

    fprintf_s(stdout, "16 >>= 2 = %d\n", Ah->A);
    // Output: 16 >>= 2 = 4  (0b10000 >> 2 = 0b100)

    A       *Ai = B(NULL, 5);   // A = 5, a = 0
    short   *AJ[] = {(short*)&Ai->A, &Ai->a};
    *AJ[1]  = 10;   // Set a to 10

    fprintf_s(stdout, "Ai[0] = %d\n", *AJ[0] ? *AJ[0] : 0); // Access 'A'
    fprintf_s(stdout, "Ai[1] = %d\n", *AJ[1] ? *AJ[1] : 0); // Access 'a'
    // Out-of-bounds access (returns 0)
    fprintf_s(stdout, "Ai[2] = %d\n", *AJ[2] ? 0 : 0);

    A       *Aj = B(NULL, 5);
    A       *AK = B(NULL, 3);
    A       *Ak = B(NULL, Aj->A ^ AK->A);   // 5 ^ 3 = 6

    fprintf_s(stdout, "Aj ^ AK: %d\n", Ak->A);

    Aj->A   ^= AK->A;   // Aj ^= AK

    fprintf_s(stdout, "Aj after Aj ^= AK: %d\n", Aj->A);

    A       *AL = B(NULL, 5);
    A       *Al = B(NULL, 3);
    A       *AM = B(NULL, AL->A | Al->A);   // 5 | 3 = 7

    fprintf_s(stdout, "AL | Al: %d\n", AM->A);

    AL->A   |= Al->A;   // AL |= Al

    fprintf_s(stdout, "AL after AL |= Al: %d\n", AL->A);

    A       *Am = B(NULL, 5);
    A       *AN = B(NULL, 0);

    if      (Am->A || AN->A) fprintf_s(stdout, "Logical OR is true\n");
    else    fprintf_s(stdout, "Logical OR is false\n");

    A       *An = B(NULL, 5);
    A       *AO = B(NULL, ~An->A);

    fprintf_s(stdout, "%d\n", AO->A);

    A       *Ao = a();
    A       *AP = C(NULL, 42);
    int     Ap = i(AP); // Implicit conversion
    double  AQ = J(AP); // Explicit conversion
    void    *Aq = j(AP);    // Pointer conversion

    fprintf_s(stdout, "Ap: %d\n", Ap);
    fprintf_s(stdout, "AQ: %g\n", AQ);
    fprintf_s(stdout, "Aq: %p\n", Aq);

    A       *AR[] = {K, k, M, m, N, O, p, Q, q, r, S, s, T, t, U, V, v, W, w, X, x, Y, y, z, AA, Aa, AB, Ab, AC, Ac, AD, Ad, AE, Ae, AF, Af, AG, Ag, AH, Ah, AI, Ai, Aj, AK, AL, Al, AM, Am, AN, An, AO, Ao, AP};

    I(AR, sizeof(AR) / sizeof(AR[0]));

    ExitProcess(0);
}