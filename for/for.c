#include <stdio.h>
#include <Windows.h>

int main()
{
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    // 1. Basic loop (copy)
    fprintf_s(stdout, "Copy: ");

    for (int i = 0; i < size; i++) fprintf_s(stdout, "%d ", numbers[i]);

    fprintf_s(stdout, "\n");

    // 2. Using reference to modify elements
    for (int *i = numbers; i < numbers + size; i++) *i *= 2; // Modify elements in-place

    // 3. Printing modified values
    fprintf_s(stdout, "Modified: ");
    for (const int *i = numbers; i < numbers + size; i++) fprintf_s(stdout, "%d ", *i); // Using const reference

    fprintf_s(stdout, "\n");

    ExitProcess(0);
}
