#pragma once
#ifndef MOBILE_DEVICE_H
#define MOBILE_DEVICE_H
#include <boost/function.hpp>

namespace mobile
{
struct Position
{
  Position()
    : x(0.0),
      y(0.0),
      z(0.0)
  {
  }

  double x, y, z;
};

}


namespace mobile
{
namespace device
{

template <typename D>
class DeviceInterface
{
public:
  DeviceInterface()
    : data_()
  {
  }

  DeviceInterface(D d)
    : data_(d)
  {
  }

  virtual ~DeviceInterface()
  {
  }

  virtual D data()
  {
    return data_;
  }

  virtual void setData(D d)
  {
    data_ = d;
  }

protected:
  D data_;
};

typedef DeviceInterface<Position> PositionInterface;
typedef DeviceInterface<bool>     DigitalInterface;
/*
class PositionInterface : public DeviceInterface<Position>
{
public:

  ~PositionInterface();
};

class DigitalInterface : public DeviceInterface<bool>
{
public:
  DigitalInterface()
    : data_(false)
  {
  }

  explicit DigitalInterface(bool value)
    : data_(value)
  {
  }

  ~DigitalInterface();
};
*/


} // end of namespace device
} // end of namespace mobile


#endif
