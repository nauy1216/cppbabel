#ifndef BABEL_SHARED_any_map_H_
#define BABEL_SHARED_any_map_H_
#include <string>
#include <any>
#include <map>
using namespace std;

#define undefined

namespace shared
{
    class Attr
    {
    private:
        any _value;
        string _name;
        bool _exist;

    public:
        Attr(string name, any value) : _name(name), _value(value)
        {
            _exist = true;
        };

        Attr()
        {
            _exist = false;
        };

        template <typename T>
        T value()
        {
            return std::any_cast<T>(_value);
        };

        void value(any newValue)
        {
            _exist = true;
            _value = newValue;
        };

        string name()
        {
            return _name;
        };

        void name(string newName)
        {
            _name = newName;
        };

        bool exist()
        {
            return _exist;
        };
    };

    struct AnyMap
    {
    private:
        map<string, Attr> _map;

    public:
        /**
         * 获取Attr对象
         */
        Attr get(string attrName)
        {
            auto it = _map.find(attrName);
            if (it != _map.end())
            {
                return it->second;
            }
            return Attr();
        }

        /**
         * 有就更新，没有就插入
         */
        AnyMap set(string attrName, any value)
        {
            _map.insert_or_assign(attrName, Attr(attrName, value));
            return *this;
        }

        template <typename T>
        T value(string attrName)
        {
            Attr attr = get(attrName);
            if (attr.exist())
            {
                return attr.value<T>();
            }
            throw std::runtime_error("不存在属性：" + attrName);
        }

        bool has(string attrName) {
            return get(attrName).exist();
        }

        // 获取值
        Attr operator[](string attrName)
        {
            return get(attrName);
        }

        // 赋值
        // Attr& operator[](string attrName) {
        //     return get(attrName);
        // }

    };

}

#endif // BABEL_SHARED_any_map_H_