/*
 * Project Name: development_sandbox
 * Author: Cyril Marx
 * Date: August 2022
 * Library: https://github.com/gavinlyonsrepo/ST7735_TFT_RPI
 */

#include <bcm2835.h>
#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>

#include "ST7735_TFT.h"
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

    std::cout << "TFT Start\r" << std::endl;
    display->TFTSetupGPIO(GPIO_RST_TFT, GPIO_DC_TFT, GPIO_CS_TFT,
                          GPIO_SCLK_TFT, GPIO_SDIN_TFT);
    display->TFTInitScreenSize(OFFSET_COL, OFFSET_ROW ,
                               TFT_WIDTH , TFT_HEIGHT);
    display->TFTInitPCBType(TFT_ST7735S_Black);
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
void testCoordConvert();
void testKeyboard();
void testFace(ST7735_TFT *display);
void testBorders(ST7735_TFT *display, ST7735_Canvas &canvas);
void testTriangles(ST7735_TFT *display, ST7735_Canvas &canvas);
void testCanvasBlit(ST7735_TFT *display, ST7735_Canvas &canvas);
void testShapes(ST7735_TFT *display, ST7735_Canvas &canvas);
void testColorConversion(ST7735_TFT *display, ST7735_Canvas &canvas);
void testLines(ST7735_TFT *display, ST7735_Canvas &canvas);
void testRect(ST7735_TFT *display, ST7735_Canvas &canvas);

//----------------------------------------------------------------------
int main(void) 
{
    ST7735_TFT *display = new ST7735_TFT();
    
    if(!bcm2835_init())
    {
        std::cout << "Error 1201 : Problem with init bcm2835 library\r" << std::endl;
        return -1;
    }
    
    bcm2835_delay(DELAY1);
    display->TFTfillScreen(0x0000);
    
    ST7735_Canvas canvas(100, 100, 0x0000);
    
    startDisplay(display);
    
    testFace(display);
    bcm2835_delay(DELAY1);
    
    testCoordConvert();
    
    testKeyboard();
    
    testBorders(display, canvas);
    bcm2835_delay(DELAY1);
    
    testShapes(display, canvas);
    bcm2835_delay(DELAY1);
    
    testTriangles(display, canvas);
    bcm2835_delay(DELAY1);
    
    testCanvasBlit(display, canvas);
    bcm2835_delay(DELAY1);
    
    testColorConversion(display, canvas);
    bcm2835_delay(DELAY1);
    
    testLines(display, canvas);
    bcm2835_delay(DELAY1);
    
    testRect(display, canvas),
    bcm2835_delay(DELAY1);

    stopDisplay(display);
    return 0;
}

//----------------------------------------------------------------------
void testKeyboard()
{
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
void testFace(ST7735_TFT *display)
{
    ST7735_Face face(display->getWidth(), display->getHeight(),
                     ST7735_Utils::rgb888To565(0x000000),
                     ST7735_Utils::rgb888To565(0xFFFFFF),
                     ST7735_Utils::rgb888To565(0xFFFFFF),
                     ST7735_Utils::rgb888To565(0xFFFFFF));
                     
    face.faceLoop(display);
    
    bcm2835_delay(DELAY2);
}

//----------------------------------------------------------------------
void testCoordConvert()
{
    int16_t x0 = 100;
    int16_t y0 = 10;
    int16_t x1 = 99;
    int16_t y1 = 10;
    int16_t x2 = 98;
    int16_t y2 = 10;
    
    std::cout << ST7735_Utils::coords2DTo1D(x0, y0, 100) << std::endl;
    std::cout << ST7735_Utils::coords2DTo1D(x1, y1, 100) << std::endl;
    std::cout << ST7735_Utils::coords2DTo1D(x2, y2, 100) << std::endl;
}

//----------------------------------------------------------------------
void testBorders(ST7735_TFT *display, ST7735_Canvas &canvas)
{
    uint16_t color_1 = ST7735_Utils::rgb888To565(0x000000);
    uint16_t color_2 = ST7735_Utils::rgb888To565(0xFFFFFF);
    
    int16_t y_pos = 0;
    
    canvas.fill(color_1);
    
    for(int i = 0; i < 100; i++)
    {
        canvas.fill(color_1);
        canvas.drawRect(20, y_pos, 30, 30, 0, color_2);
        canvas.drawRect(80, 70, 30, 30, 0, color_2);
        y_pos++;
        
        canvas.render(display, 10, 0);
        bcm2835_delay(DELAY3);
    }
    
    bcm2835_delay(DELAY2);
}

//----------------------------------------------------------------------
void testTriangles(ST7735_TFT *display, ST7735_Canvas &canvas)
{
    std::cout << "Test Triangles" << std::endl;
    
    uint16_t c_black = ST7735_Utils::rgb888To565(0x000000);
    uint16_t c_red = ST7735_Utils::rgb888To565(0xFF0000);
    
    canvas.fill(c_black);
    canvas.drawTriangle(5, 55, 40, 5, 30, 5, c_red);
    canvas.render(display, 0, 0);
    
    bcm2835_delay(DELAY2);
}

//----------------------------------------------------------------------
void testCanvasBlit(ST7735_TFT *display, ST7735_Canvas &canvas)
{
    std::cout << "Test Canvas Blit" << std::endl;
    
    uint16_t c_white = ST7735_Utils::rgb888To565(0xFFFFFF);
    uint16_t c_black = ST7735_Utils::rgb888To565(0x000000);
    uint16_t c_red = ST7735_Utils::rgb888To565(0xFF0000);
    uint16_t c_green = ST7735_Utils::rgb888To565(0x0000FF);
    
    canvas.fill(c_white);
    canvas.drawEllipse(30, 40, 20, 20, c_red, 1, true);
    canvas.render(display);
    
    bcm2835_delay(DELAY1);
    ST7735_Canvas source_canvas(60, 60, c_black);
    source_canvas.drawRect(10, 10, 30, 35, 7, c_green);
    
    canvas.blitCanvas(source_canvas, 0, 0, 60, 60, 0, 0, c_green);
    canvas.render(display);
}

//----------------------------------------------------------------------
void testShapes(ST7735_TFT *display, ST7735_Canvas &canvas)
{
    std::cout << "Test Shapes" << std::endl;
    
    uint16_t color_1 = ST7735_Utils::rgb888To565(0xFF0000);
    uint16_t color_2 = ST7735_Utils::rgb888To565(0xFFFFFF);
    uint16_t color_3 = ST7735_Utils::rgb888To565(0x00FF00);
    uint16_t color_4 = ST7735_Utils::rgb888To565(0x0000FF);
    
    float step_size = 2 * M_PI / 8;
    int radius = 30;
    float theta = 0;
    
    canvas.fill(0x0000);
    canvas.drawEllipse(70, 50, 20, 11, color_1, 3, false);
    canvas.drawRect(20, 20, 30, 50, 0, color_2);
    canvas.render(display);
    
    bcm2835_delay(DELAY2);
    
    while(theta < 2 * M_PI)
    {
        canvas.fill(0x0000);
        
        int x = 50 + radius * cos(theta);
        int y = 50 + radius * sin(theta);
        
        canvas.drawLine(50, 50, x, y, color_3, 4);
        
        canvas.render(display);
        bcm2835_delay(DELAY1);
        
        theta += step_size;
    }
    
    canvas.fill(0x0000);
    canvas.drawEllipse(20, 50, 20, 11, color_1, 1, false);
    canvas.drawRect(20, 20, 70, 50, 20, color_4);
    canvas.render(display);
    
    bcm2835_delay(DELAY2);
}

//----------------------------------------------------------------------
void testColorConversion(ST7735_TFT *display, ST7735_Canvas &canvas)
{
    std::cout << "Test Color Conversion" << std::endl;
    
    uint32_t color888_1 = 0xFF0000;
    uint32_t color888_2 = 0x00FF00;
    uint32_t color888_3 = 0x0000FF;
    uint32_t color888_4 = 0x253e4f;
    uint32_t color888_5 = 0xd76de3;
    
    uint32_t color565_1 = ST7735_Utils::rgb888To565(color888_1);
    uint32_t color565_2 = ST7735_Utils::rgb888To565(color888_2);
    uint32_t color565_3 = ST7735_Utils::rgb888To565(color888_3);
    uint32_t color565_4 = ST7735_Utils::rgb888To565(color888_4);
    uint32_t color565_5 = ST7735_Utils::rgb888To565(color888_5);
    
    std::cout << std::hex << color565_1 << std::endl;
    canvas.fill(color565_1);
    canvas.render(display);
    bcm2835_delay(DELAY1);
    
    std::cout << std::hex << color565_2 << std::endl;
    canvas.fill(color565_2);
    canvas.render(display);
    bcm2835_delay(DELAY1);
    
    std::cout << std::hex << color565_3 << std::endl;
    canvas.fill(color565_3);
    canvas.render(display);
    bcm2835_delay(DELAY1);
    
    std::cout << std::hex << color565_4 << std::endl;
    canvas.fill(color565_4);
    canvas.render(display);
    bcm2835_delay(DELAY1);
    
    std::cout << std::hex << color565_5 << std::endl;
    canvas.fill(color565_5);
    canvas.render(display);
    bcm2835_delay(DELAY1);
}

//----------------------------------------------------------------------
void testLines(ST7735_TFT *display, ST7735_Canvas &canvas)
{
    std::cout << "Test Lines" << std::endl;
    
    uint16_t base_color = 0x8666;
    uint16_t front_color = 0x0000;
    uint8_t x1 = 0;
    uint8_t y1 = 0;
    uint8_t x2 = 0;
    uint8_t y2 = 0;
    uint8_t walk_factor1 = 2;
    uint8_t walk_factor2 = 2;
    int steps = 20;
    
    display->TFTfillScreen(ST7735_BLACK);
    for(int i = 0; i < steps; i++)
    {
        canvas.fill(base_color);
        canvas.drawHLine(x1, y1, 255, front_color);
        canvas.drawVLine(x2, y2, 255, front_color);
        canvas.render(display);
        
        y1 += walk_factor1;
        if(y1 >= canvas.getHeight())
        {
            walk_factor1 = -2;
        }
        else if(y1 <= 0)
        {
            walk_factor1 = 2;
        }
        
        x2 += walk_factor2;
        if(x2 >= canvas.getWidth())
        {
            walk_factor2 = -2;
        }
        else if(x2 <= 0)
        {
            walk_factor2 = 2;
        }
    }
}

//----------------------------------------------------------------------
void testRect(ST7735_TFT *display, ST7735_Canvas &canvas)
{
    std::cout << "Test Rect" << std::endl;
    
    uint16_t base_color = 0x1734;
    uint16_t front_color = 0xffff;
    uint8_t x = 10;
    uint8_t y = 0;
    uint8_t w = 5;
    uint8_t h = 15;
    uint8_t walk_factor = 15;
    int steps = 10;
    
    for(int i = 0; i < steps; i++)
    {
        canvas.fill(base_color);
        canvas.drawRect(x, y, w, h, 0, front_color);
        canvas.render(display);
        
        y += walk_factor;
        if(y >= canvas.getHeight())
        {
            walk_factor = -20;
        }
        else if(y <= 0)
        {
            walk_factor = 20;
        }
        
        bcm2835_delay(DELAY1);
    }
}
