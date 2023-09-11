// Logger.cpp

#include "Logger.h"

namespace common
{

  // Initialize the minimum log level to INFO by default
  LogLevel Logger::minLogLevel = LogLevel::INFO;

  Logger *logger = nullptr;

  Logger::Logger(const std::string &name, bool logToFile, const std::string &logFile)
      : name(name), logToFile(logToFile)
  {
    if (logToFile && !logFile.empty())
    {
      logFileStream.open(logFile, std::ios::app);
    }
  }

  Logger::~Logger()
  {
    if (logFileStream.is_open())
    {
      logFileStream.close();
    }
  }

  void Logger::clear()
  {
    std::cout << std::flush;
  }

  void Logger::log(LogLevel level, const std::string &message)
  {
    if (static_cast<int>(level) >= static_cast<int>(minLogLevel))
    {
      std::ostringstream logStream;
      logStream << "[" << getCurrentTimestamp() << "] [" << name << "]: " << message;
      std::string logMessage = logStream.str();

      // Output to console
      std::cout << logMessage << std::endl;

      // Output to log file if enabled
      if (logToFile && logFileStream.is_open())
      {
        logFileStream << logMessage << std::endl;
      }
    }
  }

  void Logger::info(const std::string &message)
  {
    log(LogLevel::INFO, message);
  }

  void Logger::warning(const std::string &message)
  {
    log(LogLevel::WARNING, message);
  }

  void Logger::error(const std::string &message)
  {
    log(LogLevel::ERROR, message);
  }

  void Logger::debug(const std::string &message)
  {
    log(LogLevel::DEBUG, message);
  }

  void Logger::trace(const std::string &message)
  {
    log(LogLevel::TRACE, message);
  }

  std::string Logger::getCurrentTimestamp()
  {
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return timestamp;
  }

} // namespace common
