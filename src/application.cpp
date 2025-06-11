#include "application.h"
#include "log.h"

Application::Application() : _window(nullptr) {
  LOG_INIT();

}
Application::~Application() {
  _window.release();
  Window::system_stop();
}

bool Application::start() {
  if(!init())
    return false;
  while (on_update()) {
  
  }

  LOG_INIT();
  return true;
}
bool Application::init() {
  if(!Window::system_start()) return false;
  _window = std::make_unique<Window>(Window());
  if(!_window->create(1280, 720, "Harvest")) return false;
  if(!_window->open()) return false;

  _window->add_event_listener(Close, [&](const WindowEvent& e){
    _window->close();
  });

  LOG_INIT();
  return true;
}
bool Application::on_update() {
  if(!_window->is_open())
    return false;

  _window->poll_events();
  _window->swap_buffers();

  return true;
}

