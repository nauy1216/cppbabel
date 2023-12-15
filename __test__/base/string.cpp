#ifndef TEST_BABEL_base_string
#define TEST_BABEL_base_string
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"
#include "utf8.h"
#include <vector>

using namespace std;

/**
 * TODO: 怎么处理中文？？？
 * 1. 中文编码 https://zhuanlan.zhihu.com/p/234893634
 */

namespace base_string
{
    Logger log(__FILE__);

    TEST(test_base_string, base_string__)
    {
        std::cout << "【string】" << endl;

        std::string utf8String = "刘";

        std::cout << " .length ==> " << utf8String.length() << endl;
        std::cout << " utf8 ==> ";
        // 遍历 UTF-8 字符串
        for (int i = 0; i < utf8String.length(); i++)
        {
            string a = utf8String.substr(i, 3);
            std::cout << " 22 " << a.c_str() << " ";
        }

        std::cout << endl;
    }

    int codePointAtPos(const std::string &input, size_t pos)
    {
        if (pos < input.length())
        {
            char a = input.at(pos);
            int cp = static_cast<uint16_t>(input[pos]);
            std::cout << " cp ==> " << cp << endl;
            if ((cp & 0xFC00) == 0xD800 && ++pos < input.length())
            {
                int trail = static_cast<unsigned char>(input[pos]);
                if ((trail & 0xFC00) == 0xDC00)
                {
                    cp = 0x10000 + ((cp & 0x3FF) << 10) + (trail & 0x3FF);
                }
            }
            return cp;
        }
        else
        {
            // 处理索引越界，可以抛出异常或返回特殊值
            return -1;
        }
    };

    TEST(test_base_string, base_string__charCode)
    {
        std::cout << "【charCode】" << endl;

        std::string str = "刘𠮷abcdefghijklmnopqrstuvwxyz";
        std::vector<unsigned short> utf16result;
        utf8::utf8to16(str.begin(), str.end(), std::back_inserter(utf16result));
        std::cout << " utf16result.size() "  << utf16result.size() << endl;

        // for (int i = 0; i < utf16result.size(); i++) {
        //     std::cout << utf16result.at(i) << endl;
        // }
    }

}
#endif // TEST_BABEL_base_string