#include <iostream>
#include <Windows.h>

using namespace std;

struct  Example
{
    Example()           noexcept {}  // Default constructor is noexcept

    Example(Example&&)  noexcept {cout << "Move constructor called\n"; }

    Example             &operator=(Example&&) noexcept
    {
        cout    << "Move assignment called\n";
        
        return  *this;
    }

    void                safeFunction() noexcept {cout << "This function does not throw exceptions.\n";}

    void                riskyFunction() {throw runtime_error("Error!");}
};

void     testNoexcept() noexcept {cout << "This function is noexcept.\n";}

int main()
{
    Example e1;
    Example e2 = std::move(e1);  // Calls noexcept move constructor

    e2.safeFunction();

    cout    << boolalpha;
    cout    << "Is testNoexcept() noexcept? " << noexcept(testNoexcept()) << "\n";
    cout    << "Is riskyFunction() noexcept? " << noexcept(e1.riskyFunction()) << "\n";

    ExitProcess(0);
}
