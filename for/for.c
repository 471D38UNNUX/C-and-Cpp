#include <stdio.h>
#include <Windows.h>

int main()
{
    int numbers[] = {1, 2, 3, 4, 5};

    // 1. Basic loop (copy)
    fprintf_s(stdout, "Copy: ");

    for (int num = 0; num < sizeof(numbers) / sizeof(numbers[0]); num++) fprintf_s(stdout, "%d ", numbers[num]);

    fprintf_s(stdout, "\n");

    // 2. Using reference to modify elements
    for (int *num = numbers; num < numbers + sizeof(numbers) / sizeof(numbers[0]); num++) *num *= 2; // Modify elements in-place

    // 3. Printing modified values
    fprintf_s(stdout, "Modified: ");
    for (const int *num = numbers; num < numbers + sizeof(numbers) / sizeof(numbers[0]); num++) fprintf_s(stdout, "%d ", *num); // Using const reference

    fprintf_s(stdout, "\n");

    ExitProcess(0);
}
