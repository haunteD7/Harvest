#include "application.h"

#include "log.h"

Application::Application() {

}
Application::~Application() {

}

bool Application::start() {
  if(!init())
    return false;
  while (on_update()) {
  
  }

  return true;
}
bool Application::init() {

  return true;
}
bool Application::on_update() {
  

  return true;
}

