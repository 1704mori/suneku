#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

namespace common
{

  enum class LogLevel
  {
    INFO,
    WARNING,
    ERROR,
    DEBUG,
    TRACE
  };

  class Logger
  {
  public:
    Logger(const std::string &name, bool logToFile = false, const std::string &logFile = "");
    ~Logger();

    void log(LogLevel level, const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
    void debug(const std::string &message);
    void trace(const std::string &message);

    void clear();

  private:
    static LogLevel minLogLevel;
    std::string name;
    bool logToFile;
    std::ofstream logFileStream;

    std::string getCurrentTimestamp();
  };

  extern Logger *logger;

} // namespace common
