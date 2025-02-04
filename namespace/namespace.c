#include <stdio.h>
#include <Windows.h>

// Define a struct as namespace
typedef struct  MyNamespace
{
    int     myNumber;
    void    (*display)(struct MyNamespace MyNamespace);
}               MyNamespace;
void            display(struct MyNamespace MyNamespace) {fprintf(stdout, "My number is: %d\n", MyNamespace.myNumber);}
int             main()
{
    MyNamespace             MyNamespace;
    MyNamespace.display     = display;
    MyNamespace.myNumber    = 42;

    MyNamespace.display(MyNamespace);

    fprintf(stdout, "Accessing myNumber directly: %d\n", MyNamespace.myNumber);

    ExitProcess(0);
}