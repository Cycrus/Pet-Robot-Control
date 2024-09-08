
#include <iostream>
#include <unistd.h>
#include "MQTTClient.h"

int main(void) 
{
    while(true)
    {
      std::cout << "Hello from the C++ Interface." << std::endl;
      std::cout << "Paho is included." << std::endl;
      sleep(1);
    }
    return 0;
}
