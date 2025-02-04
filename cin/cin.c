#include <Windows.h>
#include <stdio.h>

char    msg[16];
int     main()
{
    fgets(msg, sizeof(msg), stdin);

    fprintf_s(stdout, msg);

    ExitProcess(0);
}