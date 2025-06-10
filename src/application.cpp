#include "application.h"
#include "log.h"

Application::Application() {
  LOG_INIT();
}
Application::~Application() {
  LOG_INIT();
}

bool Application::start() {
  LOG_INIT();

  if(!init())
    return false;
  while (on_update()) {
  
  }

  return true;
}
bool Application::init() {
  LOG_INIT();

  return true;
}
bool Application::on_update() {
  

  return true;
}

