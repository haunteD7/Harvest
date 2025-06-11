#pragma once

#include <memory>

#include "window.h"
#include "types.h"

class Application {
public:
  Application();
  ~Application();

  bool start();
private:
  bool init();
  bool on_update();

  std::unique_ptr<Window> _window;
};
