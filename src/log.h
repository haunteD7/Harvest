#pragma once

// ================ DEFINES ================

// #define INIT_LOGGING // Enables logging constructors and init functions stuff
// #define EVENTS_LOGGING // Enables logging events

#define LOG_INFO(...) Log::info(__VA_ARGS__)
#define LOG_WARN(...) Log::warn(__VA_ARGS__)
#define LOG_ERR(...) Log::err(__VA_ARGS__)

#ifdef INIT_LOGGING
#define LOG_INIT() LOG_INFO(__PRETTY_FUNCTION__)
#else
#define LOG_INIT() 
#endif // INIT_LOGGING

#ifdef EVENTS_LOGGING
#define LOG_EVENT(...) LOG_INFO(__VA_ARGS__)
#else
#define LOG_EVENT(...) 
#endif // EVENTS_LOGGING

// ============= Terminal logging =============

#include <cstdio>

#define MAX_LOG_LENGTH 8196

namespace Log {
  static char log_buffer[MAX_LOG_LENGTH];

  template<typename... Args>
  void info(const char* format, Args... args) {
    sprintf(log_buffer, format, args...);
    printf("[\x1b[36mINFO\x1b[0m]: %s\n", log_buffer);
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
