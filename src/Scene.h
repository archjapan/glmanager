#pragma once
#ifndef MOBILE_SCENE_H
#define MOBILE_SCENE_H
#include <list>
#include "Object.h"

namespace mobile
{
 
class Scene : public virtual Object, public virtual GravityMotion
{
public:
  Scene()
  {
  }
  virtual ~Scene();

  virtual void initContext();
  virtual void preFrame();
  virtual void draw();
  void setObject(GravityMotion* object);
  void startMove();
  void stopMove();

private:
  std::list<GravityMotion*> objects_;
};
};

#endif

