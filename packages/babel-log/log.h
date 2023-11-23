#ifndef BABEL_LOG_
#define BABEL_LOG_
#include <string>
#include "ylog.h"

const std::string filePath = "/Users/liuchengyuan/Documents/clangspace/cppbabel/info.log";
YLog* _log;

YLog* getLoggerInstance() {
    if (_log != nullptr) {
        return _log;
    }
    _log = new YLog(YLog::INFO, filePath, YLog::ADD);
    return _log;
};

class Logger {
public:
    template<typename T> static void Info(const T &value);
};

template<typename T> void Logger::Info(const T &value) {
    getLoggerInstance() -> W(YLog::INFO, "", value);
}

#endif // BABEL_LOG_
