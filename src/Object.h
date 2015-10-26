#pragma once
#ifndef MOBILE_OBJECT_H
#define MOBILE_OBJECT_H
#include "trackball.h"

namespace mobile
{

class Object
{
public:
  virtual ~Object() = 0;

  virtual void initContext();
  virtual void preFrame();
  virtual void intraFrame();
  virtual void draw();
  virtual void postFrame();
};

// TODO:
//   remove public Object
class GravityMotion : public virtual Object
{
public:
  GravityMotion()
    : isMove_(false)
  {
    trackballRegion(200, 200);
    gravityX_ = 0.0;
    gravityY_ = 0.0;
    gravityZ_ = 0.0;
  }

  virtual ~GravityMotion() = 0;
  void setGravityX(double gravityX)
  {
    gravityX_ = gravityX;
  }
  void setGravityY(double gravityY)
  {
    gravityY_ = gravityY;
  }
  void setGravityZ(double gravityZ)
  {
    gravityZ_ = gravityZ;
  }

  void start();
  void stop();
  
  /**
   * @brief update rotationMatrix
   */
  virtual void preFrame();

  double* matrix();


protected:
  bool isMove_;
  double gravityX_, gravityY_, gravityZ_;
  double rotationMatrix;

private:

};

class Cube : public virtual Object, public virtual GravityMotion
{
public:
  Cube()
    : GravityMotion()
  {
  }

  virtual ~Cube();
  virtual void preFrame();
  virtual void draw();
};

class Sphere : public virtual Object, public virtual GravityMotion
{
public:
  Sphere()
    : GravityMotion()
  {
  }

  virtual ~Sphere();
  virtual void draw();
};

class Cone : public virtual Object, public virtual GravityMotion
{
public:
  Cone()
    : GravityMotion()
  {
  }

  virtual ~Cone();
  virtual void draw();
};


}  // end of namespace mobile
#endif
