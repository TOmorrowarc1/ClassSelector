#include "logger.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

auto levelToString(LogLevel level) -> std::string;

Logger::Logger(const std::string &name) {
  log_file_.open(name, std::ios::out | std::ios::trunc);
  if (!log_file_.good()) {
    std::cerr << "Error: cannot open the log file.\n";
  }
}

Logger::~Logger() { log_file_.close(); }

void Logger::setLevel(LogLevel level) { level_ = level; }

void Logger::printLog(const std::string &message, LogLevel level) {
  if (level >= level_) {
    auto time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::lock_guard<std::mutex> lock(logger_lock_);
    log_file_ << std::put_time(std::localtime(&time), "%Y-%m-%d %X") << " ["
              << levelToString(level) << "] " << message << '\n';
  }
}

auto levelToString(LogLevel level) -> std::string {
  std::string result;
  switch (level) {
  case LogLevel::DEBUG:
    result = "DEBUG";
    break;
  case LogLevel::INFO:
    result = "INFO";
    break;
  case LogLevel::WARNING:
    result = "WARNING";
    break;
  case LogLevel::ERROR:
    result = "ERROR";
    break;
  case LogLevel::FATAL:
    result = "FATAL";
    break;
  }
  return result;
}