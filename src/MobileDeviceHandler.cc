#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <iterator>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Device.h"
#include "MobileDeviceHandler.h"

namespace mobile
{

MobileDeviceHandler::~MobileDeviceHandler()
{
  io_service_.run_one();
  delete server_;
}

void MobileDeviceHandler::update()
{
  io_service_.poll();
}

void MobileDeviceHandler::prim(std::istringstream& iss)
{
  using std::make_pair;
  using boost::bind;

  typedef std::map<std::string, boost::function<void (void)> > functype;
  functype funcs;
  std::string type;

  funcs.insert(make_pair("CUBE", bind(&DigitalInterface::setData, mDevice_->getCube(), true)));
  funcs.insert(make_pair("SPHERE", bind(&DigitalInterface::setData, mDevice_->getSphere(), true)));
  funcs.insert(make_pair("CONE", bind(&DigitalInterface::setData, mDevice_->getCone(), true)));

  mDevice_->getCube()->setData(false);
  mDevice_->getSphere()->setData(false);
  mDevice_->getCone()->setData(false);

  iss >> type;
  functype::iterator it = funcs.find(type);
  if(it != funcs.end())
    it->second();
  return;
}

void MobileDeviceHandler::move(std::istringstream& iss)
{
  int i;
  iss >> i;
  if(i == 0)
    mDevice_->isMove()->setData(false);
  else if(i == 1)
    mDevice_->isMove()->setData(true);
}

void MobileDeviceHandler::gravity(std::istringstream& iss)
{
  double x, y, z = 0.0;
  Position pos;
  pos.x = 0.0;
  pos.y = 0.0;
  pos.z = 0.0;
  iss >> pos.x >> pos.y;
  mDevice_->getGravityInterface()->setData(pos);
}


void MobileDeviceHandler::handle(char* receive_buffer_)
{
  using std::make_pair;
  using boost::bind;

  typedef std::map<std::string, boost::function<void (std::istringstream&)> > functype;

  std::istringstream s(receive_buffer_);
  std::string command;

  functype funcs;
  funcs.insert(make_pair("PRIM", bind(&MobileDeviceHandler::prim, this, _1)));
  funcs.insert(make_pair("MOVE", bind(&MobileDeviceHandler::move, this, _1)));
  funcs.insert(make_pair("GRAVITY", bind(&MobileDeviceHandler::gravity, this, _1)));

  while(s >> command)
  {
    functype::iterator it = funcs.find(command);
    if(it != funcs.end())
      it->second(s);
    else
      std::cerr << "Unknown Command: " << command << std::endl;
  }
}

}

