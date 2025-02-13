#include <Windows.h>
#include <stdio.h>
#include <setjmp.h>

jmp_buf     jumpBuffer;
char        jumpValue;
static void Error()
{
    fprintf_s(stdout, "Test\n");

    longjmp(jumpBuffer, 1);
}
int         main()
{
    jumpValue   = setjmp(jumpBuffer);

    if          (!jumpValue)
    {
        Error();

        fprintf_s(stdout, "This line won't execute if an exception is thrown\n");
    }
    else if     (jumpValue == 1) fprintf_s(stderr, "Error\n");
    else        fprintf_s(stdout, "Unknown exception\n");

    fprintf_s(stdout, "Continue\n");

    ExitProcess(0);
}