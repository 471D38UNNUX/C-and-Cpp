#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    //  Declare and initialize strings
    string              str1 = "Hello";
    string              str2 = "World";
    //  Concatenation
    string              result = str1 + ", " + str2 + "!";

    cout                << result << endl;
    //  Getting string length
    cout                << "Length: " << result.length() << endl;
    //  Accessing characters
    cout                << "First character: " << result[0] << endl;

    //  Modifying a string
    result[0]           = 'h';

    cout                << "Modified string: " << result << endl;

    //  Substring
    string              sub = result.substr(0, 5);

    cout            << "Substring: " << sub << endl;

    //  Finding a substring
    size_t              pos = result.find("World");
    
    if                  (pos != string::npos) cout << "'World' found at position: " << pos << endl;

    //  Hash function
    hash<string>        hasher;
    size_t              hashValue = hasher(result);

    cout                << "Hash value: " << hashValue << endl;
    //  Swap function
    cout                << "Before swap: str1 = " << str1 << ", str2 = " << str2 << endl;

    str1.swap(str2);

    cout                << "After swap: str1 = " << str1 << ", str2 = " << str2 << endl;

    //  Convert string to integer using stoi
    string              numberStr = "12345";
    int                 number = stoi(numberStr);
    
    cout                << "Converted number: " << number << endl;

    //  Convert number to string using to_string
    string              numberToStr = to_string(number);

    cout                << "Converted string: " << numberToStr << endl;

    //  String comparison using != operator
    if                  (str1 != str2) cout << "Strings are not equal." << endl;

    //  Using getline function
    cin.ignore();   //  Clear newline from previous input

    string              fullLine;

    cout                << "Enter a full line: ";

    getline(cin, fullLine);

    cout                << "You entered: " << fullLine << endl;

    //  Using basic_string class
    basic_string<char>  basicStr = "Basic string example";

    cout                << "Basic string: " << basicStr << endl;

    //  Using append function
    string              appendStr = " Appended text.";

    result.append(appendStr);

    cout                << "After append: " << result << endl;

    //  Using assign function
    string              assignStr;

    assignStr.assign("Assigned text.");

    cout                << "After assign: " << assignStr << endl;

    //  Using at function
    char                thirdChar = result.at(2);

    cout                << "Character at index 2: " << thirdChar << endl;

    //  Using back function
    char                lastChar = result.back();

    cout                << "Last character: " << lastChar << endl;

    //  Using begin function
    char                firstChar = *result.begin();

    cout                << "First character using begin: " << firstChar << endl;

    //  Using c_str function
    const char          *cstr = result.c_str();
    
    cout                << "C-style string: " << cstr << endl;

    //  Using capacity function
    cout                << "String capacity: " << result.capacity() << endl;

    //  Using clear function
    result.clear();

    cout                << "String after clear: '" << result << "' (should be empty)" << endl;

    //  Using compare function
    int                 compareResult = str1.compare(str2);

    if                  (!compareResult) cout << "Strings are equal." << endl;
    else if             (compareResult < 0) cout << "str1 is less than str2." << endl;
    else                cout << "str1 is greater than str2." << endl;

    //  Using _Copy_s function
    char                buffer[50] = {0};
    size_t              copiedChars;
    result              = "Copy this string.";

    result._Copy_s(buffer, sizeof(buffer), result.length());

    buffer[result.length()] = 0;

    cout                << "Copied string: " << buffer << endl;

    //  Using data function
    const char          *dataPtr = result.data();
    
    cout                << "Data function output: " << dataPtr << endl;
    //  Using empty function
    cout                << "Is result string empty? " << (result.empty() ? "Yes" : "No") << endl;
    
    //  Using end function
    char                lastCharUsingEnd = *(result.end() - 1);

    cout                << "Last character using end: " << lastCharUsingEnd << endl;

    ExitProcess(0);
}
