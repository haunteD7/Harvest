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
  _is_system_initialized = false;
}
bool Window::create(const u32 width, const u32 height, const std::string& title) {
  // ============== initialization ================  
  if(!is_system_initialized()) {
    LOG_ERR("Window system not initialized");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if(!_window) {
    LOG_ERR("Window creation error");
    return false;
  }
  glfwMakeContextCurrent(_window);
  glfwSetWindowUserPointer(_window, this);

  _is_created = true;
  _width = width;
  _height = height;
  // ===============================================  

  // ================= CALLBACKS ===================  
  glfwSetWindowCloseCallback(_window, [](GLFWwindow* window){
    Window* this_window = (Window*)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    LOG_EVENT("%s", event.get_event_string().c_str());

    this_window->handle_event(Close, event);
  });
  glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int x, int y){
    Window* this_window = (Window*)glfwGetWindowUserPointer(window);
    this_window->_width = x;
    this_window->_height = y;
    WindowResizeEvent event(x, y);
    LOG_EVENT("%s: { %d; %d }", event.get_event_string().c_str(), event.get_x(), event.get_y());

    this_window->handle_event(Resize, event);
  });
  glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
    Window* this_window = (Window*)glfwGetWindowUserPointer(window);
    WindowKeyboardEvent event((KeyCodes)key, (KeyAction)action, (KeyModifiers)mods);
    LOG_EVENT("%s: %s", event.get_event_string().c_str(), event.get_key_name());

    this_window->handle_event(Keyboard, event);
  });
  // ===============================================  

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
void Window::add_event_listener(WindowEventType event_type, EventCallback callback) {
  _event_callbacks[event_type] = callback; 
}
void Window::handle_event(WindowEventType event_type, const WindowEvent& event) {
  if(_event_callbacks[event_type]) _event_callbacks[event_type](event);
}
void Window::swap_buffers() {
  glfwSwapBuffers(_window);
}
void Window::make_current() {
  glfwMakeContextCurrent(_window);
}
