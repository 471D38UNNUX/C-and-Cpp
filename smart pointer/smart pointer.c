#include <Windows.h>
#include <stdio.h>

// A simple struct to demonstrate smart pointers
typedef struct      MyStruct {void (*sayHello)();} MyStruct;
typedef struct      shared_ptr
{
    MyStruct    *ptr;
    int         *refCount;
}                   shared_ptr;
typedef struct      WeakPtr {shared_ptr *shared_ptr;} WeakPtr;
static void         sayHello() {fprintf_s(stdout, "Hello from MyStruct\n");}
static MyStruct     *CMyStruct()
{
    MyStruct        *new = (MyStruct *)malloc(sizeof(MyStruct));

    if              (!new) ExitProcess(1);

    fprintf_s(stdout, "MyStruct Constructor\n");

    new->sayHello   = sayHello;

    return          new;
}
static void         DMyStruct(MyStruct *myStruct)
{
    fprintf_s(stdout, "MyStruct Destructor\n");

    free(myStruct);
}
static shared_ptr   *make_shared(MyStruct *ptr)
{
    shared_ptr          *shared = (shared_ptr *)malloc(sizeof(shared_ptr));

    if                  (!shared) ExitProcess(1);

    shared->ptr         = ptr;
    shared->refCount    = (int *)malloc(sizeof(int));

    if                  (!shared->refCount) ExitProcess(1);

    *shared->refCount   = 1;

    return              shared;
}
static void             add_ref(shared_ptr *shared_ptr) {(*shared_ptr->refCount)++;}
static void             reset(shared_ptr *shared_ptr)
{
    (*shared_ptr->refCount)--;

    if (!*shared_ptr->refCount)
    {
        free(shared_ptr->refCount);

        DMyStruct(shared_ptr->ptr);

        free(shared_ptr);
    }
}
static WeakPtr          *make_weak(shared_ptr *shared_ptr)
{
    WeakPtr             *weak = (WeakPtr *)malloc(sizeof(WeakPtr));

    if                  (!weak) ExitProcess(1);

    weak->shared_ptr    = shared_ptr;

    return              weak;
}   
static shared_ptr       *lock(WeakPtr *WeakPtr)
{
    if      (WeakPtr->shared_ptr && *WeakPtr->shared_ptr->refCount > 0) return WeakPtr->shared_ptr;

    return  NULL;
}
int                     main()
{
    fprintf_s(stdout, "Using unique_ptr:\n");
    {
        //  unique_ptr (exclusive ownership)
        MyStruct    *uniquePtr = CMyStruct();

        uniquePtr->sayHello();

        DMyStruct(uniquePtr);
    }   //  uniquePtr goes out of scope here, and MyStruct is destroyed.

    fprintf_s(stdout, "\nUsing shared_ptr:\n");
    {
        MyStruct    *sharedPtr1 = CMyStruct();
        {
            //  shared_ptr (shared ownership)
            shared_ptr  *sharedPtr2 = make_shared(sharedPtr1);

            add_ref(sharedPtr2); // shared ownership

            sharedPtr2->ptr->sayHello();

            reset(sharedPtr2);
        }   //  sharedPtr2 goes out of scope, but sharedPtr1 still exists.
        
        sharedPtr1->sayHello();

        DMyStruct(sharedPtr1);
    }   //  sharedPtr1 goes out of scope here, and MyStruct is destroyed.

    fprintf_s(stdout, "\nUsing weak_ptr:\n");
    {
        MyStruct    *myStruct = CMyStruct();
        //  shared_ptr (shared ownership) and weak_ptr (non-owning)
        shared_ptr  *sharedPtr1 = make_shared(myStruct);
        WeakPtr     *weakPtr = make_weak(sharedPtr1);  //  weak pointer does not affect ownership
        {
            //  Lock weak_ptr to get a shared_ptr
            shared_ptr  *sharedPtr2 = lock(weakPtr); // Try to lock weak_ptr to get shared ownership

            if          (sharedPtr2) sharedPtr2->ptr->sayHello();
            else        fprintf_s(stdout, "The object was already destroyed.\n");
        }   //  sharedPtr2 goes out of scope here

        //  After sharedPtr1 is destroyed, weakPtr will no longer be able to lock the object
        reset(sharedPtr1);  // Manually resetting sharedPtr1
        weakPtr->shared_ptr = NULL;

        shared_ptr  *sharedPtr3 = lock(weakPtr);

        if          (sharedPtr3) sharedPtr3->ptr->sayHello();
        else        fprintf_s(stdout, "The object was already destroyed (after reset).\n");
    }   // sharedPtr1 goes out of scope here, and MyStruct is destroyed.

    ExitProcess(0);
}
