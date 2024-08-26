/**********************************************************************
 * face_test.cpp
 * 
 * Tests for the face functionality.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#include <bcm2835.h>
#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>

#include "ST7735_TFT.hpp"
#include "ST7735_Canvas.hpp"
#include "ST7735_Utils.hpp"
#include "ST7735_Face.hpp"
#include "KeyInput.hpp"

#define DELAY1 1000
#define DELAY2 5000
#define DELAY3 16

void startDisplay(ST7735_TFT *display)
{
    uint8_t OFFSET_COL = 0;
    uint8_t OFFSET_ROW = 0;
    uint16_t TFT_WIDTH = 128;
    uint16_t TFT_HEIGHT = 160;
    
    int8_t GPIO_RST_TFT = 25;
    int8_t GPIO_DC_TFT = 24;
    int8_t GPIO_SCLK_TFT = -1;
    int8_t GPIO_SDIN_TFT = -1;
    int8_t GPIO_CS_TFT = -1;

    std::cout << "TFT Start" << std::endl;
    display->TFTSetupGPIO(GPIO_RST_TFT, GPIO_DC_TFT, GPIO_CS_TFT,
                          GPIO_SCLK_TFT, GPIO_SDIN_TFT);
    display->TFTInitScreenSize(OFFSET_COL, OFFSET_ROW ,
                               TFT_WIDTH , TFT_HEIGHT);
    display->TFTInitPCBType(TFT_ST7735S_Black);
    display->TFTfillScreen(ST7735_BLACK);
}

//----------------------------------------------------------------------
void stopFace(ST7735_Face* face)
{
  face->stopFaceLoop();
  bcm2835_delay(DELAY2);
}

//----------------------------------------------------------------------
void stopDisplay(ST7735_TFT *display)
{
    char teststr1[] = "Test over";
    display->TFTfillScreen(ST7735_BLACK);
    display->TFTdrawText(5, 50, teststr1, ST7735_GREEN, ST7735_BLACK, 2);
    bcm2835_delay(DELAY1);
    display->TFTPowerDown();
    bcm2835_close();
    delete display;
    display = nullptr;
    printf("TFT End\r\n");
}

//----------------------------------------------------------------------
ST7735_Face* startFace(ST7735_TFT *display)
{
    std::cout << std::endl;
    std::cout << "Testing Facial Feature Module." << std::endl;
    std::cout << "******************************" << std::endl;
    
    ST7735_Face* face = new ST7735_Face(display->getWidth(), display->getHeight(),
                                        ST7735_Utils::rgb888To565(0x000000),
                                        ST7735_Utils::rgb888To565(0xFFFFFF),
                                        ST7735_Utils::rgb888To565(0xFFFFFF),
                                        ST7735_Utils::rgb888To565(0xFFFFFF));
                     
    face->startFaceLoop(display, 30);
    
    bcm2835_delay(DELAY1);

    return face;
}

//----------------------------------------------------------------------
int main(void) 
{
    ST7735_TFT *display = new ST7735_TFT();
    
    if(!bcm2835_init())
    {
        std::cout << "Error 1201 : Problem with init bcm2835 library\r" << std::endl;
        return -1;
    }
    
    //bcm2835_delay(DELAY1);
    startDisplay(display);
    ST7735_Face* face = startFace(display);

    bcm2835_delay(DELAY2);

    stopFace(face);
    stopDisplay(display);
    return 0;
}
