#ifndef BABEL_REFLECT
#define BABEL_REFLECT

#include "libs/rttr/registration"

using namespace rttr;

struct MyStruct { MyStruct() {}; void func(double) {}; int data; };

RTTR_REGISTRATION
{
    registration::class_<MyStruct>("MyStruct")
         .constructor<>()
         .property("data", &MyStruct::data)
         .method("func", &MyStruct::func);
}

#endif // BABEL_REFLECT