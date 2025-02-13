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

    return  B(NULL, a->A % b->A);   // Compute remainder and return new structure variable
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
// Overloading the address-of operator (&)
A               *d(A *a)
{
    A   *B  = &*a;

    fprintf_s(stdout, "Address-of operator called on object with value: %d\n", B->A);

    return  B;  // Return pointer to the object itself
}
// Overloading the function call operator ()
A               *E(A *a, A *B)
{ 
    fprintf_s(stdout, "Function call operator called: %d + %d = %d\n", a->A, B->A, (short)(a->A + B->A));

    a->a    = (short)(a->A + B->A);

    return  b(NULL, a->A + B->A);   // Return new structure variable with sum
}
// Overloading the pre-increment operator (++A)
static void     e(A *A)
{
    A->a    = A->A; // Update 'a' with the new value
    ++A->a; // Increment 'a' first
}
// Overloading the post-increment operator (A++)
A               *F(A *B)
{
    A       *b = a();

    memcpy_s(b, sizeof(A), B, sizeof(A));   // Store original value
    
    b->a    = B->a; // Update 'a' with the new value
    B->a++; // Increment 'a'
    
    return  b;  // Return original value before increment
}
// Overloading the pre-decrement operator (--A)
static void     f(A *A)
{
    A->a    = A->A; // Store current value in a
    --A->a; // Decrement a first
}
// Overloading the post-decrement operator (A--)
A               *G(A *B)
{
    A       *b = a();

    memcpy_s(b, sizeof(A), B, sizeof(A));   // Store original value
    
    b->a    = B->a; // Update 'a' with the current value
    B->a--; // Decrement 'a'
    
    return  b;  // Return original value before decrement
}
// Overloading the division operator (/)
A               *g(A *a, A *b)
{
    if      (!b->A)
    {
        fprintf_s(stdout, "Warning: Division by zero, returning original value.\n");

        return  a;  // Return original structure variable to prevent error
    }

    return  B(NULL, a->A / b->A);   // Perform division and return new structure variable
}
// Overloading the division assignment operator (/=)
static void     H(A *a, A *B)
{
    if      (!B->A)
    {
        fprintf_s(stdout, "Warning: Division by zero, keeping original value.\n");

        return; // Keep original value to prevent error
    }

    a->A    /= B->A;    // Perform division and update 'A'
}
static void     Destroy(A *A[], size_t a) {for (size_t B = 0; B < a; B++) LocalFree(A[B]);}
int             main()
{
    srand((unsigned int)_time64(0));

    A       *h = B(NULL, (char)rand());
    A       *I = B(NULL, (char)rand());
    A       *i = B(NULL, (char)rand());
    A       *(*J[])(A *a, A *B) = {C, C};
    A       *j = (J[0](h, I), J[1](I, i));

    fprintf_s(stdout, "Result value: %d\n", j->A);
    fprintf_s(stdout, "Logical NOT of j: %s\n", j->A ? "true" : "false");   // Will print true or false based on the value of j->A
    // Testing the inequality operator
    fprintf_s(stdout, "j != I: %s\n", j->A != h->A ? "true" : "false"); // Will print true or false based on inequality of j->A and I->A

    // Testing the modulus operator
    A       *K = c(j, I);
    
    fprintf_s(stdout, "j %% I: %d\n", K->A);  // Print modulus result
    
    // Testing the modulus assignment operator (%=)
    D(j, I);

    fprintf_s(stdout, "j after j %%= I: %d\n", j->A);  // Print updated j->A after %=

    // Testing the bitwise AND operator (&)
    A       *k = B(NULL, j->A & I->A);;

    fprintf_s(stdout, "j & I: %d\n", k->A);   // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *L = d(j);

    fprintf_s(stdout, "Memory address of I: %p\n", L);    // Print address of j
    // Testing the logical AND operator (&&)
    fprintf_s(stdout, "j && I: %s\n", j->A && h->A ? "true" : "false");  // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    j->A    &= I->A;

    fprintf_s(stdout, "j after j &= I: %d\n", j->A);  // Print updated j->A after &=

    // Testing the function call operator ()
    A       *l = E(j, I);

    fprintf_s(stdout, "j(I): %d\n", l->a);  // Print function call result
    // Testing cast operators
    fprintf_s(stdout, "Casting j to int: %d\n", (int)j->A);
    fprintf_s(stdout, "Casting j to bool: %s\n", (bool)j->A ? "true" : "false");

    // Testing multiplication operator
    A       *M = b(NULL, j->A * I->A);
    
    fprintf_s(stdout, "j * I: %d\n", M->a);

    char    *m = &M->A;

    fprintf_s(stdout, "Value of L: %d\n", *m);  // Dereferencing M
    
    // Testing multiplication assignment operator
    j->a    *= I->A;

    fprintf_s(stdout, "j after j *= I: %d\n", j->A);

    // Testing the addition operator
    A       *N = b(NULL, j->A + I->A);

    fprintf_s(stdout, "j + I: %d\n", N->a);

    // Testing the unary plus operator
    A       *n = B(NULL, +j->A);

    fprintf_s(stdout, "Unary +j: %d\n", n->A);

    A       *O = B(NULL, 5);

    fprintf_s(stdout, "Before pre-increment: %d\n", O->a);

    e(O);

    fprintf_s(stdout, "After pre-increment: %d\n", O->a);

    A       *o = F(O);

    fprintf_s(stdout, "After post-increment, o->a (original): %d\n", o->a);
    fprintf_s(stdout, "After post-increment, O->a (incremented): %d\n", o->a);

    // Testing the addition assignment operator
    j->a    += I->A;

    fprintf_s(stdout, "j after j += I: %d\n", j->A);

    // Testing the subtraction operator
    A       *P = b(NULL, j->A - I->A);

    fprintf_s(stdout, "j - I: %d\n", P->a);

    // Testing the unary negation operator
    A       *p = B(NULL, -j->A);

    fprintf_s(stdout, "Unary -j: %d\n", p->A);

    A       *Q = B(NULL, 5);

    fprintf_s(stdout, "Before pre-decrement: %d\n", Q->a);

    f(Q);

    fprintf_s(stdout, "After pre-decrement: %d\n", Q->a);

    A       *q = G(Q);

    fprintf_s(stdout, "After post-decrement, q->a (original): %d\n", q->a);
    fprintf_s(stdout, "After post-decrement, Q->a (decremented): %d\n", Q->a);

    // Testing the subtraction assignment operator
    j->a    -= I->A;

    fprintf_s(stdout, "j after j -= I: %d\n", j->A);

    A       *R = B(NULL, 5);

    fprintf_s(stdout, "Value of R->a: %d\n", R->a);

    R->a    = 10;   // Modify a through the overloaded operator

    fprintf_s(stdout, "Updated value of R->a: %d\n", R->a);

    A       *r = a();
    A       **S = &r;
    r->a    = 42;

    fprintf_s(stdout, "r->*a: %d\n", (*S)->a);  // Outputs: 42

    A       *s = B(NULL, 10);
    A       *T = B(NULL, 2);
    A       *t = g(s, T);

    fprintf_s(stdout, "Result of s / T: %d\n", t->A);

    A       *U = B(NULL, 10);
    A       *u = B(NULL, 2);

    fprintf_s(stdout, "Before U /= u: %d\n", U->A);

    H(U, u);

    fprintf_s(stdout, "After U /= u: %d\n", U->A);

    A       *V = B(NULL, 10);
    A       *v = B(NULL, 15);

    fprintf_s(stdout, "V < v: %s\n", V->A < v->A ? "true" : "false");

    A       *W = B(NULL, 5);    // 5 in binary: 00000101
    A       *w = B(NULL, W->A << 2);    // Perform left shift by 2 bits, result is 20 (binary: 00010100)

    fprintf_s(stdout, "w->A: %d\n", w->A);   // Output: 20

    A       *X = B(NULL, 5);    // 5 in binary: 00000101

    fprintf_s(stdout, "Before <<= : %d\n", X->A);

    X->A <<= 2;    // Left shift by 2 bits

    fprintf_s(stdout, "After <<= : %d\n", X->A);    // Output: 20 (binary: 00010100)

    A       *x = B(NULL, 5);    // 5 in decimal
    A       *Y = B(NULL, 10);   // 10 in decimal

    fprintf_s(stdout, "x <= Y: %s\n", x->A <= Y->A ? "true" : "false"); // Output: true

    A       *y = B(NULL, 5);    // 5 in decimal
    A       *Z = B(NULL, 10);   // 10 in decimal

    fprintf_s(stdout, "Before assignment: y->a = %d\n", y->A);  // Output: 5
    fprintf_s(stdout, "Before assignment: Z->a = %d\n", Z->A);  // Output: 10

    memcpy_s(y, sizeof(A), Z, sizeof(A));   // Assign Z to y

    fprintf_s(stdout, "After assignment: y->a = %d\n", y->A);   // Output: 10

    A       *z = B(NULL, 5);    // 5 in decimal
    A       *AA = B(NULL, 5);   // 5 in decimal
    A       *Aa = B(NULL, 10);  // 10 in decimal

    fprintf_s(stdout, "z == AA: %s\n", z->A == AA->A ? "true" : "false");   // Output: true
    fprintf_s(stdout, "z == Aa: %s\n", z->A == Aa->A ? "true" : "false");   // Output: false

    A       *AB = B(NULL, 10);  // 10 in decimal
    A       *Ab = B(NULL, 5);   // 5 in decimal

    fprintf_s(stdout, "AB > Ab: %s\n", AB->A > Ab->A ? "true" : "false");   // Output: true
    fprintf_s(stdout, "Ab > AB: %s\n", Ab->A > AB->A ? "true" : "false");   // Output: false

    A       *AC = B(NULL, 10);  // 10 in decimal
    A       *Ac = B(NULL, 10);  // 10 in decimal
    A       *AD = B(NULL, 5);   // 5 in decimal

    fprintf_s(stdout, "AC >= Ac: %s\n", AC->A >= Ac->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "AC >= AD: %s\n", AC->A >= AD->A ? "true" : "false"); // Output: true
    fprintf_s(stdout, "AD >= AC: %s\n", AD->A >= AC->A ? "true" : "false"); // Output: false

    A       *Ad = B(NULL, 16);  // 16 in decimal (0b10000)
    A       *AE = B(NULL, 2);   // Shift by 2 bits
    A       *Ae = B(NULL, Ad->A >> AE->A);

    fprintf_s(stdout, "16 >> 2 = %d\n", Ae->A);
    // Output: 16 >> 2 = 4  (0b10000 >> 2 = 0b100)

    A       *AF = B(NULL, 16);    // 16 in decimal (0b10000)
    A       *Af = B(NULL, 2); // Shift by 2 bits

    AF->A >>= Af->A;

    fprintf_s(stdout, "16 >>= 2 = %d\n", AF->A);
    // Output: 16 >>= 2 = 4  (0b10000 >> 2 = 0b100)

    A       *AG = B(NULL, 5);   // A = 5, a = 0
    short   *Ag[] = {(short*)&AG->A, &AG->a};
    *Ag[1]  = 10;   // Set a to 10

    fprintf_s(stdout, "AG[0] = %d\n", *Ag[0] ? *Ag[0] : 0); // Access 'A'
    fprintf_s(stdout, "AG[1] = %d\n", *Ag[1] ? *Ag[1] : 0); // Access 'a'
    // Out-of-bounds access (returns 0)
    fprintf_s(stdout, "AG[2] = %d\n", *Ag[2] ? 0 : 0);

    A       *AH = B(NULL, 5);
    A       *Ah = B(NULL, 3);
    A       *AI = B(NULL, AH->A ^ Ah->A);   // 5 ^ 3 = 6

    fprintf_s(stdout, "AH ^ Ah: %d\n", AI->A);

    AH->A   ^= Ah->A;   // AH ^= Ah

    fprintf_s(stdout, "AH after AH ^= Ah: %d\n", AH->A);

    A       *Ai = B(NULL, 5);
    A       *AJ = B(NULL, 3);
    A       *Aj = B(NULL, Ai->A | AJ->A);   // 5 | 3 = 7

    fprintf_s(stdout, "Ai | AJ: %d\n", Aj->A);

    Ai->A   |= AJ->A;   // Ai |= AJ

    fprintf_s(stdout, "Ai after Ai |= AJ: %d\n", Ai->A);

    A       *AK = B(NULL, 5);
    A       *Ak = B(NULL, 0);

    if      (AK->A || Ak->A) fprintf_s(stdout, "Logical OR is true\n");
    else    fprintf_s(stdout, "Logical OR is false\n");

    A       *AL = B(NULL, 5);
    A       *Al = B(NULL, ~AL->A);

    fprintf_s(stdout, "%d\n", Al->A);

    A       *All[] = {h, I, j, K, k, l, N, n, O, P, p, Q, q, R, r, s, T, t, U, u, V, v, W, X, x, Y, y, Z, z, AA, Aa, AB, Ab, AC, Ac, AD, Ad, AE, Ae, AF, Af, AG, AH, Ah, Ai, AJ, Aj, AK, Ak, AL, Al};

    Destroy(All, sizeof(All) / sizeof(All[0]));

    ExitProcess(0);
}