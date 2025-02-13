#include <Windows.h>
#include <stdio.h>
#include <setjmp.h>

typedef struct Example
{
    void    (*safeFunction)();
    void    (*riskyFunction)();
}               Example;
void            safeFunction() {fprintf_s(stdout, "This function does not throw exceptions.\n");}
jmp_buf         buf;
char            noexcept, jmp;
static void     riskyFunction()
{
    longjmp(buf, 1);
    
    fprintf_s(stderr, "Error!");
}
Example         *CExample() // Default constructor is noexcept
{
    Example             *new = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(Example));

    if                  (!new) ExitProcess(1);

    new->safeFunction   = safeFunction;
    new->riskyFunction  = riskyFunction;

    return              new;
}
Example         *MCExample(Example *src)
{
    Example *new = src;
    src     = NULL;

    fprintf_s(stdout, "Move constructor called\n");

    return  new;
}
Example         *MAExample(Example *src)
{
    Example *new = CExample();

    memcpy_s(new, sizeof(Example), src, sizeof(Example));
    
    src     = NULL;

    fprintf_s(stdout, "Move assignment called\n");

    return  new;
}
Example         *DExample(Example *Example)
{
    HeapFree(GetProcessHeap, 0, Example);

    return  NULL;
}
static void     testNoexcept()
{
    if (jmp)
    {
        jmp = 0;

        return;
    }

    fprintf_s(stdout, "This function is noexcept.\n");
}
int             main()
{
    Example *e1 = CExample();
    Example *e2 = MCExample(e1);    // Calls noexcept move constructor
    e2->safeFunction();

    if      (!setjmp(buf))
    {
        jmp         = 1;
        
        testNoexcept();

        noexcept    = 1;
    }

    fprintf_s(stdout, "Is testNoexcept() noexcept? %s\n", noexcept ? "true" : "false");
    
    if      (!setjmp(buf))
    {
        jmp         = 1;
        
        e1->riskyFunction();

        noexcept    = 1;
    }
    else    jmp = 0, noexcept = 0;

    fprintf_s(stdout, "Is riskyFunction() noexcept? %s\n", noexcept ? "true" : "false");

    ExitProcess(0);
}