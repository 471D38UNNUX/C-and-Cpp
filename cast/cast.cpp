#include <iostream>
#include <typeinfo>
#include <Windows.h>

using namespace std;

class   Base {public: virtual ~Base() {}};  // Necessary for dynamic_cast
class   Derived : public Base {public: void show() {cout << "Derived class\n";}};
void    print(int* ptr) {cout << "Const_cast value: " << *ptr << '\n';}
int     main()
{
    // static_cast (Safe conversions)
    double          pi = 3.14159;
    int             intPi = static_cast<int>(pi); // Convert double to int

    cout            << "static_cast: " << intPi << '\n';

    Derived         d;
    Base            *b1 = static_cast<Base*>(&d); // Upcast (safe)

    cout            << "static_cast (Upcast): " << typeid(*b1).name() << '\n';

    // dynamic_cast (safe downcasting in polymorphism)
    Base            *b2 = new Derived();
    Derived         *d1 = dynamic_cast<Derived*>(b2); // Downcast

    if              (d1) d1->show(); // Successful cast

    Base            *b3 = new Base();
    Derived         *d2 = dynamic_cast<Derived*>(b3); // Invalid cast (nullptr)

    if              (!d2) cout << "dynamic_cast failed\n";

    // reinterpret_cast (Low-level bit reinterpretation)
    int             num = 65;
    char            *ch = reinterpret_cast<char*>(&num);

    cout            << "reinterpret_cast: " << *ch << '\n'; // May print 'A' if little-endian

    // const_cast (Removing constness)
    const int       constNum = 10;
    int             *modifiableNum = const_cast<int*>(&constNum);
    *modifiableNum  = 20; // Undefined behavior if constNum was in read-only memory

    print(modifiableNum);

    // std::bad_cast with dynamic_cast (Reference cast failure)
    try             {Derived &ref = dynamic_cast<Derived&>(*b3);}   // Throws std::bad_cast
    catch           (const bad_cast &e) {cerr << "bad_cast caught: " << e.what() << '\n';}

    try
    {
        Base        *ptr = nullptr;

        cout << typeid(*ptr).name() << '\n';
    }
    catch           (const bad_typeid &e) {cerr << "bad_typeid caught: " << e.what() << '\n';}

    int             a = 42;
    double          b = 3.14;
    Base            baseObj;
    Derived         derivedObj;
    Base            *basePtr = &derivedObj;  // Polymorphic pointer
    // Get type information
    const type_info &typeA = typeid(a);
    const type_info &typeB = typeid(b);
    const type_info &typeBase = typeid(baseObj);
    const type_info &typeDerived = typeid(derivedObj);
    const type_info &typeBasePtr = typeid(*basePtr); // Polymorphic behavior

    // Print type names
    cout            << "Type of a: " << typeA.name() << std::endl;
    cout            << "Type of b: " << typeB.name() << std::endl;
    cout            << "Type of baseObj: " << typeBase.name() << std::endl;
    cout            << "Type of derivedObj: " << typeDerived.name() << std::endl;
    cout            << "Type of *basePtr: " << typeBasePtr.name() << std::endl;

    // Compare types
    if              (typeid(a) == typeid(int)) cout << "a is an int." << std::endl;
    if              (typeid(baseObj) != typeid(derivedObj)) std::cout << "baseObj and derivedObj have different types." << std::endl;

    // Cleanup
    delete          b2;
    delete          b3;

    ExitProcess(0);
}
