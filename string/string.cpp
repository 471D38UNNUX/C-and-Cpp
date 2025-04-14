#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    //  Declare and initialize strings
    string                  str1 = "Hello";
    string                  str2 = "World";
    //  Concatenation
    string                  result = str1 + ", " + str2 + "!";

    cout                    << result << endl;
    //  Getting string length
    cout                    << "Length: " << result.length() << endl;
    //  Accessing characters
    cout                    << "First character: " << result[0] << endl;

    //  Modifying a string
    result[0]               = 'h';

    cout                    << "Modified string: " << result << endl;

    //  Substring
    string                  sub = result.substr(0, 5);

    cout                    << "Substring: " << sub << endl;

    //  Finding a substring
    size_t                  pos = result.find("World");
    
    if                      (pos != string::npos) cout << "'World' found at position: " << pos << endl;

    //  Hash function
    hash<string>            hasher;
    size_t                  hashValue = hasher(result);

    cout                    << "Hash value: " << hashValue << endl;
    //  Swap function
    cout                    << "Before swap: str1 = " << str1 << ", str2 = " << str2 << endl;

    str1.swap(str2);

    cout                    << "After swap: str1 = " << str1 << ", str2 = " << str2 << endl;

    //  Convert string to integer using stoi
    string                  numberStr = "12345";
    int                     number = stoi(numberStr);
    
    cout                    << "Converted number: " << number << endl;

    //  Convert number to string using to_string
    string                  numberToStr = to_string(number);

    cout                    << "Converted string: " << numberToStr << endl;

    //  String comparison using != operator
    if                      (str1 != str2) cout << "Strings are not equal." << endl;

    //  Using getline function
    cin.ignore();   //  Clear newline from previous input

    string                  fullLine;

    cout                << "Enter a full line: ";

    getline(cin, fullLine);

    cout                    << "You entered: " << fullLine << endl;

    //  Using basic_string class
    basic_string<char>  basicStr = "Basic string example";

    cout                    << "Basic string: " << basicStr << endl;

    //  Using append function
    string                  appendStr = " Appended text.";

    result.append(appendStr);

    cout                    << "After append: " << result << endl;

    //  Using assign function
    string                  assignStr;

    assignStr.assign("Assigned text.");

    cout                    << "After assign: " << assignStr << endl;

    //  Using at function
    char                    thirdChar = result.at(2);

    cout                    << "Character at index 2: " << thirdChar << endl;

    //  Using back function
    char                    lastChar = result.back();

    cout                    << "Last character: " << lastChar << endl;

    //  Using begin function
    char                    firstChar = *result.begin();

    cout                    << "First character using begin: " << firstChar << endl;

    //  Using front function
    char                    frontChar = result.front();
    
    cout                    << "First character using front: " << frontChar << endl;

    //  Using c_str function
    const char              *cstr = result.c_str();
    
    cout                    << "C-style string: " << cstr << endl;

    //  Using capacity function
    cout                    << "String capacity: " << result.capacity() << endl;

    //  Using clear function
    result.clear();

    cout                    << "String after clear: '" << result << "' (should be empty)" << endl;

    //  Using compare function
    int                     compareResult = str1.compare(str2);

    if                      (!compareResult) cout << "Strings are equal." << endl;
    else if                 (compareResult < 0) cout << "str1 is less than str2." << endl;
    else                    cout << "str1 is greater than str2." << endl;

    //  Using _Copy_s function
    char                    buffer[50] = {0};
    size_t                  copiedChars;
    result                  = "Copy this string.";

    result._Copy_s(buffer, sizeof(buffer), result.length());

    buffer[result.length()] = 0;

    cout                    << "Copied string: " << buffer << endl;

    //  Using data function
    const char              *dataPtr = result.data();
    
    cout                    << "Data function output: " << dataPtr << endl;
    //  Using empty function
    cout                    << "Is result string empty? " << (result.empty() ? "Yes" : "No") << endl;
    
    //  Using end function
    char                    lastCharUsingEnd = *(result.end() - 1);

    cout                    << "Last character using end: " << lastCharUsingEnd << endl;

    //  Using erase function
    result                  = "Erase part of this string.";

    result.erase(6, 9); //  Remove "part of "

    cout                    << "After erase: " << result << endl;

    //  Using find_first_not_of function
    string                  sample = "###Hello###";
    size_t                  firstNotOf = sample.find_first_not_of("#");
    
    if                      (firstNotOf != string::npos) cout << "First character not '#': " << sample[firstNotOf] << " at position " << firstNotOf << endl;    
    else                    cout << "No different characters found." << endl;

    //  Using find_first_of function
    string                  findSample = "abcdefg";
    size_t                  firstOf = findSample.find_first_of("dc");

    if                      (firstOf != string::npos) cout << "First character found: " << findSample[firstOf] << " at position " << firstOf << endl;
    else                    cout << "No matching characters found." << endl;

    //  Using find_last_not_of function
    size_t                  lastNotOf = sample.find_last_not_of("#");

    if                      (lastNotOf != string::npos) cout << "Last character not '#': " << sample[lastNotOf] << " at position " << lastNotOf << endl;    
    else                    cout << "No different characters found." << endl;

    //  Using find_last_of function
    size_t                  lastOf = sample.find_last_of("#");
    
    if                      (lastOf != string::npos) cout << "Last occurrence of '#': at position " << lastOf << endl;
    else                    cout << "Character not found." << endl;

    //  Using get_allocator function
    allocator<string>       alloc = result.get_allocator(); //  Get allocator from existing string
    string                  *p = alloc.allocate(1); //  Allocate space for one string

    alloc.construct(p, "Allocated string"); //  Construct the string in-place

    cout                    << "Allocated string using get_allocator: " << *p << endl;
    
    alloc.destroy(p);   //  Destroy the string object
    
    alloc.deallocate(p, 1); //  Free the memory

    //  Using insert function
    result                  = "Say !";

    result.insert(4, "Hello");

    cout                    << "After insert: " << result << endl;
    //  Using max_size function
    cout                    << "Maximum size a string can hold: " << result.max_size() << endl;

    //  Using pop_back function
    result                  = "Remove last.";

    result.pop_back();

    cout                    << "After pop_back: " << result << endl;

    //  Using push_back function
    result.push_back('?');  //  Appends a character at the end

    cout                    << "After push_back: " << result << endl;
    //  Using rbegin function
    cout                    << "Last character using rbegin: " << *result.rbegin() << endl;

    //  Using rend function
    auto                    rendIt = result.rend();
    rendIt--;
    
    cout                    << "Character before rend: " << *rendIt << endl;

    //  Using replace function
    result                  = "I love programming!";

    result.replace(7, 11, "coding");    //  Replacing "programming" with "coding"
    
    cout                    << "After replace: " << result << endl;

    //  Using reserve function
    string                  reservedStr;

    reservedStr.reserve(100);   //  Reserve space for at least 100 characters
    
    reservedStr             = "Reserved string memory.";

    cout                    << "After reserve: " << reservedStr << endl;
    cout                    << "Reserved capacity: " << reservedStr.capacity() << endl;

    //  Using resize function
    string                  resizeStr = "Resize me!";
    
    cout                    << "Original string: " << resizeStr << endl;

    resizeStr.resize(5);    //  Shrinks the string

    cout                    << "After shrinking: " << resizeStr << endl;

    resizeStr.resize(10, '*');  //  Expands and fills with '*'

    cout                    << "After expanding: " << resizeStr << endl;

    //  Using rfind function
    string                  rfindStr = "one two three two one";
    size_t                  lastPos = rfindStr.rfind("two");

    if                      (lastPos != string::npos) cout << "Last occurrence of 'two' is at position: " << lastPos << endl;
    else                    cout << "'two' not found." << endl;

    //  Using shrink_to_fit function
    result                  = "This is a long string with extra capacity.";

    cout                    << "Capacity before shrink_to_fit: " << result.capacity() << endl;

    result.resize(10);  //  Resize to reduce actual string size

    result.shrink_to_fit(); //  Request to reduce capacity to fit size

    cout                    << "Capacity after shrink_to_fit: " << result.capacity() << endl;
    
    ExitProcess(0);
}
