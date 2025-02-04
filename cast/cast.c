#include <stdio.h>
#include <Windows.h>
#include <setjmp.h>

typedef enum    type_info {TYPE_INT, TYPE_DOUBLE, TYPE_BASE, TYPE_DERIVED} type_info;
typedef struct  Base {type_info type;} Base; // Necessary for dynamic_cast
typedef struct  Derived
{
    Base    *Base;
    void    (*show)();
}               Derived;
Base            *CBase()
{
    Base        *new = GlobalAlloc(GPTR, sizeof(Base));

    if          (!new) ExitProcess(1);

    new->type   = TYPE_BASE;

    return      new;
}
Base            *DBase(Base *Base)
{
    GlobalFree(Base);

    return  Base;
}
void            show() {fprintf(stdout, "Derived class\n");}
Derived         *CDerived(Base *Base)
{
    Base            = CBase();
    Derived         *new = GlobalAlloc(GPTR, sizeof(Derived));

    if              (!new) ExitProcess(1);

    new->Base       = Base;
    new->Base->type = TYPE_DERIVED;
    new->show       = show;

    return          new;
}
Derived         *DDerived(Base *Base, Derived *Derived)
{
    Base    = DBase(Base);

    GlobalFree(Derived);

    return  Derived;
}
void            print(int *ptr) {fprintf(stdout, "Const_cast value: %d\n", *ptr);}
const char      *typeidname(type_info value)
{
    switch (value)
    {
        case        TYPE_INT: return "int";
        case        TYPE_DOUBLE: return "double";
        case        TYPE_BASE: return "struct Base";
        case        TYPE_DERIVED: return "struct Derived";
        default:    return "Unknown";
    }
}
jmp_buf         cast;
jmp_buf         typeid;
char            castvalue;
char            typeidvalue;
int             main()
{
    // static_cast (Safe conversions)
    double          pi = 3.14159;
    int             intpi = (int)pi;    // Convert double to int

    fprintf(stdout, "static_cast: %d\n", intpi);

    Base            *b1 = NULL;
    Derived         *d = CDerived(b1);
    b1              = d->Base;  // Upcast (safe)

    fprintf(stdout, "static_cast (Upcast): %s\n", typeidname(b1->type));

    // dynamic_cast (safe downcasting in polymorphism)
    Base            *b2 = NULL;
    b2              = (Base*)CDerived(b2);
    Derived         *d1 = (Derived*)b2; // Downcast

    if              (d1->Base->type == TYPE_DERIVED) d1->show();    // Successful cast

    Base            *b3 = CBase();
    Derived         *d2 = (Derived*)b3; // Undefined behavior if calling member of struct d2

    if              (b3->type != TYPE_DERIVED) fprintf(stderr, "dynamic_cast failed\n");

    // reinterpret_cast (Low-level bit reinterpretation)
    int             num = 65;
    char            *ch = (char*)&num;

    fprintf(stdout, "reinterpret_cast: %s\n", ch);  // May print 'A' if little-endian

    // const_cast (Removing constness)
    const int       constNum = 10;
    int             *modifiableNum = (int *)&constNum;
    *modifiableNum  = 20;   // Undefined behavior if constNum was in read-only memory

    print(modifiableNum);

    castvalue       = setjmp(cast);

    // bad_cast with dynamic_cast (Reference cast failure)
    if              (!castvalue)
    {
        Derived *ref = (Derived*)b3;

        if      (b3->type != TYPE_DERIVED) longjmp(cast, 1);
    }
    else            {fprintf(stderr, "bad_cast caught: Bad dynamic_cast!\n");}

    typeidvalue     = setjmp(typeid);

    if              (!typeidvalue)
    {
        Base    *ptr = NULL;

        if      (!ptr) longjmp(typeid, 1);

        fprintf(stdout, "%s\n", typeidname(ptr->type));
    }
    else            {fprintf(stderr, "bad_typeid caught: Attempted a typeid of NULL pointer!\n");}

    int             a = 42;
    double          b = 3.14;
    Base            *baseObj = CBase();
    Derived         *derivedObj = CDerived(baseObj);
    Base            *basePtr = derivedObj->Base;  // Polymorphic pointer
    type_info       typeA = TYPE_INT;
    type_info       typeB = TYPE_DOUBLE;
    type_info       typeBase = baseObj->type;
    type_info       typeDerived = derivedObj->Base->type;
    type_info       typeBasePtr = basePtr->type;

    // Print type names
    fprintf(stdout, "Type of a: %s\n", typeidname(typeA));
    fprintf(stdout, "Type of b: %s\n", typeidname(typeB));
    fprintf(stdout, "Type of baseObj: %s\n", typeidname(typeBase));
    fprintf(stdout, "Type of derivedObj: %s\n", typeidname(typeDerived));
    fprintf(stdout, "Type of *basePtr: %s\n", typeidname(typeBasePtr));

    // Compare types
    if              (typeA == TYPE_INT) fprintf(stdout, "a is an int.\n");
    if              (typeBase != typeDerived) fprintf(stdout, "baseObj and derivedObj have different types.\n");

    // Cleanup
    d               = DDerived(b1, d);
    b2              = DBase(b2);
    b3              = DBase(b3);
    derivedObj      = DDerived(baseObj, derivedObj);

    ExitProcess(0);
}