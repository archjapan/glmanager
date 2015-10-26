#pragma once
#ifndef MOBILE_MOBILE_DEVICE_H
#define MOBILE_MOBILE_DEVICE_H
#include "Device.h"
#include "Handler.h"

namespace mobile
{
using namespace device;

class MobileDevice
{
public:
  MobileDevice()
    : gravity_(),
      cube_(true),
      sphere_(false),
      cone_(false),
      move_(false)
  {
  }
  ~MobileDevice();
  void update();

  void setHandler(Handler* handler)
  {
    handler_ = handler;
  }

  PositionInterface* getGravityInterface()
  {
    return &gravity_;
  }

  DigitalInterface*  getCube()
  {
    return &cube_;
  }

  DigitalInterface* getSphere()
  {
    return &sphere_;
  }

  DigitalInterface* getCone()
  {
    return &cone_;
  }

  DigitalInterface* isMove()
  {
    return &move_;
  }


private:
  PositionInterface gravity_;
  DigitalInterface  cube_;
  DigitalInterface  sphere_;
  DigitalInterface  cone_;
  DigitalInterface  move_;

  Handler* handler_;
};

} // end of namespace mobile

#endif

