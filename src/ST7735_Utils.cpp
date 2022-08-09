/**********************************************************************
 * ST7735_Utils.cpp
 * 
 * Implementation of the ST7735_Utils class.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#include "ST7735_Utils.hpp"

uint16_t ST7735_Utils::coords2DTo1D(uint8_t x, uint8_t y, uint8_t width)
{
    uint8_t converted_y;
    
    if(y > 0)
    {
        converted_y = y - 1;
    }
    else
    {
        converted_y = 0;
    }
    
    uint16_t id = x + converted_y * width;
    
    return id;
}

uint16_t ST7735_Utils::coords2DTo1D(int16_t x, int16_t y, int16_t width)
{
    uint8_t converted_y;
    
    if(y > 0)
    {
        converted_y = y - 1;
    }
    else
    {
        converted_y = 0;
    }
    
    uint16_t id = x + converted_y * width;
    
    return id;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t ST7735_Utils::rgb888To565(uint32_t rgb888)
{
    uint8_t r_mask = 0b00011111;
    uint8_t g_mask = 0b00111111;
    uint8_t b_mask = 0b00011111;
    
    uint8_t r = rgb888 >> 16;
    uint8_t g = rgb888 >> 8;
    uint8_t b = rgb888;
    
    float r_fraction = static_cast<float>(r) / 255.0 * 31.0;
    float g_fraction = static_cast<float>(g) / 255.0 * 63.0;
    float b_fraction = static_cast<float>(b) / 255.0 * 31.0;
    
    uint8_t r565 = static_cast<uint8_t>(r_fraction) & r_mask;
    uint8_t g565 = static_cast<uint8_t>(g_fraction) & g_mask;
    uint8_t b565 = static_cast<uint8_t>(b_fraction) & b_mask;
    
    uint16_t rgb565 = (r565 << 11) + (g565 << 5) + (b565 << 0);
    
    return rgb565;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Utils::swap(uint8_t &x0, uint8_t &x1)
{
    uint8_t x_temp = x0;
    x0 = x1;
    x1 = x_temp;
}

void ST7735_Utils::swap(int16_t &x0, int16_t &x1)
{
    int16_t x_temp = x0;
    x0 = x1;
    x1 = x_temp;
}
