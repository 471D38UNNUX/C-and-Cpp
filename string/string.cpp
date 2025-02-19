#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    //  Declare and initialize strings
    string          str1 = "Hello";
    string          str2 = "World";
    //  Concatenation
    string          result = str1 + ", " + str2 + "!";

    cout            << result << endl;
    //  Getting string length
    cout            << "Length: " << result.length() << endl;
    //  Accessing characters
    cout            << "First character: " << result[0] << endl;

    //  Modifying a string
    result[0]       = 'h';

    cout            << "Modified string: " << result << endl;

    //  Substring
    string          sub = result.substr(0, 5);

    cout            << "Substring: " << sub << endl;

    //  Finding a substring
    size_t          pos = result.find("World");
    
    if              (pos != string::npos) cout << "'World' found at position: " << pos << endl;

    //  Hash function
    hash<string>    hasher;
    size_t          hashValue = hasher(result);

    cout            << "Hash value: " << hashValue << endl;
    //  Swap function
    cout            << "Before swap: str1 = " << str1 << ", str2 = " << str2 << endl;

    str1.swap(str2);

    cout            << "After swap: str1 = " << str1 << ", str2 = " << str2 << endl;

    // Convert string to integer using stoi
    string          numberStr = "12345";
    int             number = stoi(numberStr);
    
    cout            << "Converted number: " << number << endl;

    ExitProcess(0);
}
