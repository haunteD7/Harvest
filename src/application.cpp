#include "application.h"
#include "log.h"


Application::Application() {
  LOG_INIT();
}
Application::~Application() {
}

bool Application::start() {
  if(!init())
    return false;
  while (on_update()) {}
  LOG_INIT();
  return true;
}
void Application::shutdown() {
  Renderer::system_stop();
  Window::system_stop();
}
bool Application::init() {
  // Window initialization
  if(!Window::system_start()) return false;
  _window = Window();
  if(!_window.create(1280, 720, "Harvest")) return false;
  if(!_window.open()) return false;

  // Renderer initialization
  if(!Renderer::system_start()) return false;
  _renderer = Renderer();

  // Event callbacks
  _window.add_event_listener(Close, [&](const WindowEvent& event){
    _window.close();
  });
  _window.add_event_listener(Keyboard, [&](const WindowEvent& event){
    auto e = static_cast<const WindowKeyboardEvent&>(event);
  });
  _window.add_event_listener(Resize, [&](const WindowEvent& event){
    auto e = static_cast<const WindowResizeEvent&>(event);
    _renderer.set_viewport(e.get_x(), e.get_y());

  });

  LOG_INIT();
  return true;
}
bool Application::on_update() { // Main loop
  if(!_window.is_open())
    return false;

  _renderer.set_clear_color(0.5f, 0.5f, 0.5f, 1.f);
  _renderer.clear();

  _window.poll_events();
  _window.swap_buffers();

  return true;
}

