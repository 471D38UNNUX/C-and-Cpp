#include <Windows.h>
#include <stdio.h>
#include <string.h>

unsigned    long long hash(char *str)
{
    unsigned long long  hasher = 14695981039346656037ULL, prime = 1099511628211;

    while               (*str) hasher ^= (unsigned char)(*str), hasher *= prime, str++;

    return              hasher;
}
int         main()
{
    char                str1[] = "Hello";
    char                str2[] = "World";
    //  Concatenation
    char                result[14];

    _snprintf_s(result, sizeof(result), _TRUNCATE, "%s, %s!", str1, str2);

    fprintf_s(stdout, "%s\n", result);
    //  Getting string length
    fprintf_s(stdout, "Length: %llu\n", strlen(result));
    //  Accessing characters
    fprintf_s(stdout, "First character: %c\n", result[0]);

    //  Modifying a string
    result[0]           = 'h';

    fprintf_s(stdout, "Modified string: %s\n", result);

    //  Substring
    char                sub[6];

    strncpy_s(sub, sizeof(sub), result, 5);

    fprintf_s(stdout, "Substring: %s\n", sub);

    //  Finding a substring
    char                *pos = strstr(result, "World");

    if                  (pos) fprintf_s(stdout, "'World' found at position: %llu\n", pos - result);

    //  Hash function (C++'s FNV-1a hash for demonstration)
    unsigned long long  hashValue = hash(result);

    fprintf_s(stdout, "Hash value: %llu\n", hashValue);
    //  Swap function
    fprintf_s(stdout, "Before swap: str1 = %s, str2 = %s\n", str1, str2);

    char                tmp[6];
    
    strcpy_s(tmp, sizeof(tmp), str1);
    strcpy_s(str1, sizeof(str1), str2);
    strcpy_s(str2, sizeof(str2), tmp);

    fprintf_s(stdout, "After swap: str1 = %s, str2 = %s\n", str1, str2);

    // Convert string to integer using strtol
    char                numberStr[] = "12345";
    char                *endptr;
    int                 number = strtol(numberStr, &endptr, 10);

    fprintf_s(stdout, "Converted number: %d\n", number);

    ExitProcess(0);
}