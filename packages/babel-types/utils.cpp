#ifndef BABEL_TYPES_UTILS
#define BABEL_TYPES_UTILS

#include <map>
#include <any>
#include <string>

namespace utils
{
    template <typename T>
    void iterateObjectProperties(const T &obj)
    {
        // 使用反射方式遍历对象的所有属性值
        for (const auto &member : obj)
        {
            std::cout << member << ": " << obj.*member << std::endl;
        }
    }

    template <typename T, typename U>
    bool shallowEqual(T actual, U expected, std::vector<std::string> props)
    {
        return true;
    };

    template <typename T, typename U>
    void inherit(string key, T child, U parent){

    };

}

#endif // BABEL_TYPES_UTILS