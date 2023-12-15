#ifndef TEST_BABEL_babel_parser_util_utf8
#define TEST_BABEL_babel_parser_util_utf8
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"
#include "babel-parser/util_utf8.h"

using namespace std;

namespace babel_parser_util_utf8
{
    Logger log(__FILE__);

    TEST(test_babel_parser, babel_parser__util_utf8)
    {
        std::cout << "【charCode】" << endl;

        Utf8String<uint32_t> utf8string;

        utf8string.setInput("ABC%^&*(()刘𠮷abcdefghijklmnopqrstuvwxyz");
        log << " utf8string.getCodepointsSize() " << utf8string.getCodepointsSize() << log.endl(__LINE__);
        for (int i = 0; i < utf8string.getCodepointsSize(); i++) {
            log << utf8string.getCodeAt(i) << utf8string.getStringByCode(utf8string.getCodeAt(i)) << " ";
        };
        log << log.endl(__LINE__);

        utf8string.setInput("ABC%^&*(()刘𠮷abcdefghijklmnopqrstuvwxyz");
        log << " utf8string.getCodepointsSize() " << utf8string.getCodepointsSize() << log.endl(__LINE__);
        for (int i = 0; i < utf8string.getCodepointsSize(); i++) {
            log << utf8string.getCodeAt(i) << utf8string.getStringByCode(utf8string.getCodeAt(i)) << " ";
        };
        log << log.endl(__LINE__);

        log << utf8string.toString() << log.endl(__LINE__);
    }

}
#endif // TEST_BABEL_babel_parser_util_utf8