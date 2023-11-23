#include <iostream>
#include "packages/test/babel-types.cpp"
#include "packages/test/babel-types-reflect.cpp"
#include "packages/babel-log/log.h"

int main()
{
    Logger::Info("执行main");
    test_babel_types();
    test_babel_types_reflect();
    return 0;
}
