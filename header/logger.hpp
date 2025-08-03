#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <fstream>
#include <mutex>
#include <string>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, FATAL };

class Logger {
private:
  std::fstream log_file_;
  LogLevel level_;
  std::mutex logger_lock_;

public:
  Logger() = delete;
  Logger(const std::string &name);
  ~Logger();

  void setLevel(LogLevel level);

  void printLog(const std::string &content, LogLevel level);
};
#endif