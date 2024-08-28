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
#include <chrono>
#include <thread>


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
left_eye_(LEFT_EYE, 20, 128, 80, face_color, left_eye_color, accent_color),
right_eye_(RIGHT_EYE, 20, 128, 80, face_color, right_eye_color, accent_color),
running_(false)
{
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Face::setEmotion(Emotion emotion, float strength)
{

}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Face::lookAt(float x, float y)
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
void ST7735_Face::stopFaceLoop()
{
    running_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Face::startFaceLoop(ST7735_TFT *display, int frequency)
{
  std::thread face_thread(&ST7735_Face::faceLoop, this, display, frequency);
  face_thread.detach();
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Face::faceLoop(ST7735_TFT *display, int frequency)
{
  running_ = true;
  int sleep_time = 1000 / frequency;

  display->TFTfillScreen(0x0000);

  while(running_)
  {
      render(display);
      bcm2835_delay(sleep_time);
  }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Face::faceDemoLoop(ST7735_TFT *display)
{
    const int16_t EVENT_WAKEUP = 0;
    const int16_t EVENT_MOVEEYES = 1;
    const int16_t EVENT_HAPPY = 2;
    const int16_t EVENT_EMOTIONS = 3;
    const int16_t EVENT_GOSLEEP = 4;
    
    bool running = true;
    int16_t event = 0;
    int16_t frame = 0;
    
    display->TFTfillScreen(0x0000);
    
    while(running)
    {
        switch(event)
        {
            case EVENT_WAKEUP:
                if(frame == 0)
                {
                    right_eye_.setUpperEyelid(0);
                    left_eye_.setUpperEyelid(0);
                }
                else if(frame > 50 && frame < 80)
                {
                    right_eye_.moveUpperEyelid(5);
                    left_eye_.moveUpperEyelid(5);
                }
                else if(frame > 80)
                {
                    event++;
                    frame = 0;
                }
                break;
                
            case EVENT_MOVEEYES:
                if(frame > 0 && frame < 10)
                {
                    right_eye_.moveUpperEyelid(-2);
                    left_eye_.moveUpperEyelid(-2);
                }
                else if(frame > 10 && frame < 20)
                {
                    right_eye_.moveEye(0, 3);
                    left_eye_.moveEye(0, 3);
                }
                else if(frame > 30 && frame < 35)
                {
                    right_eye_.moveEye(0, -5);
                    left_eye_.moveEye(0, -5);
                }
                else if(frame > 40 && frame < 50)
                {
                    right_eye_.moveEye(0, 5);
                    left_eye_.moveEye(0, 5);
                }
                else if(frame > 60)
                {
                    event++;
                    frame = 0;
                }
                
                break;
                
            case EVENT_HAPPY:
                if(frame > 0 && frame < 5)
                {
                    right_eye_.moveLowerEyelid(-5);
                    left_eye_.moveLowerEyelid(-5);
                }
                else if(frame == 10)
                {
                    right_eye_.moveEye(0, -5);
                    left_eye_.moveEye(0, -5);
                }
                else if(frame == 20)
                {
                    right_eye_.moveEye(2, 0);
                    left_eye_.moveEye(2, 0);
                }
                else if(frame == 22)
                {
                    right_eye_.moveEye(-4, 0);
                    left_eye_.moveEye(-4, 0);
                }
                else if(frame == 24)
                {
                    right_eye_.moveEye(4, 0);
                    left_eye_.moveEye(4, 0);
                }
                else if(frame == 26)
                {
                    right_eye_.moveEye(-4, 0);
                    left_eye_.moveEye(-4, 0);
                }
                else if(frame == 28)
                {
                    right_eye_.moveEye(4, 0);
                    left_eye_.moveEye(4, 0);
                }
                else if(frame == 30)
                {
                    right_eye_.moveEye(-4, 0);
                    left_eye_.moveEye(-4, 0);
                }
                else if(frame > 40)
                {
                    event++;
                    frame = 0;
                }
                break;
                
            case EVENT_EMOTIONS:
                if(frame < 5)
                {
                    right_eye_.moveLowerEyelid(4);
                    left_eye_.moveLowerEyelid(4);
                    left_eye_.moveEyebrowDepth(4);
                }
                else if(frame > 40 && frame < 60)
                {
                    right_eye_.moveEyebrowDepth(1);
                }
                else if(frame > 80 && frame < 100)
                {
                    right_eye_.moveEyebrowAngle(-1);
                    left_eye_.moveEyebrowAngle(-1);
                }
                else if(frame > 120 && frame < 130)
                {
                    right_eye_.moveLowerEyelid(-2);
                }
                else if(frame > 130 && frame < 140)
                {
                    left_eye_.moveLowerEyelid(-2);
                }
                else if(frame > 160 && frame < 200)
                {
                    right_eye_.moveEyebrowAngle(1);
                    left_eye_.moveEyebrowAngle(1);
                }
                else if(frame > 220)
                {
                    event++;
                    frame = 0;
                }
                break;
            
            case EVENT_GOSLEEP:
                if(frame < 20)
                {
                    right_eye_.moveEyebrowAngle(-1);
                    left_eye_.moveEyebrowAngle(-1);
                    right_eye_.moveLowerEyelid(2);
                    left_eye_.moveLowerEyelid(2);
                    right_eye_.moveEyebrowDepth(-1);
                    left_eye_.moveEyebrowDepth(-1);
                }
                else if(frame > 30 && frame < 50)
                {
                    right_eye_.moveUpperEyelid(-5);
                    left_eye_.moveUpperEyelid(-5);
                }
                else if(frame > 50)
                {
                    event++;
                    frame = 0;
                }
                break;
                
            default:
                running = false;
                break;
        }
        
        /*
        right_eye_.moveEye(speed_x, speed_y);
        left_eye_.moveEye(speed_x, speed_y);
        right_eye_.moveEyebrowAngle(general_direction);
        left_eye_.moveEyebrowAngle(general_direction);
        right_eye_.moveEyebrowDepth(general_direction);
        left_eye_.moveEyebrowDepth(general_direction);
        right_eye_.moveLowerEyelid(general_direction);
        left_eye_.moveLowerEyelid(general_direction);
        right_eye_.moveUpperEyelid(general_direction);
        left_eye_.moveUpperEyelid(general_direction);
        */
        
        render(display);
        bcm2835_delay(FRAME_DELAY_);
        frame++;
    }
}
