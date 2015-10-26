#pragma once
#ifndef MOBILE_APP_H
#define MOBILE_APP_H
#include "Object.h"
#include "Scene.h"
#include "MobileDevice.h"

namespace mobile
{

class App : public Object
{
public:
  explicit App(int* argc, char* argv[])
    : argc_(argc),
      argv_(argv),
      scene_(),
      cube_(),
      sphere_(),
      cone_(),
      mDevice_()
  {
  }

  void initContext();
  void run();

  void display();
  void resize(int w, int h);
  void mouse(int button, int state, int x, int y);
  void keyboard(unsigned char key, int x, int y);

  MobileDevice* mobileDevice() { return &mDevice_; }

private:
  virtual void preFrame();
  virtual void draw();
  virtual void intraFrame();
  virtual void postFrame();

  int* argc_;
  char** argv_;

  Scene scene_;
  Cube cube_;
  Sphere sphere_;
  Cone cone_;
  
  MobileDevice mDevice_;
};

}

#endif
