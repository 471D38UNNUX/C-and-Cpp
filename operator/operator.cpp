#include <iostream>
#include <random>
#include <Windows.h>

using namespace std;

class   A
{
    public:
        // Constructor
        A()                 noexcept = default;
        explicit A(char A)  noexcept : a(A), B(0), b(0) {}
        explicit A(short A) noexcept : a(0), B(A), b(0) {}
        explicit A(int A)   noexcept : a(0), B(0), b(A) {}
        // Overloading the comma operator
        A                   operator,(const A &A) noexcept
        {
            cout    << "Comma operator called: " << static_cast<short>(a) << ", " << static_cast<short>(A.a) << endl;

            return  A;  // Return the right-hand operand
        };
        ~A()                noexcept = default;
        // Overloading the logical NOT operator (!)
        bool                operator!() const noexcept {return !a;} // Return true if 'a' is 0, else false
        // Overloading the inequality operator (!=)
        bool                operator!=(const A &A) const noexcept {return a != A.a;}    // Compare the 'a' values for inequality
        // Overloading the modulus operator (%)
        A                   operator%(const A &B) const noexcept
        {
            if      (!B.a)
            {
                cout    << "Warning: Modulus by zero, returning original value." << endl;
            
                return  *this;  // Return original object to prevent error
            }
            
            return  A(static_cast<char>(a % B.a));  // Compute remainder and return new object
        }
        // Overloading the modulus assignment operator (%=)
        A                   &operator%=(const A &A) noexcept
        {
            if      (!A.a)
            {
                cout    << "Warning: Modulus by zero, keeping original value." << endl;
                
                return  *this;  // Keep original value to prevent error
            }
            
            a       %= A.a; // Compute and update 'a'
            
            return  *this;
        }
        // Overloading the bitwise AND operator (&)
        A                   operator&(const A &B) const noexcept {return A(static_cast<char>(a & B.a));}   // Perform bitwise AND and return new object
        // Overloading the address-of operator (&)
        A                   *operator&() noexcept
        {
            cout    << "Address-of operator called on object with value: " << static_cast<short>(a) << endl;
            
            return   this;  // Return pointer to the object itself
        }
        // Overloading the logical AND operator (&&)
        bool                operator&&(const A &A) const noexcept {return a && A.a;}    // Logical AND of 'a' values
        // Overloading the bitwise AND assignment operator (&=)
        A                   &operator&=(const A &A) noexcept
        {
            a       &= A.a; // Perform bitwise AND and update 'a'
            
            return   *this;
        }
        // Overloading the function call operator ()
        A                   operator()(const A &b) noexcept
        {
            B       = static_cast<short>(a + b.a);

            cout    << "Function call operator called: " << static_cast<short>(a) << " + " << static_cast<short>(b.a) << " = " << B << endl;

            return  A(B);   // Return new object with sum
        }
        // Overloading explicit cast operator to int
        explicit operator   int() const noexcept {return static_cast<int>(a);}
        // Overloading explicit cast operator to bool
        explicit operator   bool() const noexcept {return a;}
        // Overloading the multiplication operator (*)
        A                   operator*(const A &a) const noexcept {return  A(static_cast<short>(this->a * a.a));}
        // Overloading the pointer dereference operator (*)
        char                operator*() const noexcept {return a;}
        // Overloading the multiplication assignment operator (*=)
        A                   &operator*=(const A &A) noexcept
        {
            B       = a * A.a;

            return  *this;
        }
        // Overloading the addition operator (+)
        A                   operator+(const A &a) const noexcept {return A(static_cast<short>(this->a + a.a));}
        // Overloading the unary plus operator (+)
        A                   operator+() const noexcept {return A(a);}
        // Overloading the pre-increment operator (++A)
        A                   &operator++() noexcept
        {
            B       = a;    // Update 'B' with the new value
            ++B;    // Increment 'B' first

            return  *this;  // Return updated object
        }
        // Overloading the post-increment operator (A++)
        A                   operator++(int) noexcept
        {
            A       A = *this;  // Store original value
            A.B     = B;    // Update 'B' with the new value
            B++;    // Increment 'B'
            return  A;  // Return original value before increment
        }
        // Overloading the addition assignment operator (+=)
        A                   &operator+=(const A &A) noexcept
        {
            B       = static_cast<short>(a + A.a);

            return  *this;
        }
        // Overloading the subtraction operator (-)
        A                   operator-(const A &a) const noexcept {return A(static_cast<short>(this->a - a.a));}
        // Overloading the unary negation operator (-)
        A                   operator-() const noexcept {return A(static_cast<char>(-a));}
        // Overloading the pre-decrement operator (--A)
        A                   &operator--() noexcept
        {
            B       = a;    // Store current value in B
            --B;    // Decrement B first
            
            return  *this;  // Return updated object
        }
        // Overloading the post-decrement operator (A--)
        A                   operator--(int) noexcept
        {
            A       A = *this;  // Store original value
            A.B     = B;    // Update 'B' with the current value
            B--;    // Decrement 'B'

            return  A;  // Return original value before decrement
        }
        // Overloading the subtraction assignment operator (-=)
        A                   &operator-=(const A &A) noexcept
        {
            B       = static_cast<short>(a - A.a);

            return  *this;
        }
        // Overloading the member selection operator (->)
        A                   *operator->() noexcept {return this;}   // Return pointer to the current object
        // Overloading the pointer-to-member selection operator (->*)
        template            <typename a>
        a                   operator->*(a A::*A) const noexcept {return this->*A;}
        // Overloading the division operator (/)
        A                   operator/(const A &B) const noexcept
        {
            if      (!B.a)
            {
                cout    << "Warning: Division by zero, returning original value." << endl;
            
                return  *this;  // Return original object to prevent error
            }
            
            return  A(static_cast<char>(a / B.a));  // Perform division and return new object
        }
        // Overloading the division assignment operator (/=)
        A                   &operator/=(const A &A) noexcept
        {
            if      (!A.a)
            {
                cout    << "Warning: Division by zero, keeping original value." << endl;

                return  *this;  // Keep original value to prevent error
            }
            a       /= A.a; // Perform division and update 'a'

            return  *this;
        }
        // Overloading the less than operator (<)
        bool                operator<(const A &A) const noexcept {return a < A.a;}  // Compare the 'a' values
        // Overloading the shift left operator (<<)
        A                   operator<<(int b) const noexcept {return A(static_cast<char>(a << b));} // Perform bitwise left shift and return new object
        // Overloading the shift left assignment operator (<<=)
        A                   &operator<<=(int A) noexcept
        {
            a       <<= A;  // Perform bitwise left shift and update 'a'

            return  *this;
        }
        // Overloading the less than or equal to operator (<=)
        bool                operator<=(const A &A) const noexcept {return a <= A.a;}    // Compare the 'a' values for less than or equal to
        // Overloading the assignment operator (=)
        A                   &operator=(const A& A) noexcept
        {
            if      (this != &A)    // Prevent self-assignment
            {
                a = A.a;    // Copy the 'a' value
                B = A.B;    // Copy the 'B' value
            }
            return  *this;  // Return the current object to allow chaining
        }
        // Overloading the equality operator (==)
        bool                operator==(const A &A) const noexcept {return a == A.a && B == A.B;}    // Compare both 'a' and 'B' values
        // Overloading the greater than operator (>)
        bool                operator>(const A &A) const noexcept {return a > A.a;}  // Compare based on 'a' value
        // Overloading the greater than or equal to operator (>=)
        bool                operator>=(const A &A) const noexcept {return a >= A.a;}    // Compare based on 'a' value
        // Overloading the right shift operator (>>)
        A                   operator>>(const A &B) const noexcept {return A(static_cast<char>(a >> B.a));}  // Perform bitwise right shift
        // Overloading the right shift assignment operator (>>=)
        A                   &operator>>=(const A &A) noexcept
        {
            a       >>= A.a;    // Perform bitwise right shift and assign

            return  *this;
        }
        // Overloading the array subscript operator []
        short               &operator[](size_t A) noexcept
        {
            static short    b;

            switch          (A)
            {
                case 0:
                    b       = a;

                    return  b;
                case 1:
                    return B;
                default:
                    b       = 0;  // Return reference to a static variable for out-of-bounds access
            
                    return  b;
            }        
        }
        // Overloading the array subscript operator [] (const version)
        const short         &operator[](size_t A) const noexcept
        {
            static const short  b = 0, C = a;
            
            switch              (A)
            {
                case 0:
                    return C;
                case 1:
                    return B;
                default:
                    return  b;
            }
        }
        // Overloading the bitwise XOR operator (^)
        A                   operator^(const A &B) const noexcept {return A(static_cast<char>(a ^ B.a));}
        // Overloading the bitwise XOR assignment operator (^=)
        A                   &operator^=(const A &A) noexcept
        {
            a       ^= A.a; // Perform bitwise XOR and update 'a'
            
            return  *this;
        }
        // Overloading the bitwise OR operator (|)
        A                   operator|(const A &B) const noexcept {return A(static_cast<char>(a | B.a));}
        // Overloading the bitwise OR assignment operator (|=)
        A                   &operator|=(const A &A) noexcept
        {
            a       |= A.a; // Perform bitwise OR and update 'a'

            return  *this;
        }
        // Overloading the logical OR operator (||)
        bool                operator||(const A &A) const noexcept {return a || A.a;}
        // Overloading the one's complement operator (~)
        A                   operator~() const noexcept {return A(static_cast<char>(~a));}
        void                operator delete(void *A)
        {
            cout        << "operator delete called" << endl;

            ::operator  delete(A);  // Directly calling global operator delete
        }
        void                *operator new(size_t A)
        {
            cout    << "operator new called, size: " << A << endl;

            return  ::operator new(A);  // Directly calling global operator new
        }
        // Implicit conversion to int
        operator            int()
        {
            cout    << "Converting to int" << endl;

            return  b;
        }
        // Explicit conversion to double
        explicit            operator double()
        {
            cout    << "Converting to double" << endl;

            return  static_cast<double>(b) + 0.5;
        }
        // Conversion to void* (pointer)
        operator            void*()
        {
            cout    << "Converting to void*" << endl;

            return  this;
        }
        char                a;
        short               B;
        int                 b;
};
mt19937 a(_time64(nullptr));
uniform_int_distribution<int>B(-128, 127);
int     main() noexcept
{
    A       b(static_cast<char>(B(a)));
    A       C(static_cast<char>(B(a)));
    A       c(static_cast<char>(B(a)));
    A       D = (b, C, c);

    cout    << "Result value: " << static_cast<short>(D.a) << endl;
    cout    << "Logical NOT of D: " << (!D ? "true" : "false") << endl; // Will print true or false based on the value of D.a
    // Testing the inequality operator
    cout    << "D != C: " << (D != C ? "true" : "false") << endl;  // Will print true or false based on inequality of D.a and C.a
    
    // Testing the modulus operator
    A       d = D % C;

    cout    << "D % C: " << static_cast<short>(d.a) << endl;  // Print modulus result

    // Testing the modulus assignment operator (%=)
    D       %= C;

    cout    << "D after D %= C: " << static_cast<short>(D.a) << endl;   // Print updated D.a after %=

    // Testing the bitwise AND operator (&)
    A       e = D & C;
    
    cout    << "D & C: " << static_cast<short>(e.a) << endl;    // Print bitwise AND result

    // Testing the address-of operator (&)
    A       *F = &D;

    cout    << "Memory address of D: " << F << endl;    // Print address of D
    // Testing the logical AND operator (&&)
    cout    << "D && C: " << (D && C ? "true" : "false") << endl;   // Logical AND result

    // Testing the bitwise AND assignment operator (&=)
    D       &= C;

    cout    << "D after D &= C: " << static_cast<short>(D.a) << endl;   // Print updated D.a after &=

    // Testing the function call operator ()
    A       f = D(C);
    
    cout    << "D(C) result: " << f.B << endl;  // Print function call result

    // Testing cast operators
    cout    << "Casting D to int: " << static_cast<int>(D) << endl;
    cout    << "Casting D to bool: " << (static_cast<bool>(D) ? "true" : "false") << endl;

    // Testing multiplication operator
    A       G = D * C;

    cout    << "D * C: " << G.B << endl;
    cout    << "Value of G: " << static_cast<short>(*G) << endl;    // Dereferencing G
    
    // Testing multiplication assignment operator
    D       *= C;
    
    cout    << "D after D *= C: " << static_cast<short>(D.B) << endl;

    // Testing the addition operator
    A       g = D + C;

    cout    << "D + C: " << g.B << endl;

    // Testing the unary plus operator
    A       H = +D;
    
    cout    << "Unary +D: " << static_cast<short>(H.a) << endl;

    A       h(static_cast<char>(5));

    cout    << "Before pre-increment: " << h.B << endl;

    ++h;

    cout    << "After pre-increment: " << h.B << endl;

    A       I = h++;    // Post-increment

    cout    << "After post-increment, I.B (original): " << I.B << endl;
    cout    << "After post-increment, h.B (incremented): " << h.B << endl;

    // Testing the addition assignment operator
    D       += C;

    cout    << "D after D += C: " << D.B << endl;

    // Testing the subtraction operator
    A       i = D - C;

    cout    << "D - C: " << i.B << endl;

    // Testing the unary negation operator
    A       J = -D;
    
    cout    << "Unary -D: " << static_cast<short>(J.a) << endl;

    A       j(static_cast<char>(5));

    cout    << "Before pre-decrement: " << j.B << endl;

    --j;

    cout    << "After pre-decrement: " << j.B << endl;

    A       K = j--;    // Post-decrement

    cout    << "After post-decrement, K.B (original): " << K.B << endl;
    cout    << "After post-decrement, j.B (decremented): " << j.B << endl;

    // Testing the subtraction assignment operator
    D       -= C;

    cout    << "D after D -= C: " << D.B << endl;

    A       k(static_cast<char>(5));

    cout    << "Value of k->B: " << k->B << endl;

    k->B    = 10;   // Modify B through the overloaded operator

    cout    << "Updated value of k->B: " << k->B << endl;

    A       L;
    short   A::*l = &A::B;
    L.*l    = 42;

    cout    << "L->*l: " << L->*l << endl;  // Outputs: 42

    A       M(static_cast<char>(10));
    A       m(static_cast<char>(2));
    A       N = M / m;

    cout    << "Result of M / m: " << static_cast<short>(N.a) << endl;

    A       n(static_cast<char>(10));
    A       O(static_cast<char>(2));

    cout    << "Before n /= O: " << static_cast<short>(n.a) << endl;

    n       /= O;

    cout    << "After n /= O: " << static_cast<short>(n.a) << endl;

    A       o(static_cast<char>(10));
    A       P(static_cast<char>(15));

    cout    << "o < P: " << (o < P ? "true" : "false") << endl;

    A       p(static_cast<char>(5));    // 5 in binary: 00000101
    A       Q = p << 2; // Perform left shift by 2 bits, result is 20 (binary: 00010100)

    cout    << "Q.a: " << static_cast<short>(Q.a) << endl; // Output: 20

    A       q(static_cast<char>(5));    // 5 in binary: 00000101

    cout    << "Before <<= : " << static_cast<short>(q.a) << endl;

    q       <<= 2;  // Left shift by 2 bits

    cout    << "After <<= : " << static_cast<short>(q.a) << endl;   // Output: 20 (binary: 00010100)

    A       R(static_cast<char>(5));    // 5 in decimal
    A       r(static_cast<char>(10));   // 10 in decimal

    cout    << "R <= r: " << (R <= r ? "true" : "false") << endl;   // Output: true

    A       S(static_cast<char>(5));    // 5 in decimal
    A       s(static_cast<char>(10));   // 10 in decimal

    cout    << "Before assignment: S.a = " << static_cast<short>(S.a) << endl;  // Output: 5
    cout    << "Before assignment: s.a = " << static_cast<short>(s.a) << endl;  // Output: 10

    S = s;  // Assign s to S

    cout    << "After assignment: S.a = " << static_cast<short>(S.a) << endl;   // Output: 10

    A       T(static_cast<char>(5));    // 5 in decimal
    A       t(static_cast<char>(5));    // 5 in decimal
    A       U(static_cast<char>(10));   // 10 in decimal

    cout    << "T == t: " << (T == t ? "true" : "false") << endl;   // Output: true
    cout    << "T == U: " << (T == U ? "true" : "false") << endl;   // Output: false

    A       u(static_cast<char>(10));   // 10 in decimal
    A       V(static_cast<char>(5));    // 5 in decimal

    cout    << "u > V: " << (u > V ? "true" : "false") << endl; // Output: true
    cout    << "V > u: " << (V > u ? "true" : "false") << endl; // Output: false

    A       v(static_cast<char>(10));   // 10 in decimal
    A       W(static_cast<char>(10));   // 10 in decimal
    A       w(static_cast<char>(5));    // 5 in decimal

    cout    << "v >= W: " << (v >= W ? "true" : "false") << endl;   // Output: true
    cout    << "v >= w: " << (v >= w ? "true" : "false") << endl;   // Output: true
    cout    << "w >= v: " << (w >= v ? "true" : "false") << endl;   // Output: false

    A       X(static_cast<char>(16));   // 16 in decimal (0b10000)
    A       x(static_cast<char>(2));    // Shift by 2 bits

    A       Y = X >> x;

    cout    << "16 >> 2 = " << static_cast<short>(Y.a) << endl;  
    // Output: 16 >> 2 = 4  (0b10000 >> 2 = 0b100)

    A       y(static_cast<char>(16));   // 16 in decimal (0b10000)
    A       Z(static_cast<char>(2));    // Shift by 2 bits

    y       >>= Z;

    cout    << "16 >>= 2 = " << static_cast<short>(y.a) << endl;
    // Output: 16 >>= 2 = 4  (0b10000 >> 2 = 0b100)

    A       z(static_cast<char>(5));    // a = 5, B = 0
    
    z.B     = 10;   // Set B to 10

    cout    << "z[0]: " << z[0] << endl;  // Access 'a'
    cout    << "z[1]: " << z[1] << endl;  // Access 'B'

    // Out-of-bounds access (returns 0)
    cout    << "z[2] (out of bounds): " << z[2] << endl;

    A       AA(static_cast<char>(5));
    A       Aa(static_cast<char>(3));
    A       AB = AA ^ Aa; // 5 ^ 3 = 6

    cout    << "AA ^ Aa: " << static_cast<short>(AB.a) << endl;

    AA      ^= Aa;  //  AA ^= Aa
    
    cout    << "AA after AA ^= Aa: " << static_cast<short>(AA.a) << endl;

    A       Ab(static_cast<char>(5));
    A       AC(static_cast<char>(3));
    A       Ac = Ab | AC;   // 5 | 3 = 7

    cout    << "Ab | AC: " << static_cast<short>(Ac.a) << endl;

    Ab       |= AC;  // Ab |= AC

    cout    << "Ab after Ab |= AC: " << static_cast<short>(Ab.a) << endl;

    A       AD(static_cast<char>(5));
    A       Ad(static_cast<char>(0));

    if      (AD || Ad) cout << "Logical OR is true\n";
    else    cout << "Logical OR is false\n";

    A       AE(static_cast<char>(5));
    A       Ae = ~AE;

    cout    << static_cast<short>(Ae.a) << endl;

    A       *AF = new A();

    delete  AF;

    A       *Af = new A(42);
    int     AG = *Af;   // Implicit conversion
    double  Ag = static_cast<double>(*Af);  // Explicit conversion
    void    *AH = *Af;  // Pointer conversion

    cout    << "AG: " << AG << endl;
    cout    << "Ag: " << Ag << endl;
    cout    << "AH: " << AH << endl;

    delete  Af;

    ExitProcess(0);
}