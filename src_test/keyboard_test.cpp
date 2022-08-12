/**********************************************************************
 * keyboard_test.cpp
 * 
 * Tests for the keyboard input functionality.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#include <iostream>

#include "KeyInput.hpp"


//----------------------------------------------------------------------
void testKeyboard()
{
    std::cout << std::endl;
    std::cout << "Testing Nonblocking Direct Keyboard Input Module." << std::endl;
    std::cout << "******************************" << std::endl;
    
    KeyInput keyboard("/dev/input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.1:1.0-event-kbd", false);
    bool do_loop = true;
    while(do_loop)
    {
        keyboard.getKey();
        if(keyboard.getCode() != 0)
        {
            std::cout << "Code = " << keyboard.getCode() << " ... State = " << keyboard.getState() << std::endl;
        }
        if(keyboard.getCode() == 1)
        {
            do_loop = false;
        }
    }
}

//----------------------------------------------------------------------
int main(void) 
{
    testKeyboard();
    
    return 0;
}
