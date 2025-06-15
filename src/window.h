#pragma once

#include <string>
#include <array>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "types.h"
#include "window_event.h"

using EventCallback = std::function<void(const WindowEvent&)>;

class Window {
public:
  Window();
  ~Window();

  static bool system_start();
  static void system_stop();
  static bool is_system_initialized() { return _is_system_initialized; }

  bool create(const u32 width, const u32 height, const std::string& title);
  bool is_created() const { return _is_created; }
  bool is_open() const { return _is_open; }
  bool open(bool fullscreen = false);
  bool close();
  void swap_buffers();

  void poll_events();
  void add_event_listener(WindowEventType event_type, EventCallback callback);
private:
  void handle_event(WindowEventType event_type, const WindowEvent& event);

  static bool _is_system_initialized;

  std::array<EventCallback, WindowEventType::Count> _event_callbacks;

  GLFWwindow* _window;

  u32 _width;
  u32 _height;
  bool _is_created;
  bool _is_open;
};
