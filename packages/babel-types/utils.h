#ifndef BABEL_TYPES_UTILS_H_
#define BABEL_TYPES_UTILS_H_
#include <map>
#include <any>
#include <string>
using namespace std;

namespace utils
{
    template <typename T>
    bool shallowEqual(T actual, T expected);

    template <typename T>
    bool shallowEqual(T actual, T expected)
    {
        if (actual == expected) {
            return true;
        }
        return false;
    };

    // template <typename T, typename U>
    // void inherit(string key, T child, U parent);
}

#endif // BABEL_TYPES_UTILS_H_