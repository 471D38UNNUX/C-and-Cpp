#include <Windows.h>
#include <stdio.h>

int main()
{
    fprintf_s(stderr, "Hello, World!\n");

    ExitProcess(0);
}