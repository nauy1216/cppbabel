#ifndef BABEL_LOG_H_
#define BABEL_LOG_H_
#include <string>
#include <sstream>

#include "ylog.h"

using namespace std;

const std::string filePath = "/Users/liuchengyuan/Documents/clangspace/cppbabel/info.log";

class Logger
{
private:
    // 输出代码所在的文件位置
    std::string codefile = "";
    // 写入本地文件
    YLog *log;
    // 缓存日志
    ostringstream *oss;

public:
    Logger(const string &codefile) : codefile(codefile)
    {
        this->log = new YLog(YLog::INFO, filePath, YLog::ADD);
        this->oss = new ostringstream();
    };
    ~Logger()
    {
        delete this->log;
        delete this->oss;
    };

    template <typename T>
    Logger *Info(const T &value)
    {
        // 注意这里不能写成 (this->oss) << value;
        *(this->oss) << value;
        return this;
    };

    void Endl(const int codeline)
    {
        this->log->writeFile(codefile, codeline, YLog::INFO, this->oss->str());
    };
};
#endif // BABEL_LOG_H_
