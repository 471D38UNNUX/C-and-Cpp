#include <Windows.h>
#include <stdio.h>
#include <string.h>

unsigned long long  hash(char *str)
{
    unsigned long long  hasher = 14695981039346656037ULL, prime = 1099511628211;

    while               (*str) hasher ^= (unsigned char)(*str), hasher *= prime, str++;

    return              hasher;
}
typedef struct      basic_string
{
    char    *data;
    size_t  size;
}                   basic_string;
static basic_string *Cbasic_string(char *str, size_t size)
{
    basic_string    *new = (basic_string*)VirtualAlloc(NULL, sizeof(basic_string), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if              (!new) ExitProcess(1);

    new->data       = (char*)VirtualAlloc(NULL, size + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if              (!new->data) ExitProcess(1);
    
    strncpy_s(new->data, size + 1, str, size);

    new->size       = size;

    return          new;
}
static void         Dbasic_string(basic_string *basic_string[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        VirtualFree(basic_string[i]->data, 0, MEM_RELEASE);
        VirtualFree(basic_string[i], 0, MEM_RELEASE);
    }
}
static void         append_substr(basic_string *dest, char *str, size_t count)
{
    size_t                  new_size = dest->size + count;

    char                    *new_data = (char *)VirtualAlloc(NULL, new_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if                      (!new_data) ExitProcess(1);

    strncpy_s(new_data, new_size, dest->data, dest->size - 1);

    strncat_s(new_data, new_size, str, count);

    VirtualFree(dest->data, 0, MEM_RELEASE);

    dest->data              = new_data;
    dest->size              = new_size;
}
static void         append_basic_string(basic_string *dest, basic_string *str) {append_substr(dest, str->data, strnlen_s(str->data, SIZE_MAX));}
static void         append_repeated_char(basic_string *dest, size_t count, char char_value)
{
    size_t                  new_size = dest->size + count;

    char                    *new_data = (char *)VirtualAlloc(NULL, new_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if                      (!new_data) ExitProcess(1);

    strncpy_s(new_data, new_size, dest->data, dest->size - 1);
    
    memset(new_data + dest->size - 1, char_value, count);

    new_data[new_size - 1]  = '\0';

    VirtualFree(dest->data, 0, MEM_RELEASE);

    dest->data              = new_data;
    dest->size              = new_size;
}
static void         append_range(basic_string *dest, char *first, const char *last)
{
    if      (first >= last) return;

    size_t  count = last - first;

    append_substr(dest, first, count);
}
static void         assign_n(basic_string *dest, char *str, size_t count)
{
    size_t              new_size = strnlen_s(str, count);
    char                *new_data = (char *)VirtualAlloc(NULL, new_size + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if                  (!new_data) ExitProcess(1);

    strncpy_s(new_data, new_size + 1, str, new_size);
    
    new_data[new_size]  = '\0';

    if                  (dest->data) VirtualFree(dest->data, 0, MEM_RELEASE);
    
    dest->data = new_data;
    dest->size = new_size;
}
static void         assign(basic_string *dest, char *str) {assign_n(dest, str, strnlen_s(str, _TRUNCATE));}
static void         assign_substr(basic_string *dest, const basic_string *src, size_t off, size_t count)
{
    if (off >= src->size) return;
    if (count > src->size - off) count = src->size - off;

    assign_n(dest, src->data + off, count);
}
static void         assign_repeat(basic_string *dest, size_t count, char ch)
{
    char            *new_data = (char *)VirtualAlloc(NULL, count + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if              (!new_data) ExitProcess(1);

    memset(new_data, ch, count);
    
    new_data[count] = '\0';

    if              (dest->data) VirtualFree(dest->data, 0, MEM_RELEASE);
    
    dest->data      = new_data;
    dest->size      = count;
}
static void         assign_range(basic_string *dest, char *first, char *last)
{
    if (first >= last) return;

    assign_n(dest, first, strnlen_s(first, last - first));
}
int                 main()
{
    basic_string        *str1 = Cbasic_string("Hello", 6);
    basic_string        *str2 = Cbasic_string("World", 6);
    //  Concatenation
    basic_string        *result = Cbasic_string("", 14);

    _snprintf_s(result->data, result->size, _TRUNCATE, "%s, %s!", str1->data, str2->data);

    fprintf_s(stdout, "%s\n", result->data);
    //  Getting string length
    fprintf_s(stdout, "Length: %llu\n", result->size);
    //  Accessing characters
    fprintf_s(stdout, "First character: %c\n", result->data[0]);

    //  Modifying a string
    result->data[0]     = 'h';

    fprintf_s(stdout, "Modified string: %s\n", result->data);

    //  Substring
    basic_string        *sub = Cbasic_string("", 6);

    strncpy_s(sub->data, sub->size, result->data, 5);

    fprintf_s(stdout, "Substring: %s\n", sub->data);

    //  Finding a substring
    char                *pos = strstr(result->data, "World");

    if                  (pos) fprintf_s(stdout, "'World' found at position: %llu\n", pos - result->data);

    //  Hash function (C++'s FNV-1a hash for demonstration)
    unsigned long long  hashValue = hash(result->data);

    fprintf_s(stdout, "Hash value: %llu\n", hashValue);
    //  Swap function
    fprintf_s(stdout, "Before swap: str1 = %s, str2 = %s\n", str1->data, str2->data);

    char                tmp[6];
    
    strncpy_s(tmp, sizeof(tmp), str1->data, str1->size);
    strncpy_s(str1->data, str1->size, str2->data, str2->size);
    strncpy_s(str2->data, str2->size, tmp, sizeof(tmp));

    fprintf_s(stdout, "After swap: str1 = %s, str2 = %s\n", str1->data, str2->data);

    //  Convert string to integer using strtol
    basic_string        *numberStr = Cbasic_string("12345", 6);
    char                *endptr;
    int                 number = strtol(numberStr->data, &endptr, 10);

    fprintf_s(stdout, "Converted number: %d\n", number);

    //  Convert number to string using _snprintf_s
    basic_string        *numberToStr = Cbasic_string("", 14);

    _snprintf_s(numberToStr->data, numberToStr->size, _TRUNCATE, "%d", number);

    fprintf_s(stdout, "Converted string: %s\n", numberToStr->data);

    //  String comparison using strcmp
    if                  (strcmp(str1->data, str2->data)) fprintf_s(stdout, "Strings are not equal.\n");

    char                fullLine[255];

    //  Clear newline from previous input
    getchar();

    fprintf_s(stdout, "Enter a full line: ");

    //  Using fgets function
    if                  (fgets(fullLine, sizeof(fullLine), stdin))
    {
        size_t  len = strnlen_s(fullLine, sizeof(fullLine));

        if      (len > 0 && fullLine[len - 1] == '\n') fullLine[len - 1] = '\0';

        fprintf_s(stdout, "You entered: %s\n", fullLine);
    }

    //  Using basic_string struct
    basic_string        *basicStr = Cbasic_string("Basic string example", 21);

    fprintf_s(stdout, "Basic string: %s\n", basicStr->data);

    //  Using append function
    basic_string        *appendStr = Cbasic_string(" Appended text.", 16);

    append_basic_string(result, appendStr);

    fprintf_s(stdout, "After append: %s\n", result->data);

    //  Using assign function
    basic_string        *assignStr = Cbasic_string("", 1);

    assign(assignStr, "Assigned text.");

    fprintf_s(stdout, "After assign: %s\n", assignStr->data);

    //  Using at function
    char                thirdChar = result->data[2];

    fprintf_s(stdout, "Character at index 2: %c\n", thirdChar);

    basic_string        *All[] = {str1, str2, result, sub, numberStr, numberToStr, basicStr, appendStr, assignStr};

    Dbasic_string(All, sizeof(All) / sizeof(All[0]));

    ExitProcess(0);
}