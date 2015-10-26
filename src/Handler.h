#pragma once
#ifndef MOBILE_HANDLER_H
#define MOBILE_HANDLER_H
namespace mobile
{
class Handler
{
public:
  virtual ~Handler();
  virtual void update() = 0;
};

}


#endif
