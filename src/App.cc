#ifdef __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif  __APPLE__
#include <GLUT/glut.h>
#endif
#include "App.h"

namespace
{
mobile::App* newApp;

void display()
{
  newApp->display();
}

void resize(int w, int h)
{
  newApp->resize(w, h);
}

void mouse(int button, int state, int x, int y)
{
  newApp->mouse(button, state, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
  newApp->keyboard(key, x, y);
}
} // end of namespace ::


namespace mobile
{

void App::initContext()
{
  ::newApp = this;
  glutInit(argc_, argv_);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv_[0]);
  glutDisplayFunc(::display);

  scene_.initContext();

  glutReshapeFunc(::resize);
  glutMouseFunc(::mouse);
  glutIdleFunc(glutPostRedisplay);
  glutKeyboardFunc(::keyboard);

  scene_.setObject(&cube_);
}

void App::run()
{
  glutMainLoop();
}

void App::display()
{
  preFrame();
  draw();
  intraFrame();
  postFrame();
}

void App::resize(int w, int h)
{
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  {
    glLoadIdentity();
    gluPerspective(30.0, (double)w/(double)h, 1.0, 100.0);
  }
  glMatrixMode(GL_MODELVIEW);
}

void App::mouse(int button, int state, int x, int y)
{
}

void App::keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
  case '\033':
    exit(0);

  default:
    break;
  }
}

void App::preFrame()
{
  mDevice_.update();
  bool prev = false;

  if(mDevice_.getCube()->data())
    scene_.setObject(&cube_);
  else if(mDevice_.getSphere()->data())
    scene_.setObject(&sphere_);
  else if(mDevice_.getCone()->data())
    scene_.setObject(&cone_);
  
  Position pos = mDevice_.getGravityInterface()->data();
  scene_.setGravityX(pos.x);
  scene_.setGravityY(pos.y);
  scene_.setGravityZ(pos.z);
  scene_.preFrame();
  if(mDevice_.isMove()->data() && prev == false)
  {
    scene_.startMove();
  }
  else if(mDevice_.isMove()->data() == false && prev == true)
  {
    scene_.stopMove();
  }
  prev = mDevice_.isMove()->data();

}

void App::draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  scene_.draw();

  glutSwapBuffers();
}

void App::intraFrame()
{
  scene_.intraFrame();
}

void App::postFrame()
{
  scene_.postFrame();
}

} // end of namespace mobile

