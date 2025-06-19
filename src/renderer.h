#pragma once

#include "types.h"

class Renderer {
public:
  Renderer();
  ~Renderer();

  static bool system_start();
  static void system_stop();
  static bool is_system_initialized() { return _is_system_initialized; }

  void set_clear_color(const float r, const float g, const float b, const float a);
  void clear();
  void set_viewport(const u32 width, const u32 height);
private:
  static bool _is_system_initialized;
};
