/**********************************************************************
 * ST7735_Utils.hpp
 * 
 * A class containing static util functions for use with the
 * ST7735_TFT display library.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#ifndef ST7735_UTILS_HPP
#define ST7735_UTILS_HPP

#include <stdint.h>

class ST7735_Utils
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Deleted constructor. Should never be instantiated.
    //
    ST7735_Utils() = delete;
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Deleted copy constructor.
    //
    ST7735_Utils(const ST7735_Utils&) = delete;
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Deleted destructor
    //
    ~ST7735_Utils() = delete;
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Converts a 2d coordinate onto a 1d system. Used for more intuitive selection of 1d bitmaps.
    ///
    /// @param x      The x coordinate to convert.
    /// @param y      The y coordinate to convert.
    /// @param width  The width of the 2d system the 2d coordinate stems from.
    ///
    /// @return       The 1d coordinate representation of the 2d coordinate.
    /// 
    //
    static uint16_t coords2DTo1D(uint8_t x, uint8_t y, uint8_t width);
    static uint16_t coords2DTo1D(int16_t x, int16_t y, int16_t width);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Converts a 24 bit 888 color type to a 16 bit 565 color type. Used for more intuitive color selection.
    /// Should only be used when initializing a program and not in runtime due to some divisions.
    ///
    /// @param rgb888    The 888 rgb color value to convert.
    ///
    /// @return          The converted rgb 565 value.
    /// 
    //
    static uint16_t rgb888To565(uint32_t rgb888);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Swaps two 8bit numbers. Returns via by reference passed parameters.
    ///
    /// @param x0    The first number to swap.
    /// @param x1    The second number to swap.
    /// 
    //
    static void swap(uint8_t &x0, uint8_t &x1);
    static void swap(int16_t &x0, int16_t &x1);
};

#endif // ST7735_UTILS_HPP
