#include "window.h"
#include "log.h"

bool Window::_is_system_initialized = false;

Window::Window() {
  _event_callbacks = { nullptr };
  _window = nullptr;
  _is_created = false;
  _is_open = false;
  _width = 0;
  _height = 0;

  LOG_INIT();
}
Window::~Window() {
  glfwDestroyWindow(_window);
}
bool Window::system_start() {
  glfwSetErrorCallback([](int error_code, const char* description){
     LOG_ERR("GLFW error [%d]: %s", error_code, description);
  });

  if(!glfwInit()) {
    LOG_ERR("GLFW initialization error");
    return false;
  }
  Window::_is_system_initialized = true;

  LOG_INIT();
  return true;
}
void Window::system_stop() {
  glfwTerminate();  
}
bool Window::create(unsigned int width, unsigned int height, std::string title) {
  if(!is_system_initialized()) {
    LOG_ERR("Window system not initialized");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if(!_window) {
    LOG_ERR("Window creation error");
    return false;
  }
  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, this);

  // ================= CALLBACKS ===================  
  glfwSetWindowCloseCallback(_window, [](GLFWwindow* window){
    Window* this_window = (Window*)glfwGetWindowUserPointer(window);

    WindowCloseEvent e;

    if(this_window->_event_callbacks[WindowEventType::Close]) this_window->_event_callbacks[WindowEventType::Close](e);
  });
  // ===============================================  

  _is_created = true;
  _width = width;
  _height = height;

  LOG_INIT();
  return true;
}
bool Window::open(bool fullscreen) {
  _is_open = true;
  glfwShowWindow(_window);

  return true;
}
bool Window::close() {
  _is_open = false;
  glfwHideWindow(_window);

  return true;
}
void Window::poll_events() {
  glfwPollEvents();
}
void Window::add_event_listener(WindowEventType event, EventCallback callback) {
  _event_callbacks[event] = callback; 
}
void Window::swap_buffers() {
  glfwSwapBuffers(_window);
}
