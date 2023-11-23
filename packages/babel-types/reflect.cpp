#ifndef BABEL_TYPES_REFLECT
#define BABEL_TYPES_REFLECT

#include <map>
#include <any>
#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <utility>
#include <cstddef>


namespace reflect
{
    /**
        MyClass obj(42);
        auto it = &MyClass::myAttribute;
        std::cout << "Dynamic attribute value: " << getProperty(obj, it)<< std::endl;
    */
    // 模板函数，用于获取和设置对象的属性值
    template <typename T, typename U>
    U getProperty(const T &obj, U T::*attr)
    {
        return obj.*attr;
    }

    /**
     * setProperty(obj, it, 55)
     */
    template <typename T, typename U>
    void setProperty(T &obj, U T::*attr, U value)
    {
        obj.*attr = value;
    };
}

#endif // BABEL_TYPES_REFLECT