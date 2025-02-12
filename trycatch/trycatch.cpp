#include <Windows.h>
#include <iostream>

using namespace std;

static void Error()
{
    cout    << "Test" << "\n";

    throw   runtime_error("Error");
}
int         main()
{
    try                         
    {
        Error();

        cout << "This line won't execute if an exception is thrown\n";
    }
    catch(runtime_error &A)     {cout << A.what() << "\n";}
    catch(...)                  {cout << "Unknown exception\n";}

    cout                        << "Continue\n";

    ExitProcess(0);
}