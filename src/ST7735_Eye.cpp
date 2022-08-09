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
#include "ST7735_Utils.hpp"

ST7735_Eye::ST7735_Eye(int16_t eye_side,
                       int16_t corner_radius,
                       int16_t canvas_width,
                       int16_t canvas_height,
                       uint16_t background_color,
                       uint16_t eye_color,
                       uint16_t glare_color) :
background_color_(background_color),
eye_color_(eye_color),
glare_color_(glare_color),
frame_(canvas_width, canvas_height, background_color),
eye_side_(eye_side),
corner_radius_(corner_radius),
MAX_UPPER_EYELID_(100),
MIN_UPPER_EYELID_(15),
MIN_X_(0),
MIN_Y_(0),
MAX_X_(100),
MAX_Y_(100),
norm_x_(45),
norm_y_(10),
norm_width_(60),
norm_height_(60),
MAX_LOWER_EYELID_(100),
MIN_LOWER_EYELID_(75),
MAX_EYEBROW_DEPTH_(15),
MIN_EYEBROW_DEPTH_(0),
MAX_EYEBROW_ANGLE_(50),
MIN_EYEBROW_ANGLE_(-50)
{
    x_ = norm_x_;
    y_ = norm_y_;
    
    width_ = norm_width_;
    height_ = norm_height_;
    
    upper_eyelid_ = MAX_UPPER_EYELID_;
    lower_eyelid_ = MAX_LOWER_EYELID_;
    
    eyebrow_depth_ = MIN_EYEBROW_DEPTH_;
    eyebrow_angle_ = 0;
    
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
void ST7735_Eye::setUpperEyelid(int16_t percentage)
{
    ST7735_Utils::checkLimits(percentage, MIN_UPPER_EYELID_, MAX_UPPER_EYELID_);
    
    int16_t new_height = (float)norm_height_ / 100.0 * (float)percentage;
    int16_t new_x = x_ - (new_height - height_) / 5;
    setEyePos(new_x, y_);
    height_ = new_height;
    upper_eyelid_ = percentage;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::moveUpperEyelid(int16_t value)
{
    setUpperEyelid(upper_eyelid_ + value);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::setLowerEyelid(int16_t percentage)
{
    ST7735_Utils::checkLimits(percentage, MIN_LOWER_EYELID_, MAX_LOWER_EYELID_);
    lower_eyelid_ = percentage;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::moveLowerEyelid(int16_t value)
{
    setLowerEyelid(lower_eyelid_ + value);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::setEyebrowDepth(int16_t depth)
{
    ST7735_Utils::checkLimits(depth, MIN_EYEBROW_DEPTH_, MAX_EYEBROW_DEPTH_);
    eyebrow_depth_ = depth;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::moveEyebrowDepth(int16_t depth)
{
    setEyebrowDepth(eyebrow_depth_ + depth);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::setEyebrowAngle(int16_t angle)
{
    ST7735_Utils::checkLimits(angle, MIN_EYEBROW_ANGLE_, MAX_EYEBROW_ANGLE_);
    eyebrow_angle_ = angle;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::moveEyebrowAngle(int16_t angle)
{
    setEyebrowAngle(eyebrow_angle_ + angle);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::setEyePos(int16_t x, int16_t y)
{
    ST7735_Utils::checkLimits(x, MIN_X_, MAX_X_);
    ST7735_Utils::checkLimits(y, MIN_Y_, MAX_Y_);
    
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
void ST7735_Eye::update()
{
    simulatePerspective();
    
    // Width and Height must be swapped to account for swapped x and y axis.
    MAX_X_ = frame_.getWidth() - height_;
    MAX_Y_ = frame_.getHeight() - width_;
    
    frame_.fill(background_color_);
    
    drawEye();
    drawLowerEyelid();
    drawEyebrow();
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::drawEye()
{
    frame_.drawRect(x_, y_, height_, width_, corner_radius_, eye_color_);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::drawLowerEyelid()
{
    float eyelid_height = (100.0 - lower_eyelid_) * (float)upper_eyelid_ * 0.01;
    
    frame_.drawEllipse(x_, y_ + (width_ / 2),
                       eyelid_height, width_ / 1.5,
                       background_color_, 1, true);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::drawEyebrow()
{
    int16_t left_vert_x = x_ + height_ + 25 - eyebrow_depth_;
    int16_t right_vert_x = x_ + height_ + 25 - eyebrow_depth_;
    int16_t left_vert_y = -norm_y_ + y_ - 20;
    int16_t right_vert_y = -norm_y_ + y_ + frame_.getHeight() + 20;

    left_vert_x += eyebrow_angle_ / 2 * eye_side_;
    right_vert_x -= eyebrow_angle_ / 2 * eye_side_;
    frame_.drawLine(left_vert_x, left_vert_y, right_vert_x, right_vert_y, background_color_, 20); 
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Eye::simulatePerspective()
{
    if(eye_side_ == LEFT_EYE)
    {
        uint16_t new_width = norm_width_ - (norm_y_ - y_);
        width_ = new_width;
    }
    else
    {
        uint16_t new_width = norm_width_ + (norm_y_ - y_) / 2;
        y_ += width_ - new_width;
        width_ = new_width;
    }
}
