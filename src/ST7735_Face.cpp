/**********************************************************************
 * ST7735_Face.cpp
 * 
 * Implementation of the ST7735_Face class.
 * Important note: display is rotated 90° counter clockwise to achieve
 * larger facial expressions.
 * With this configuration is origin at bottom left.
 * x increases upwards.
 * y inreases to the right.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#include "ST7735_Face.hpp"

#include <bcm2835.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

#include "KeyInput.hpp"

ST7735_Face::ST7735_Face(int16_t screen_width,
                         int16_t screen_height,
                         uint16_t face_color,
                         uint16_t left_eye_color,
                         uint16_t right_eye_color,
                         uint16_t accent_color) :
face_color_(face_color),
left_eye_color_(left_eye_color),
right_eye_color_(right_eye_color),
accent_color_(accent_color),
frame_(screen_width, screen_height, face_color),
left_eye_(128, 80, face_color, left_eye_color, accent_color),
right_eye_(128, 80, face_color, right_eye_color, accent_color),
running_(false)
{
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Face::render(ST7735_TFT *display)
{
    frame_.fill(face_color_);
    left_eye_.blit(frame_, 0, 0);
    right_eye_.blit(frame_, 0, 80);
    frame_.render(display, 0, 0);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Face::faceLoop(ST7735_TFT *display)
{
    KeyInput keyboard("/dev/input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.1:1.0-event-kbd", false);
    
    running_ = true;
    
    int16_t upper_eyelid_left = 100;
    int16_t upper_eyelid_right = 100;
    int16_t lower_eyelid_left = 100;
    int16_t lower_eyelid_right = 100;
    int8_t speed_x = 0;
    int8_t speed_y = 0;
    int16_t step_size = 5;
    bool uper_eyelids_open = true;
    bool lower_eyelids_open = true;
    bool wink = false;
    
    srand(time(NULL));
    display->TFTfillScreen(0x0000);
    
    while(running_)
    {
        keyboard.getKey();

        switch(keyboard.getCode())
        {
            case K_8:
                speed_x = step_size;
                break;
                
            case K_6:
                speed_y = step_size;
                break;
            
            case K_2:
                speed_x = -step_size;
                break;
                
            case K_4:
                speed_y = -step_size;
                break;
                
            case K_7:
                if(keyboard.getState() == ButtonState::PRESS)
                {
                    upper_eyelid_left -= 5;
                    upper_eyelid_right -= 5;
                    /*if(upper_eyelid_left == 70 || upper_eyelid_right == 70)
                    {
                        upper_eyelid_left = 20;
                        upper_eyelid_right = 20;
                    }
                    else
                    {
                        upper_eyelid_left = 70;
                        upper_eyelid_right = 70;
                    }*/
                }
                break;
                
            case K_9:
                if(keyboard.getState() == ButtonState::PRESS)
                {
                    lower_eyelid_left -= 5;
                    lower_eyelid_right -= 5;
                    /*if(lower_eyelid_left == 70 || lower_eyelid_right == 100)
                    {
                        lower_eyelid_left = 20;
                        lower_eyelid_right = 20;
                    }
                    else
                    {
                        lower_eyelid_left = 70;
                        lower_eyelid_right = 70;
                    }*/
                    std::cout << lower_eyelid_left << std::endl;
                }
                break;
        }
        
        if(keyboard.getState() == ButtonState::ERROR)
        {
            speed_x = 0;
            speed_y = 0;
        }
        
        right_eye_.moveEye(speed_x, speed_y);
        left_eye_.moveEye(speed_x, speed_y);
        right_eye_.setUpperEyelid(upper_eyelid_right);
        left_eye_.setUpperEyelid(upper_eyelid_left);
        right_eye_.setLowerEyelid(lower_eyelid_right);
        left_eye_.setLowerEyelid(lower_eyelid_left);
        
        render(display);
        
        bcm2835_delay(FRAME_DELAY_);
    }
}
