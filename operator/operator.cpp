#include <iostream>
#include <random>
#include <ctime>
#include <Windows.h>

using namespace std;

class   A
{
    public:
        // Constructor
        A()                 noexcept {}
        explicit A(char A)  noexcept : a(A), B(0) {}
        explicit A(short A) noexcept : a(0), B(A) {}
        // Overloading the comma operator
        A                   operator,(const A &A) noexcept
        {
            cout    << "Comma operator called: " << static_cast<short>(a) << ", " << static_cast<short>(A.a) << endl;

            return  A;  // Return the right-hand operand
        };
        ~A()                noexcept {}
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
        char                a;
        short               B;
};
mt19937 a(time(nullptr));
uniform_int_distribution<int>B(-128, 127);
int     main()
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


    ExitProcess(0);
}