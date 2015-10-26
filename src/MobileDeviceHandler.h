#pragma once
#ifndef MOBILE_MOBILE_DEVICE_HANDLER_H
#define MOBILE_MOBILE_DEVICE_HANDLER_H
#include "Handler.h"
#include "main.h"
#include "Server.h"
#include "MobileDevice.h"

namespace mobile
{

class MobileDeviceHandler : public Handler
{
public:
  MobileDeviceHandler(MobileDevice* mDevice)
    : io_service_(),
      mDevice_(mDevice)
  {
    server_ = new Server(
        io_service_,
        ::PORT,
        boost::bind(&MobileDeviceHandler::handle, this, _1));
    mDevice_->setHandler(this);
  }

  ~MobileDeviceHandler();
  virtual void update();

private:
  void prim(std::istringstream& iss);
  void move(std::istringstream& iss);
  void gravity(std::istringstream& iss);
  void handle(char* receive_buffer_);

  boost::asio::io_service io_service_;
  MobileDevice* mDevice_;
  Server* server_;
};
}

#endif
