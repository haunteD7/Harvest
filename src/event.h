#pragma once

#include "types.h"

#include <string>

#define REGISTER_EVENT(x) virtual u32 get_event_type() const override { return x; } \
                          virtual std::string get_event_string() override { return #x; }
class BaseEvent {
public:
  BaseEvent(){}
  virtual ~BaseEvent(){}

  virtual u32 get_event_type() const = 0;
  virtual std::string get_event_string() = 0;
};
