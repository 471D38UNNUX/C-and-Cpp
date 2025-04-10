#include <Windows.h>
#include <stdio.h>
#include <string.h>

unsigned long long  hash(char *str)
{
    unsigned long long  hasher = 14695981039346656037ULL, prime = 1099511628211;

    while               (*str) hasher ^= (unsigned char)(*str), hasher *= prime, str++;

    return              hasher;
}
typedef struct      allocator
{
    struct basic_string *(*allocate)(size_t size);
    void                (*construct)(struct basic_string **ptr, char *str);
    void                (*destroy)(struct basic_string *ptr);
    void                (*deallocate)(void *ptr);
} allocator;
typedef struct      basic_string
{
    char        *data;
    size_t      size, capacity;
    allocator   get_allocator;
    size_t      max_size;
}                   basic_string;
static basic_string *Cbasic_string(char *str);
static basic_string *Cbasic_stringn(char *str, size_t size);
static basic_string *allocate(size_t size) {return (basic_string*)VirtualAlloc(NULL, size * sizeof(basic_string), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);}
static void         construct(struct basic_string **ptr, char *str) {*ptr = Cbasic_string(str);}
static void         constructn(struct basic_string **ptr, char *str) {*ptr = Cbasic_stringn(str, strnlen_s(str, _TRUNCATE));}
static void         destroy(struct basic_string *ptr)
{
    if          (!ptr) return;
    if          (ptr->data)
    {
        VirtualFree(ptr->data, 0, MEM_RELEASE);
        ptr->data = NULL;
    }
    
    ptr->size   = 0;
}
static void         deallocate(void *ptr) {if (ptr) {VirtualFree(ptr, 0, MEM_RELEASE);}}
static basic_string *Cbasic_string(char *str)
{
    size_t size                     = strnlen_s(str, _TRUNCATE), len = (size) ? size : 0;

    if                              (!size) size = 1;
    
    basic_string                    *new = (basic_string*)VirtualAlloc(NULL, sizeof(basic_string), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if                              (!new) ExitProcess(1);

    new->data                       = (char*)VirtualAlloc(NULL, len + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if                              (!new->data) ExitProcess(1);
    
    strncpy_s(new->data, size + 1, str, size);

    size_t                          capacity = 15;

    while                           (size > capacity)
    {
        if          (capacity > 0xfffffffffffffff) break;

        capacity    += 16;
    }

    new->size                       = size;
    new->capacity                   = capacity;
    new->get_allocator.allocate     = allocate;
    new->get_allocator.construct    = construct;
    new->get_allocator.destroy      = destroy;
    new->get_allocator.deallocate   = deallocate;
    new->max_size                   = 0x7fffffffffffffff;

    return                  new;
}
static basic_string *Cbasic_stringn(char *str, size_t size)
{   
    basic_string                    *new = (basic_string*)VirtualAlloc(NULL, sizeof(basic_string), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if                              (!new) ExitProcess(1);

    new->data                       = (char*)VirtualAlloc(NULL, size + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if                              (!new->data) ExitProcess(1);
    
    strncpy_s(new->data, size + 1, str, size);

    size_t                          capacity = 15;

    while                           (size > capacity)
    {
        if          (capacity > 0xfffffffffffffff) break;

        capacity    += 16;
    }
    
    new->size                       = size;
    new->capacity                   = capacity;
    new->get_allocator.allocate     = allocate;
    new->get_allocator.construct    = construct;
    new->get_allocator.destroy      = destroy;
    new->get_allocator.deallocate   = deallocate;
    new->max_size                   = 0x7fffffffffffffff;

    return                  new;
}
static basic_string *Rbasic_string(basic_string *basic_string, char *str)
{
    VirtualFree(basic_string->data, 0, MEM_RELEASE);
    VirtualFree(basic_string, 0, MEM_RELEASE);

    return  Cbasic_string(str);
}
static basic_string *Rbasic_stringn(basic_string *basic_string, char *str, size_t size)
{
    VirtualFree(basic_string->data, 0, MEM_RELEASE);
    VirtualFree(basic_string, 0, MEM_RELEASE);

    return  Cbasic_stringn(str, size);
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
    size_t                  new_size = dest->size + count + 1;

    char                    *new_data = (char *)VirtualAlloc(NULL, new_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if                      (!new_data) ExitProcess(1);

    strncpy_s(new_data, new_size, dest->data, dest->size);

    strncat_s(new_data, new_size, str, count);

    VirtualFree(dest->data, 0, MEM_RELEASE);

    size_t                  capacity = 15;

    while                   (new_size - 1 > capacity)
    {
        if          (capacity > 0xfffffffffffffff) break;

        capacity    += 16;
    }

    dest->data              = new_data;
    dest->size              = new_size - 1;
    dest->capacity          = capacity;
}
static void         append_basic_string(basic_string *dest, basic_string *str) {append_substr(dest, str->data, strnlen_s(str->data, SIZE_MAX));}
static void         append_repeated_char(basic_string *dest, size_t count, char char_value)
{
    size_t                  new_size = dest->size + count + 1;

    char                    *new_data = (char *)VirtualAlloc(NULL, new_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if                      (!new_data) ExitProcess(1);

    strncpy_s(new_data, new_size, dest->data, dest->size);
    
    memset(new_data + dest->size - 1, char_value, count);

    new_data[new_size - 1]  = 0;

    VirtualFree(dest->data, 0, MEM_RELEASE);

    size_t                  capacity = 15;

    while                   (new_size - 1 > capacity)
    {
        if          (capacity > 0xfffffffffffffff) break;

        capacity    += 16;
    }

    dest->data              = new_data;
    dest->size              = new_size - 1;
    dest->capacity          = capacity;
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
    
    new_data[new_size]  = 0;

    if                  (dest->data) VirtualFree(dest->data, 0, MEM_RELEASE);

    size_t              capacity = 15;

    while               (new_size - 1 > capacity)
    {
        if          (capacity > 0xfffffffffffffff) break;

        capacity    += 16;
    }
    
    dest->data          = new_data;
    dest->size          = new_size;
    dest->capacity      = capacity;
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
    
    new_data[count] = 0;

    if              (dest->data) VirtualFree(dest->data, 0, MEM_RELEASE);

    size_t          capacity = 15;

    while           (count > capacity)
    {
        if          (capacity > 0xfffffffffffffff) break;

        capacity    += 16;
    }
    
    dest->data      = new_data;
    dest->size      = count;
    dest->capacity  = capacity;
}
static void         assign_range(basic_string *dest, char *first, char *last)
{
    if (first >= last) return;

    assign_n(dest, first, strnlen_s(first, last - first));
}
static int          compare(char *str1, size_t pos1, size_t num1, char *str2, size_t pos2, size_t num2)
{
    if      (!str1 || !str2) return (str1 == str2) ? 0 : (str1 ? 1 : -1);

    size_t  len1 = strnlen_s(str1, _TRUNCATE);
    size_t  len2 = strnlen_s(str2, _TRUNCATE);

    if      (pos1 > len1) return -1;
    if      (pos2 > len2) return 1;

    char    *sub1 = str1 + pos1;
    char    *sub2 = str2 + pos2;
    size_t  max_cmp1 = (num1 == -1) ? len1 - pos1 : num1, max_cmp2 = (num2 == -1) ? len2 - pos2 : num2, cmp_len = (max_cmp1 < max_cmp2) ? max_cmp1 : max_cmp2;
    int     result = strncmp(sub1, sub2, cmp_len);

    if      (!result)
    {
        if (max_cmp1 < max_cmp2) return -1;
        if (max_cmp1 > max_cmp2) return 1;
    }

    return  result;
}
static int          compare_full(char *str1, char *str2) {return compare(str1, 0, -1, str2, 0, -1);}
static int          compare_substring(char *str1, size_t pos1, size_t num1, char *str2) {return compare(str1, pos1, num1, str2, 0, -1);}
static int          compare_substrings(char *str1, size_t pos1, size_t num1, char *str2, size_t pos2, size_t num2) {return compare(str1, pos1, num1, str2, pos2, num2);}
static void         erase_range(int *arr, size_t *size, size_t first, size_t last)
{
    if      (first >= last || last > *size) return;

    memmove_s(&arr[first], (*size - first) * sizeof(arr[0]), &arr[last], (*size - last) * sizeof(arr[0]));
    
    *size   -= (last - first);
}
static void         erase_at(int *arr, size_t *size, size_t index)
{
    if (index >= *size) return;

    memmove_s(&arr[index], (*size - index) * sizeof(arr[0]), &arr[index + 1], (*size - index - 1) * sizeof(arr[0]));
    
    (*size)--;
}
static void         erase_substr(char *str, size_t *size, size_t offset, size_t count)
{
    if          (offset >= *size) return;
    if          (offset + count > *size) count = *size - offset;
    
    memmove_s(&str[offset], (*size - offset) * sizeof(char), &str[offset + count], (*size - (offset + count)) * sizeof(char));

    *size       -= count;
    str[*size]  = 0;
}
static size_t       find_char(char *str, char ch, size_t offset)
{
    if      (!str) return -1;

    char    *pos = strchr(str + offset, ch);

    return  pos ? (size_t)(pos - str) : -1;
}
static size_t       find_str(char *str, char *substr)
{
    if      (!str || !substr) return -1;

    char    *pos = strstr(str, substr);
    
    return  pos ? (size_t)(pos - str) : -1;
}
static size_t       find_substr(char *str, char *substr, size_t offset)
{
    if      (!str || !substr) return -1;

    char    *pos = strstr(str + offset, substr);
    
    return  pos ? (size_t)(pos - str) : -1;
}
static size_t       find_substr_n(char *str, char *substr, size_t offset, size_t count)
{
    if      (!str || !substr || !count) return -1;

    char    *pos = strstr(str + offset, substr);

    if      (!pos) return -1;

    return  !strncmp(pos, substr, count) ? (size_t)(pos - str) : -1;
}
static size_t       find_first_not_of(char *str, const char *chars, size_t max_len) {return  (strspn(str, chars) < strnlen_s(str, max_len)) ? strspn(str, chars) : -1;}
static size_t       find_first_not_of_char(char *str, char ch, size_t offset, size_t max_len)
{
    for     (size_t i = offset; i < strnlen_s(str, max_len); i++) if (str[i] != ch) return i;
    
    return  -1;
}
static size_t       find_first_not_of_set(char *str, char *set, size_t offset, size_t count)
{
    size_t  pos = strspn(str + offset, set);
    pos     += offset;

    return  (pos < strnlen_s(str, count)) ? pos : -1;
}
static size_t       find_first_not_of_string(char *str, char *target, size_t offset, size_t max_len) {return find_first_not_of_set(str, target, offset, strnlen_s(str, max_len) - offset);}
static size_t       find_first_of(char *str, char *chars)
{
    size_t  pos = strcspn(str, chars);

    return  (str[pos]) ? pos : -1;
}
static size_t       find_first_of_char(char *str, char ch, size_t offset)
{
    char    *pos   = strchr(str + offset, ch);

    return  (pos != NULL) ? (size_t)(pos - str) : -1;
}
static size_t       find_first_of_chars(char *str, char *chars, size_t offset)
{
    size_t  pos = strcspn(str + offset, chars);

    return  (str[offset + pos]) ? (offset + pos) : -1;
}
static size_t       find_first_of_chars_n(char *str, char *chars, size_t offset, size_t count)
{
    size_t  pos = strcspn(str + offset, chars);

    return  (pos < count && str[offset + pos]) ? (offset + pos) : -1;
}
static size_t       find_first_of_str(char *str, char *find_str, size_t offset)
{
    while   (str[offset])
    {
        if (strchr(find_str, str[offset])) return offset;

        offset++;
    }

    return  -1;
}
static size_t       find_last_not_of_char(char *str, size_t str_size, char ch)
{
    if      (!str || !str_size) return (size_t)-1;

    size_t  len = strnlen_s(str, str_size);

    for     (size_t i = len; i-- > 0;) if (str[i] != ch) return i;

    return  -1;
}
static size_t       find_last_not_of_char_n(char *str, size_t str_size, char ch, size_t offset)
{
    if      (!str || !str_size) return -1;

    size_t  len = strnlen_s(str, str_size);

    if      (offset >= len) offset = len - 1;

    for     (size_t i = offset + 1; i-- > 0;) if (str[i] != ch) return i;

    return  -1;
}
static size_t       find_last_not_of_str(char *str, size_t str_size, char *chars, size_t offset)
{
    if      (!str || !chars || !str_size) return (size_t)-1;

    size_t  len = strnlen_s(str, str_size);

    if      (offset >= len) offset = len - 1;

    for     (size_t i = offset + 1; i-- > 0;) if (!strchr(chars, str[i])) return i;

    return  -1;
}
static size_t       find_last_not_of_str_n(char *str, size_t str_size, char *chars, size_t offset, size_t count)
{
    if      (!str || !chars || !str_size || !count) return (size_t)-1;

    size_t  len = strnlen_s(str, str_size);

    if      (offset >= len) offset = len - 1;

    for     (size_t i = offset + 1; i-- > 0;) if (!memchr(chars, str[i], count)) return i;

    return  -1;
}
static size_t find_last_of_char( char *str, char char_value)
{
    size_t  len = strnlen_s(str, SIZE_MAX);

    for     (size_t i = len; i > 0; --i) if (str[i - 1] == char_value) return i - 1;

    return  SIZE_MAX;
}
static size_t       find_last_of_char_n(char *str, char char_value, size_t offset)
{
    size_t  len = strnlen_s(str, SIZE_MAX);

    if      (offset >= len) offset = len - 1;

    for     (size_t i = offset + 1; i > 0; --i) if (str[i - 1] == char_value) return i - 1;

    return  SIZE_MAX;
}
static size_t       find_last_of_set(char *str, const char *chars, size_t offset)
{
    size_t  len = strnlen_s(str, SIZE_MAX);

    if      (offset >= len) offset = len - 1;

    for     (size_t i = offset + 1; i > 0; --i) if (strrchr(chars, str[i - 1])) return i - 1;

    return  SIZE_MAX;
}
static size_t       find_last_of_set_count(char *str, char *chars, size_t offset, size_t count)
{
    size_t  len = strnlen_s(str, SIZE_MAX);

    if      (offset >= len) offset = len - 1;

    size_t  start = (offset >= count) ? (offset - count + 1) : 0;

    for     (size_t i = offset + 1; i > start; --i) if (strrchr(chars, str[i - 1])) return i - 1;

    return  SIZE_MAX;
}
static basic_string *insert_str_basic_string(basic_string *bstr, size_t pos, char *insert)
{
    size_t  len1 = bstr->size;
    size_t  len2 = strnlen_s(insert, 4096);

    if      (pos > len1) return NULL;
    
    char    *new_data = (char *)VirtualAlloc(NULL, len1 + len2 + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if      (!new_data) ExitProcess(1);

    memcpy_s(new_data, len1 + len2 + 1, bstr->data, pos);
    memcpy_s(new_data + pos, len1 + len2 + 1 - pos, insert, len2);
    memcpy_s(new_data + pos + len2, len1 + len2 + 1 - pos - len2, bstr->data + pos, len1 - pos + 1);
    
    bstr    = Rbasic_string(bstr, new_data);

    return  bstr;
}
static basic_string *insert_str_count_basic_string(basic_string *bstr, size_t pos, char *insert, size_t count)
{
    size_t  len1 = bstr->size;

    if      (pos > len1) return NULL;

    char    *new_data = (char *)VirtualAlloc(NULL, len1 + count + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if      (!new_data) ExitProcess(1);

    memcpy_s(new_data, len1 + count + 1, bstr->data, pos);
    memcpy_s(new_data + pos, len1 + count + 1 - pos, insert, count);
    memcpy_s(new_data + pos + count, len1 + count + 1 - pos - count, bstr->data + pos, len1 - pos + 1);

    bstr    = Rbasic_string(bstr, new_data);

    return  bstr;
}
static basic_string *insert_str_substr_basic_string(basic_string *str1, size_t pos, basic_string *str2, size_t offset, size_t count)
{
    if      (offset > str2->size || offset + count > str2->size) return NULL;

    return  insert_str_count_basic_string(str1, pos, str2->data + offset, count);
}
static basic_string *insert_repeat_char_basic_string(basic_string *bstr, size_t pos, size_t count, char ch)
{
    size_t  len = bstr->size;
    
    if      (pos > len) return NULL;

    char    *new_data = (char *)VirtualAlloc(NULL, len + count + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if      (!new_data) ExitProcess(1);

    memcpy_s(new_data, len + count + 1, bstr->data, pos);
    
    memset(new_data + pos, ch, count);
    
    memcpy_s(new_data + pos + count, len + count + 1 - pos - count, bstr->data + pos, len - pos + 1);

    bstr    = Rbasic_string(bstr, new_data);

    return  bstr;
}
static basic_string *insert_iter_char_basic_string(basic_string *bstr, char *iter, char ch) {return insert_repeat_char_basic_string(bstr, iter - bstr->data, 1, ch);}
static basic_string *insert_iter_range_basic_string(basic_string *bstr, char *iter, char *first, char *last) {return insert_str_count_basic_string(bstr, iter - bstr->data, first, last - first);}
static basic_string *insert_iter_repeat_basic_string(basic_string *bstr, char *iter, size_t count, char ch) {return insert_repeat_char_basic_string(bstr, iter - bstr->data, count, ch);}
static void         pop_back(basic_string **str)
{
    if                  (!str || !*str || (*str)->size <= 1) return;

    size_t              new_size = (*str)->size;

    char                temp[4096];

    errno_t             err = memcpy_s(temp, sizeof(temp), (*str)->data, new_size);
    
    if                  (err) return;

    temp[new_size - 1]  = 0;

    *str                = Rbasic_string(*str, temp);
}
static void         push_back(basic_string **str_ptr, char ch)
{
    if                      (!str_ptr || !*str_ptr) return;

    basic_string            *str = *str_ptr;
    // Allocate a new buffer for the extended string (old size + 1 char + null)
    char                    *new_data = (char*)VirtualAlloc(NULL, str->size + 2, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if                      (!new_data) ExitProcess(1);

    // Copy old string into new buffer
    memcpy_s(new_data, str->size + 2, str->data, str->size);

    // Append the new character and null terminator
    new_data[str->size]     = ch;
    new_data[str->size + 1] = 0;

    // Replace the old basic_string with a new one
    *str_ptr                = Rbasic_stringn(str, new_data, str->size + 1);

    // Free temporary buffer
    VirtualFree(new_data, 0, MEM_RELEASE);
}
int                 main()
{
    basic_string                                                    *str1 = Cbasic_string("Hello");
    basic_string                                                    *str2 = Cbasic_string("World");
    //  Concatenation
    basic_string                                                    *result = Cbasic_stringn("", str1->size + strnlen_s(", ", _TRUNCATE) + str2->size + strnlen_s("!", _TRUNCATE));

    _snprintf_s(result->data, result->size + 1, _TRUNCATE, "%s, %s!", str1->data, str2->data);

    fprintf_s(stdout, "%s\n", result->data);
    //  Getting string length
    fprintf_s(stdout, "Length: %llu\n", strnlen_s(result->data, result->size));
    //  Accessing characters
    fprintf_s(stdout, "First character: %c\n", result->data[0]);

    //  Modifying a string
    result->data[0]                                                 = 'h';

    fprintf_s(stdout, "Modified string: %s\n", result->data);

    //  Substring
    basic_string                                                    *sub = Cbasic_stringn("", 6);

    strncpy_s(sub->data, sub->size + 1, result->data, 5);

    fprintf_s(stdout, "Substring: %s\n", sub->data);

    //  Finding a substring
    size_t                                                          pos = find_str(result->data, "World");

    if                                                              (pos != -1) fprintf_s(stdout, "'World' found at position: %llu\n", pos);

    //  Hash function (C++'s FNV-1a hash for demonstration)
    unsigned long long                                              hashValue = hash(result->data);

    fprintf_s(stdout, "Hash value: %llu\n", hashValue);
    //  Swap function
    fprintf_s(stdout, "Before swap: str1 = %s, str2 = %s\n", str1->data, str2->data);

    char                                                            tmp[6];
    
    strncpy_s(tmp, sizeof(tmp), str1->data, str1->size + 1);
    strncpy_s(str1->data, str1->size + 1, str2->data, str2->size + 1);
    strncpy_s(str2->data, str2->size + 1, tmp, sizeof(tmp));

    fprintf_s(stdout, "After swap: str1 = %s, str2 = %s\n", str1->data, str2->data);

    //  Convert string to integer using strtol
    basic_string                                                    *numberStr = Cbasic_string("12345");
    char                                                            *endptr;
    int                                                             number = strtol(numberStr->data, &endptr, 10);

    fprintf_s(stdout, "Converted number: %d\n", number);

    //  Convert number to string using _snprintf_s
    basic_string                                                    *numberToStr = Cbasic_stringn("", numberStr->size + 1);

    _snprintf_s(numberToStr->data, numberToStr->size + 1, _TRUNCATE, "%d", number);

    fprintf_s(stdout, "Converted string: %s\n", numberToStr->data);

    //  String comparison using strncmp
    if                          (strncmp(str1->data, str2->data, str1->size)) fprintf_s(stdout, "Strings are not equal.\n");

    char                                                            fullLine[255];

    //  Clear newline from previous input
    getchar();

    fprintf_s(stdout, "Enter a full line: ");

    //  Using fgets function
    if                                                              (fgets(fullLine, sizeof(fullLine), stdin))
    {
        size_t  len = strnlen_s(fullLine, sizeof(fullLine));

        if                                                          (len > 0 && fullLine[len - 1] == '\n') fullLine[len - 1] = 0;

        fprintf_s(stdout, "You entered: %s\n", fullLine);
    }

    //  Using basic_string struct
    basic_string                                                    *basicStr = Cbasic_string("Basic string example");

    fprintf_s(stdout, "Basic string: %s\n", basicStr->data);

    //  Using append function
    basic_string                                                    *appendStr = Cbasic_string(" Appended text.");

    append_basic_string(result, appendStr);

    fprintf_s(stdout, "After append: %s\n", result->data);

    //  Using assign function
    basic_string                                                    *assignStr = Cbasic_string("");

    assign(assignStr, "Assigned text.");

    fprintf_s(stdout, "After assign: %s\n", assignStr->data);

    //  Using at function
    char                                                            thirdChar = result->data[2];

    fprintf_s(stdout, "Character at index 2: %c\n", thirdChar);

    //  Using back function
    char                                                            lastChar = result->data[result->size - 1];

    fprintf_s(stdout, "Last character: %c\n", lastChar);

    //  Using begin function
    char                                                            firstChar = *result->data;

    fprintf_s(stdout, "First character using begin: %c\n", firstChar);

    //  Using front function
    char                                                            frontChar = result->data[0];

    fprintf_s(stdout, "First character using front: %c\n", frontChar);

    //  Using capacity function

    fprintf_s(stdout, "String capacity: %lld\n", result->capacity);

    //  Using _strnset_s function
    _strnset_s(result->data, result->size + 1, 0, result->size + 1);

    fprintf_s(stdout, "String after clear: '%s' (should be empty)\n", result->data);

    //  Using compare function
    int                                                             compareResult = compare_full(str1->data, str2->data);

    if                                                              (!compareResult) puts("Strings are equal.");
    else if                                                         (compareResult < 0) puts("str1 is less than str2.");
    else                                                            puts("str1 is greater than str2.");

    //  Using strncpy_s function
    char                                                            buffer[50] = {0};
    size_t                                                          copiedChars;
    result                                                          = Rbasic_string(result, "Copy this string.");
    
    strncpy_s(buffer, sizeof(buffer), result->data, result->size);

    buffer[result->size]                                            = 0;

    fprintf_s(stdout, "Copied string: %s\n", buffer);

    //  Using data function
    const char                                                      *dataPtr = result->data;

    fprintf_s(stdout, "Data function output: %s\n", dataPtr);

    //  Using empty function
    fprintf_s(stdout, "Is result string empty? %s\n", !strncmp(result->data, "", result->size) ? "Yes" : "No");

    //  Using end function
    char                                                            lastCharUsingEnd = *(result->data + result->size - 1);

    fprintf_s(stdout, "Last character using end: %c\n", lastCharUsingEnd);

    //  Using erase function
    result                                                          = Rbasic_string(result, "Erase part of this string.");

    erase_substr(result->data, &result->size + 1, 6, 9);    //  Remove "part of "

    fprintf_s(stdout, "After erase: %s\n", result->data);

    //  Using find_first_not_of function
    basic_string                                                    *sample = Cbasic_string("###Hello###");
    size_t                                                          firstNotOf = find_first_not_of(sample->data, "#", strnlen_s(sample->data, _TRUNCATE));

    if                                                              (firstNotOf != -1) fprintf_s(stdout, "First character not '#': %c at position %llu\n", sample->data[firstNotOf], firstNotOf);
    else                                                            puts("No different characters found.\n");

    //  Using find_first_of function
    basic_string                                                    *findSample = Cbasic_string("abcdefg");
    size_t                                                          firstOf = find_first_of(findSample->data, "dc");

    if                                                              (firstOf != -1) fprintf_s(stdout, "First character found: %c at position %llu\n", findSample->data[firstOf], firstOf);
    else                                                            puts("No different characters found.\n");

    //  Using find_last_not_of function
    size_t                                                          lastNotOf = find_last_not_of_char(sample->data, sample->size + 1, '#');
    
    if                                                              (lastNotOf != -1) fprintf_s(stdout, "Last character not '#': %c at position %llu\n", sample->data[lastNotOf], lastNotOf);
    else                                                            puts("No different characters found.\n");

    //  Using find_last_of function
    size_t                                                          lastOf = find_last_of_char(sample->data, '#');

    if                                                              (lastOf != -1) fprintf_s(stdout, "Last occurrence of '#': at position %llu\n", lastOf);
    else                                                            puts("Character not found.\n");

    //  Using get_allocator function
    allocator                                                       alloc = result->get_allocator;  //  Get allocator from existing string
    basic_string                                                    *p = alloc.allocate(1); //  Allocate space for one string
    
    alloc.construct(&p, "Allocated string"); //  Construct the string in-place

    fprintf_s(stdout, "Allocated string using get_allocator: %s\n", p->data);

    alloc.destroy(p);   //  Destroy the string object

    alloc.deallocate(p);    //  Free the memory

    //  Using insert function
    result                                                          = Rbasic_string(result, "Say !");
    result                                                          = insert_str_basic_string(result, 4, "Hello");

    fprintf_s(stdout, "After insert: %s\n", result->data);
    //  Using max_size function
    fprintf_s(stdout, "Maximum size a string can hold: %lld\n", result->max_size);

    //  Using pop_back function
    result                                                          = Rbasic_string(result, "Remove last.");

    pop_back(&result);

    fprintf_s(stdout, "After pop_back: %s\n", result->data);

    //  Using push_back function
    push_back(&result, '?');    //  Appends a character at the end

    fprintf_s(stdout, "After push_back: %s\n", result->data);
    //  Using rbegin function
    fprintf_s(stdout, "Last character using rbegin: %c\n", *(result->data + result->size - 1));

    basic_string                                                    *All[] = {str1, str2, result, sub, numberStr, numberToStr, basicStr, appendStr, assignStr, sample, findSample};

    Dbasic_string(All, sizeof(All) / sizeof(All[0]));

    ExitProcess(0);
}