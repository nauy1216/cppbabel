#include <string>
#include <vector>
#include "utf8.h"
#include <iostream>

using namespace std;


template <typename INT_TYPE>
class Utf8String
{
private:
    string input;                // 输入的字符串
    vector<INT_TYPE> codepoints; // 解析后的unicode

    void getCodepoints()
    {
        // 先清空
        codepoints.clear();
        utf8::utf8to32(input.begin(), input.end(), std::back_inserter(codepoints));
    }

public:
    /**
     * 更新utfsting
    */
    void setInput(string i)
    {
        input = i;
        getCodepoints();
    };

    /**
     * 清空
    */
    void clear()
    {
        string i = "";
        setInput(i);
    };

    /**
     * 获取unicode字符数量
    */
    size_t getCodepointsSize()
    {
        return codepoints.size();
    };

    /**
     * 返回指定位置的unicode编码
    */
    INT_TYPE getCodeAt(INT_TYPE index)
    {
        // TODO 这里要判断数组越界？？？
        return codepoints.at(index);
    };

    /**
     * 返回指定unicode编码对应的字符
     *
     */
    INT_TYPE getStringByCode(INT_TYPE codepoint)
    {
        std::string utf8String;
        utf8::append(codepoint, std::back_inserter(utf8String));
        return utf8String;
    };


    /**
     * 返回指定返回的字符
     *
     */
    string getStringFrom(INT_TYPE start, INT_TYPE end)
    {
        std::string utf8String;
        size_t len = codepoints.size();
        for (int i = start; i < end; i++) {
            if (i < len) {
                utf8::append(getCodeAt(i), std::back_inserter(utf8String));
            } else {
                break;
            }
        }
        return utf8String;
    };


    /**
     * 返回utf8 string
    */
    string toString() {
        std::string utf8String;
        size_t len = codepoints.size();
        for (int i = 0; i < len; i++) {
            utf8::append(getCodeAt(i), std::back_inserter(utf8String));
        }
        return utf8String;
    };
};
