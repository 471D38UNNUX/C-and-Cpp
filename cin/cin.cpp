#include <Windows.h>
#include <iostream>

using namespace std;

char    * msg;
int     main() noexcept
{
    cin.getline(msg, 16);

    cout    << msg << endl;
    
    ExitProcess(0);
}