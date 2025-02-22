#include <iostream>
#include <Windows.h>

using namespace std;

int main() noexcept
{
    int         numbers[] = {1, 2, 3, 4, 5};

    // 1. Basic range-based for loop (copy)
    cout << "Copy: ";

    for         (int num : numbers) cout << num << " ";

    cout        << endl;

    // 2. Using reference to modify elements
    for         (int &num : numbers) num *= 2;  // Modify elements in-place

    cout        << "Modified: ";
    
    for         (const int &num : numbers) cout << num << " ";  // Using const reference

    cout        << endl;

    ExitProcess(0);
}
