#include <Windows.h>
#include <iostream>

using namespace std;

// This function is guaranteed not to throw exceptions
int main() noexcept
{
    cout    << "Hello, World!" << endl;
    
    ExitProcess(0);
}