#pragma once

// ================ DEFINES ================

#define INIT_LOGGING

#define LOG_INFO(...) Log::info(__VA_ARGS__)
#define LOG_WARN(...) Log::warn(__VA_ARGS__)
#define LOG_ERR(...) Log::err(__VA_ARGS__)

#ifdef INIT_LOGGING

#define LOG_INIT() LOG_INFO(__PRETTY_FUNCTION__)

#else

#define LOG_INIT() 

#endif // INIT_LOGGING

// ============= LOG FUNCTIONS =============

#include <cstdio>

#define MAX_LOG_LENGTH 8196

namespace Log {
  static char log_buffer[MAX_LOG_LENGTH];

  template<typename... Args>
  void info(const char* format, Args... args) {
    sprintf(log_buffer, format, args...);
    printf("[\x1b[34mINFO\x1b[0m]: %s\n", log_buffer);
  }
  template<typename... Args>
  void warn(const char* format, Args... args) {
    sprintf(log_buffer, format, args...);
    printf("[\x1b[33mWARN\x1b[0m]: %s\n", log_buffer);
  }
  template<typename... Args>
  void err(const char* format, Args... args) {
    sprintf(log_buffer, format, args...);
    printf("[\x1b[31mERROR\x1b[0m]: %s\n", log_buffer);
  }
}
