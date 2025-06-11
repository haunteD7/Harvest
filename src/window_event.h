#pragma once

#include "event.h"

enum WindowEventType : u32 {
  Close = 0,
  Resize,

  Count
};

class WindowEvent : public BaseEvent {
public:
  WindowEvent(){}
  virtual ~WindowEvent(){}
};

class WindowCloseEvent : public WindowEvent {
public:
  WindowCloseEvent() {

  }
  ~WindowCloseEvent() {}

  REGISTER_EVENT(WindowEventType::Close);
};
class WindowResizeEvent : public WindowEvent {
public:
  WindowResizeEvent() {

  }
  virtual ~WindowResizeEvent() {}

  REGISTER_EVENT(WindowEventType::Resize);

private:
  u32 x, y;
};
