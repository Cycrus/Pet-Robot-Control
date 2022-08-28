/**********************************************************************
 * analog_digital_converter_test.cpp
 * 
 * Tests for the ADS1115 Analog to Digital Converter via I2C.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/
 
 // http://www.netzmafia.de/skripten/hardware/RasPi/RasPi_I2C.html
 // http://www.netzmafia.de/skripten/hardware/RasPi/Projekt-ADS1115/index.html

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <chrono>

extern "C"
{
    #include <i2c/smbus.h>
    #include <linux/i2c-dev.h>
    #include <linux/i2c.h>
}

using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

#define ADS_ADDR 0x48
#define CONVERSION_FINISHED 0x80


//----------------------------------------------------------------------
int powerDownModeTest(int device)
{
    uint8_t buf[10];
    int16_t val;
    
    while(true)
    {
        // Configuration of chip
        buf[0] = 1;
        buf[1] = 0b11000011;
        buf[2] = 0b10000101;
        
        if(write(device, buf, 3) != 3)
        {
            std::cout << "[ERROR] Failed to write to register." << std::endl;
            return 1;
        }
        
        // Waiting for conversion
        do
        {
            if(read(device, buf, 2) != 2)
            {
                std::cout << "[ERROR] Read conversion error" << std::endl;
                return 1;
            }
        } while(!(buf[0] & CONVERSION_FINISHED));
        
        // Read from conversion register
        buf[0] = 0;
        if(write(device, buf, 1) != 1)
        {
            std::cout << "[ERROR] Failed to write to register." << std::endl;
            return 1;
        }
        
        if(read(device, buf, 2) != 2)
        {
            std::cout << "[ERROR] Failed to read conversion." << std::endl;
            return 1;
        }
        
        // Convert buffer to int value
        val = (int16_t)buf[0] * 256 + (uint16_t)buf[1];
        
        //Display results
        printf("Hex: 0x%02x%02x - Int: %d - Float, converted: %f V\n",
                buf[0], buf[1], val, (float)val*4.096/32768.0);
    }
    
    return 0;
}


//----------------------------------------------------------------------
int main()
{
    // Opening the I2C Bus with read and write access
    int fd = open("/dev/i2c-1", O_RDWR);
    
    if(fd < 0)
    {
        std::cout << "[ERROR] Failed to open the i2c bus." << std::endl;
        return 1;
    }
    
    // Setting the specific device address to be an I2C slave which can be communicated with
    if(ioctl(fd, I2C_SLAVE, ADS_ADDR) < 0)
    {
        std::cout << "[ERROR] Failed to acquire bus access and/or talk to slave." << std::endl;
        return 1;
    }
    
    int error_code = powerDownModeTest(fd);
    
    
    close(fd);
    return error_code;
}
