
#include <iostream>
#include <unistd.h>
#include "MQTTClient.h"

int main(void) 
{
  int i = 0;
  while(true)
  {
    std::cout << "Hello from the C++ Interface: " << i << std::endl;
    std::cout << "Paho is included." << std::endl;
    sleep(1);
    i++;
  }
  return 0;
}
