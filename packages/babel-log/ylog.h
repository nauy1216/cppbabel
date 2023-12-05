#ifndef BABEL_YLOG_H_
#define BABEL_YLOG_H_

#include <string>
#include <fstream>
#include <cassert>
#include <ctime>

using namespace std;

class YLog
{
private:
  std::ofstream of_;
  int minlevel_;

public:
  enum Type
  {
    ADD = 0,
    OVER
  };

  enum Level
  {
    DEBUG = 0,
    INFO,
    ERR
  };

  YLog(const int level, const std::string &logfile, const int type = YLog::OVER) : minlevel_(level)
  {
    assert((this->ERR == level || this->INFO == level || this->DEBUG == level) && "Logfile create failed, please check the level(YLog::ERR or YLog::INFO or YLog::DEBUG.");

    if (type == this->ADD)
    { // 如果是添加
      this->of_.open(logfile.c_str(), std::ios_base::out | std::ios_base::app);
    }
    else if (type == this->OVER)
    { // 如果是覆盖
      this->of_.open(logfile.c_str(), std::ios_base::out | std::ios_base::trunc);
    }
    else
    {
      assert(0 && "Logfile create failed, please check the type(YLog::OVER or YLog::ADD).");
    }

    assert(this->of_.is_open() && "Logfile create failed, please check the logfile's name and path.");

    return;
  }

  ~YLog()
  {
    if (this->of_.is_open())
    {
      this->of_.close();
    }
    return;
  }

  void openFileCheck() {
    assert(this->of_.is_open() && "Logfile write failed.");
  };

  void writeDateTime()
  {
    time_t sectime = time(NULL);
    tm tmtime;
#ifdef _WIN32
#if _MSC_VER < 1600
    tmtime = *localtime(&sectime);
#else
    localtime_s(&tmtime, &sectime);
#endif
#else
    localtime_r(&sectime, &tmtime);
#endif
    // 年月日时分秒
    this->of_ << tmtime.tm_year + 1900 << '-' << tmtime.tm_mon + 1 << '-' << tmtime.tm_mday << ' ' << tmtime.tm_hour << ':' << tmtime.tm_min << ':' << tmtime.tm_sec;
  };

  void writeLevel(int level)
  {
    // 日志等级
    if (this->ERR == level)
    {
      this->of_ << " [ERROR] ";
    }
    else if (this->INFO == level)
    {
      this->of_ << " [INFO] ";
    }
    else if (this->DEBUG == level)
    {
      this->of_ << " [DEBUG] ";
    }
    else
    {
      assert(0 && "Log write failed, please check the level(YLog::ERR or YLog::INFO or YLog::DEBUG.");
    }
  };

  template <typename T>
  void writeContent(const T &value)
  {
    this->of_ << value;
  }

  void writeEndl(const string &codefile, const int codeline)
  {
    // 文件名:行号
    this->of_ << "        @at [" << codefile << ':' << codeline << "] ";
    // 换行
    this->of_ << std::endl;
  }

  // 定义的模版方法
  template <typename T>
  void writeFile(const std::string &codefile, const int codeline, const int level, const T &value)
  {
    this->openFileCheck();

    if (this->minlevel_ <= level)
    {
      // 时间
      this->writeDateTime();

      // 日志等级
      this->writeLevel(level);

      // 日志内容
      this->writeContent(value);

      // 换行
      this->writeEndl(codefile, codeline);
    }
  }
};
#endif // BABEL_YLOG_H_
