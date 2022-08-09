/**********************************************************************
 * ST7735_Eye.cpp
 * 
 * Implementation of the ST7735_Eye class.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#include "ST7735_Eye.hpp"

#include <iostream>

ST7735_Eye::ST7735_Eye(int16_t canvas_width,
                       int16_t canvas_height,
                       uint16_t background_color,
                       uint16_t eye_color,
                       uint16_t glare_color) :
frame_(canvas_width, canvas_height, background_color),
background_color_(background_color),
eye_color_(eye_color),
glare_color_(glare_color),
norm_x_(45),
norm_y_(10),
norm_width_(60),
norm_height_(60),
upper_eyelid_(100),
lower_eyelid_(100)
{
    x_ = norm_x_;
    y_ = norm_y_;
    
    width_ = norm_width_;
    height_ = norm_height_;
    
    MIN_X_ = 0;
    MIN_Y_ = 0;
    
    MAX_UPPER_EYELID_ = 100;
    MIN_UPPER_EYELID_ = 15;
    
    MAX_LOWER_EYELID_ = 100;
    MIN_LOWER_EYELID_ = 75;
    
    update();
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::blit(ST7735_Canvas &canvas, int16_t x, int16_t y)
{
    update();
    
    canvas.blitCanvas(frame_, 0, 0, frame_.getWidth(), frame_.getHeight(),
                      x, y, background_color_);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::update()
{
    // Width and Height must be swapped to account for swapped x and y axis.
    MAX_X_ = frame_.getWidth() - height_;
    MAX_Y_ = frame_.getHeight() - width_;
    
    frame_.fill(background_color_);
    
    drawEye();
    drawLowerEyelid();
    drawEyebrow();
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::setUpperEyelid(int16_t percentage)
{
    if(percentage > MAX_UPPER_EYELID_)
    {
        percentage = MAX_UPPER_EYELID_;
    }
    else if(percentage < MIN_UPPER_EYELID_)
    {
        percentage = MIN_UPPER_EYELID_;
    }
    
    int16_t new_height = (float)norm_height_ / 100.0 * (float)percentage;
    int16_t new_x = x_ - (new_height - height_) / 5;
    setEyePos(new_x, y_);
    height_ = new_height;
    upper_eyelid_ = percentage;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::setLowerEyelid(int16_t percentage)
{
    if(percentage > MAX_LOWER_EYELID_)
    {
        percentage = MAX_LOWER_EYELID_;
    }
    else if(percentage < MIN_LOWER_EYELID_)
    {
        percentage = MIN_LOWER_EYELID_;
    }
    
    lower_eyelid_ = percentage;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::setEyePos(int16_t x, int16_t y)
{
    if(x < MIN_X_)
    {
        x = MIN_X_;
    }
    else if(x > MAX_X_)
    {
        x = MAX_X_;
    }
    if(y < MIN_Y_)
    {
        y = MIN_Y_;
    }
    else if(y > MAX_Y_)
    {
        y = MAX_Y_;
    }
    
    x_ = x;
    y_ = y;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::moveEye(int16_t x, int16_t y)
{
    setEyePos(x_ + x, y_ + y);
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getX()
{
    return x_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getY()
{
    return y_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getNormX()
{
    return norm_x_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getNormY()
{
    return norm_y_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getMinX()
{
    return MIN_X_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getMaxX()
{
    return MAX_X_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getMinY()
{
    return MIN_Y_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Eye::getMaxY()
{
    return MAX_Y_;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::drawEye()
{
    frame_.drawRect(x_, y_, height_, width_, 10, eye_color_);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::drawLowerEyelid()
{
    if(lower_eyelid_ < 100)
    {
        float eyelid_height = (100.0 - lower_eyelid_) * (float)upper_eyelid_ * 0.01;
        
        frame_.drawEllipse(x_, y_ + (width_ / 2),
                           eyelid_height, width_ / 1.5,
                           background_color_, 1, true);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::drawEyebrow()
{
    
}
