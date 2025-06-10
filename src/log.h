#pragma once

// ================ DEFINES ================

#define LOG_INFO(...) Log::info(__VA_ARGS__)
#define LOG_WARN(...) Log::warn(__VA_ARGS__)
#define LOG_ERR(...) Log::err(__VA_ARGS__)

// ============= LOG FUNCTIONS =============
#include <cstdio>

#define MAX_LOG_LENGTH 8196

namespace Log {
  static char log_buffer[MAX_LOG_LENGTH];

  template<typename... Args>
  void info(const char* format, Args... args) {
    sprintf(log_buffer, format, args...);
    printf("[INFO]: %s\n", log_buffer);
  }
  template<typename... Args>
  void warn(const char* format, Args... args) {
    sprintf(log_buffer, format, args...);
    printf("[WARN]: %s\n", log_buffer);
  }
  template<typename... Args>
  void err(const char* format, Args... args) {
    sprintf(log_buffer, format, args...);
    printf("[ERROR]: %s\n", log_buffer);
  }
}
