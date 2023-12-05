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
    //
    bool isEnd;

    int codeline;

    void reset()
    {
        this->isEnd = false;
        this->codeline = 0;
    }

public:
    Logger(const string &codefile) : codefile(codefile)
    {
        this->log = new YLog(YLog::INFO, filePath, YLog::ADD);
        this->oss = new ostringstream();
        this->reset();
    };
    ~Logger()
    {
        delete this->log;
        delete this->oss;
    };

    template <typename T>
    Logger *Info(const T &value)
    {
        this->reset();
        // 注意这里不能写成 (this->oss) << value;
        *(this->oss) << value;
        return this;
    };

    void Endl(const int codeline)
    {
        this->log->writeFile(codefile, codeline, YLog::INFO, this->oss->str());
        // 输出完成之后清空
        delete this->oss;
        this->oss = new ostringstream(); 
    };

    string endl(const int codeline)
    {
        this->isEnd = true;
        this->codeline = codeline;
        return "";
    };

    template <typename T>
    Logger &operator<<(const T &value)
    {
        *(this->oss) << value;
        if (this->isEnd)
        {
            this->Endl(this->codeline);
        }
        this->reset();
        return *this;
    };
};
#endif // BABEL_LOG_H_
