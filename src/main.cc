#include <iostream>
#include <boost/asio.hpp>
#include "App.h"
#include "MobileDeviceHandler.h"



int main(int argc, char* argv[])
{
  mobile::App app(&argc, argv);

  try
  {
    app.initContext();

    mobile::MobileDeviceHandler handler(app.mobileDevice());

    app.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}


