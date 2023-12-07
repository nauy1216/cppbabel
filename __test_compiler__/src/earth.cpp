#include <iostream>
#include "earth.h"
#include "moon.h"

void earth_start()
{
    std::cout << "earth_start \r\n"<< std::endl;

    moon_start();
}