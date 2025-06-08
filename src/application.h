#pragma once

class Application {
  public:
    Application();
    ~Application();

    bool start();
  private:
    bool init();
    bool on_update();

};
