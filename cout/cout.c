#include <Windows.h>
#include <stdio.h>

int main()
{
    fprintf_s(stdout, "Hello, World!\n");

    ExitProcess(0);
}