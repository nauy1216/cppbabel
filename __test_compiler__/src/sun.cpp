#include <iostream>
#include "sun.h"
#include "earth.h"


void sun_start()
{
    std::cout << "sun_start \r\n"<< std::endl;

    earth_start();
};