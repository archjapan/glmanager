#include <boost/foreach.hpp>
#ifdef __linux__
#include <GL/gl.h>
#elif  __APPLE__
#include <GL/glut.h>
#endif
#include "Scene.h"

namespace mobile
{

Scene::~Scene()
{
  objects_.clear();
}

void Scene::initContext()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void Scene::preFrame()
{
  BOOST_FOREACH(GravityMotion* o, objects_)
  {
    o->setGravityX(gravityX_);
    o->setGravityY(gravityY_);
    o->setGravityZ(gravityZ_);
    o->preFrame();
  }
}

void Scene::startMove()
{
  BOOST_FOREACH(GravityMotion* o, objects_)
  {
    o->start();
  }
}

void Scene::stopMove()
{
  BOOST_FOREACH(GravityMotion* o, objects_)
  {
    o->stop();
  }
}

void Scene::draw()
{
  static double color = -1.0;
  color += 0.001;
  if(color > 1.0) color = -1.0;

  if(color < 0.0)
    glColor3d(1.0 + color, 0.0, 0.0);
  else
    glColor3d(color, 0.0, 0.0);
  glTranslated(0.0, 0.0, -10.0);
  BOOST_FOREACH(Object* o, objects_)
  {
    o->draw();
  }
}

void Scene::setObject(GravityMotion* object)
{
  objects_.clear();
  objects_.push_back(object);
}

}


