
#include <iostream>
#include <unistd.h>

int main(void) 
{
    while(true)
    {
      std::cout << "Hello from the C++ Interface." << std::endl;
      sleep(1);
    }
    return 0;
}
