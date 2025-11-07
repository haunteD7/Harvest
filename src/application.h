#pragma once

#include <memory>

#include "window.h"
#include "renderer.h"

class Application
{
public:
  Application();
  ~Application();

  bool start();
  void shutdown();

private:
  bool init();
  bool on_update();

  Window _window;
  Renderer _renderer;
};
