#include <iostream>
#include <Windows.h>

using namespace std;

// Define a namespace
namespace   MyNamespace
{
    int     myNumber = 42;

    void    display() {cout << "My number is: " << myNumber << endl;}
}
int         main()
{
    // Accessing the namespace members using the scope resolution operator (::)
    MyNamespace::display();
    
    // Another way to use namespace members
    using namespace MyNamespace;
    cout << "Accessing myNumber directly: " << myNumber << endl;

    ExitProcess(0);
}
