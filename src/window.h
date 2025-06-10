#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
  Window();
  ~Window();
private:
  GLFWwindow* _window;

  bool is_created;
};
