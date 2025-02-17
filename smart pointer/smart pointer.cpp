#include <Windows.h>
#include <iostream>
#include <memory>

using namespace std;

//  A simple struct to demonstrate smart pointers
struct MyStruct
{
    MyStruct()      {cout << "MyStruct Constructor\n";}
    ~MyStruct()     {cout << "MyStruct Destructor\n";}
    void sayHello() {cout << "Hello from MyStruct\n";}
};
int main()
{
    cout    << "Using unique_ptr:\n";
    {
        //  unique_ptr (exclusive ownership)
        unique_ptr<MyStruct>    uniquePtr = make_unique<MyStruct>();

        uniquePtr->sayHello();
    }   //  uniquePtr goes out of scope here, and MyStruct is destroyed.

    cout    << "\nUsing shared_ptr:\n";
    {
        //  shared_ptr (shared ownership)
        shared_ptr<MyStruct>    sharedPtr1 = make_shared<MyStruct>();
        {
            shared_ptr<MyStruct>    sharedPtr2 = sharedPtr1;    // shared ownership

            sharedPtr2->sayHello();
        }   //  sharedPtr2 goes out of scope, but sharedPtr1 still exists.

        sharedPtr1->sayHello();
    }   //  sharedPtr1 goes out of scope here, and MyStruct is destroyed.

    cout    << "\nUsing weak_ptr:\n";
    {
        // shared_ptr (shared ownership) and weak_ptr (non-owning)
        shared_ptr<MyStruct>    sharedPtr1 = make_shared<MyStruct>();
        weak_ptr<MyStruct>      weakPtr = sharedPtr1;   // weak pointer does not affect ownership
        {
            // Lock weak_ptr to get a shared_ptr
            shared_ptr<MyStruct>    sharedPtr2 = weakPtr.lock();

            if                      (sharedPtr2) sharedPtr2->sayHello();
            else                    cout << "The object was already destroyed.\n";
        }   //  sharedPtr2 goes out of scope here

        //  After sharedPtr1 is destroyed, weakPtr will no longer be able to lock the object
        sharedPtr1.reset(); // Manually resetting sharedPtr1

        shared_ptr<MyStruct>    sharedPtr3 = weakPtr.lock();

        if                      (sharedPtr3) sharedPtr3->sayHello();
        else                    cout << "The object was already destroyed (after reset).\n";
    }   //  sharedPtr1 goes out of scope here, and MyStruct is destroyed.

    ExitProcess(0);
}
