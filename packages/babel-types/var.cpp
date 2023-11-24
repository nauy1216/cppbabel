#ifndef BABEL_TYPES_VAR
#define BABEL_TYPES_VAR

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <any>
#include <variant>

namespace var
{
    class Any
    {
    private:
        std::string _type;
        std::any _value;

    public:
        /**
         * 取值
         */
        template <typename T>
        T value()
        {
            return std::any_cast<T>(_value);
        };

        /**
         * 赋值
         */
        void value(std::string type, std::any value)
        {
            this->_type = type;
            this->_value = value;
        };

        std::string type()
        {
            return _type;
        };
    };

};

#endif // BABEL_TYPES_VAR
