#include "Device.h"
#include "MobileDevice.h"

namespace mobile
{

using namespace device;
MobileDevice::~MobileDevice()
{
}

void MobileDevice::update()
{
  if(handler_)
    handler_->update();
}

}

