#ifdef __linux__
#include <GL/gl.h>
#include <GL/glut.h>
#elif  __APPLE__
#include <GLUT/glut.h>
#endif
#include <iostream>
#include "Object.h"

namespace
{
const double PADDING = 100.0;
const double SCALE   = 1.0;
}

namespace mobile
{

Object::~Object()
{
}

void Object::initContext() 
{
}

void Object::preFrame()
{
}

void Object::intraFrame()
{
}

void Object::draw()
{
}

void Object::postFrame()
{
}

GravityMotion::~GravityMotion()
{
}

void GravityMotion::start()
{
  isMove_ = true;
  std::cout << "isMove_=" << isMove_ << std::endl;
  std::cout << "GRAVITY=" << gravityX_ << std::endl;
  trackballStart(SCALE*gravityX_+PADDING, SCALE*gravityY_+PADDING);
}

void GravityMotion::stop()
{
  isMove_ = false;
  trackballStop(SCALE*gravityX_+PADDING, SCALE*gravityY_+PADDING);
}

void GravityMotion::preFrame()
{
  if(isMove_);
    trackballMotion(SCALE*gravityX_+PADDING, SCALE*gravityY_+PADDING);
}

double* GravityMotion::matrix()
{
  return trackballRotation();
}

Cube::~Cube()
{
}

void Cube::preFrame()
{
  GravityMotion::preFrame();
}

void Cube::draw()
{
  glMultMatrixd(matrix());
  glutWireCube(1.0);
}

Sphere::~Sphere()
{
}

void Sphere::draw()
{
  glMultMatrixd(matrix());
  glutWireSphere(1.0, 20, 20);
}

Cone::~Cone()
{
}

void Cone::draw()
{
  glMultMatrixd(matrix());
  glutWireCone(1.0, 1.0, 20, 20);
}

} // end of namespace mobile

