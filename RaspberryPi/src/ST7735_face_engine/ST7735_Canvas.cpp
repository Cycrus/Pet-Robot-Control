/**********************************************************************
 * ST7735_Canvas.cpp
 * 
 * The implementation of the ST7735_Canvas class.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#include "ST7735_Canvas.hpp"

#include <cmath>
#include "ST7735_Utils.hpp"

ST7735_Canvas::ST7735_Canvas(int16_t width, int16_t height, uint16_t color) :
width_(width), height_(height)
{
    pixel_num_ = width_ * height_;
    bitmap_.insert(std::begin(bitmap_), pixel_num_, color);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::render(ST7735_TFT *display, int16_t x, int16_t y)
{
    display->TFTdrawCanvas16(x, y, getBitmapArray(), (int16_t)width_, (int16_t)height_);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::fill(uint16_t color)
{
    std::fill(std::begin(bitmap_), std::begin(bitmap_) + pixel_num_,
              color);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::setPixel(int16_t x, int16_t y, uint16_t color)
{
    if(x >= width_ || y >= height_ || x < 0 || y < 0)
    {
        return;
    }
    
    uint16_t pixel_id = ST7735_Utils::coords2DTo1D(x, y, width_);
    bitmap_.at(pixel_id) = color;
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawHLine(int16_t x, int16_t y, int16_t length, uint16_t color)
{
    int16_t right_end = x + length;
    
    for(int16_t x_it = x; x_it < right_end; x_it++)
    {
        if(x_it > width_)
        {
            return;
        }
        
        setPixel(x_it, y, color);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawVLine(int16_t x, int16_t y, int16_t length, uint16_t color)
{
    int16_t lower_end = y + length;
    
    for(int16_t y_it = y; y_it < lower_end; y_it++)
    {
        if(y_it > height_)
        {
            return;
        }
        
        setPixel(x, y_it, color);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                             uint16_t color, int16_t width)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    
    if(dx >= dy)
    {
        drawXLine(x0, y0, x1, y1, dx, dy, color, width);
    }
    else
    {
        drawYLine(x0, y0, x1, y1, dx, dy, color, width);
    }
}

#include <iostream>
//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawRect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t r, uint16_t color)
{
    if(r > 0)
    {
        if(r * 2 >= width)
        {
            r = width / 2;
        }
        else if(r * 2 >= height)
        {
            r = height / 2;
        }
        
        drawEllipse(x + r, y + r, r, r, color, 1, true);
        drawEllipse(x + width - r, y + r, r, r, color, 1, true);
        drawEllipse(x + r, y + height - r, r, r, color, 1, true);
        drawEllipse(x + width - r, y + height - r, r, r, color, 1, true);
        
        drawPointyRect(x + r, y, width - 2 * r, height + 1, color);
        drawPointyRect(x, y + r, width + 1, height - 2 * r, color);
    }
    
    else
    {
        drawPointyRect(x, y, width, height, color);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawEllipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color,
                                int16_t thickness, bool fill)
{
    if(fill)
    {
        drawFilledEllipse(x, y, width, height, color);
    }
    
    else
    {
        drawEllipseOutline(x, y, width, height, color, thickness);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                                 uint16_t color)
{
    //Source: http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    
    int16_t y_0 = y0;
    int16_t y_1 = y1;
    int16_t y_2 = y2;
    int16_t x_0 = x0;
    int16_t x_1 = x1;
    int16_t x_2 = x2;
    
    if(y1 < y0)
    {
        ST7735_Utils::swap(x_1, x_0);
        ST7735_Utils::swap(y_1, y_0);
    }
    if(y2 < y0)
    {
        ST7735_Utils::swap(x_2, x_0);
        ST7735_Utils::swap(y_2, y_0);
    }
    if(y2 < y1)
    {
        ST7735_Utils::swap(x_2, x_1);
        ST7735_Utils::swap(y_2, y_1);
    }
    
    if(y_1 == y_2)
    {
        bottomFlatTriangle(x_0, y_0, x_1, y_1, x_2, y_2, color);
    }
    
    else if(y_0 == y_1)
    {
        topFlatTriangle(x0, y0, x1, y1, x2, y2, color);
    }
    
    else
    {
        int16_t x3 = x0 + ((float)y1 - (float)y0) / ((float)y2 - (float)y0 * (x2 - y0));
        int16_t y3 = y1;
        bottomFlatTriangle(x0, y0, x1, y1, x3, y3, color);
        topFlatTriangle(x1, y1, x3, y3, x2, y2, color);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::blitCanvas(ST7735_Canvas &source, int16_t source_x, int16_t source_y, int16_t width,
                               int16_t height, int16_t target_x, int16_t target_y, uint16_t alpha_color)
{
    if(source_x + width > source.width_)
    {
        width = source.width_ - source_x;
    }
    
    if(source_y + height > source.height_)
    {
        height = source.height_ - source_y;
    }
    
    for(int16_t y = 0; y < height; y++)
    {
        if(y + target_y > height_ || y + target_y < 0)
        {
            continue;
        }
        
        for(int16_t x = 0; x < width; x++)
        {
            if(x + target_x > width_ || x + target_x < 0)
            {
                continue;
            }
            
            uint16_t source_pixel_col = source.getPixelColor(x, y);
            if(source_pixel_col != alpha_color)
            {
                setPixel(x + target_x, y + target_y, source_pixel_col);
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t *ST7735_Canvas::getBitmapArray()
{
    uint16_t *array = &bitmap_.at(0);
    return array;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<uint16_t> ST7735_Canvas::getBitmap()
{
    return bitmap_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Canvas::getWidth()
{
    return width_;
}

//-----------------------------------------------------------------------------------------------------------------
int16_t ST7735_Canvas::getHeight()
{
    return height_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t ST7735_Canvas::getPixelNum()
{
    return pixel_num_;
}

//-----------------------------------------------------------------------------------------------------------------
uint16_t ST7735_Canvas::getPixelColor(int16_t x, int16_t y)
{
    if(x >= width_ || y >= height_)
    {
        return 0x0000;
    }
    
    uint16_t id = ST7735_Utils::coords2DTo1D(x, y, width_);
    return bitmap_.at(id);
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawFilledEllipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
    // Source: https://stackoverflow.com/questions/10322341/simple-algorithm-for-drawing-filled-ellipse-in-c-c
    int hh = height * height;
    int ww = width * width;
    int hhww = hh * ww;
    int x0 = width;
    int dx = 0;
    
    for(int x_it = -width; x_it <= width; x_it++)
    {
        setPixel(x + x_it, y, color);
    }
    
    for(int y_it = 1; y_it <= height; y_it++)
    {
        int x1 = x0 - (dx - 1);
        for( ; x1 > 0; x1--)
        {
            if(x1 * x1 * hh + y_it * y_it * ww <= hhww)
            {
                break;
            }
        }
        
        dx = x0 - x1;
        x0 = x1;
        
        for(int x_it = -x0; x_it <= x0; x_it++)
        {
            setPixel(x + x_it, y - y_it, color);
            setPixel(x + x_it, y + y_it, color);
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawEllipseOutline(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color,
                                       int16_t thickness)
{
    for(int circle = 0; circle <= thickness; circle++)
    {
        int width0 = width - circle;
        int height0 = height - circle;
        float theta = 0;
        float step = 2 * M_PI / 40;
        int x_it = 0;
        int y_it = 0;
        
        
        while(theta < 2 * M_PI)
        {
            int new_x_it = x + width0 * cos(theta);
            int new_y_it = y + height0 * sin(theta);
            
            setPixel(new_x_it, new_y_it, color);
            
            if(theta > 0)
            {
                drawLine(x_it, y_it, new_x_it, new_y_it,
                         color, 1);
            }
            
            x_it = new_x_it;
            y_it = new_y_it;
            
            theta += step;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawPointyRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
    int16_t lower_end = y + height;
    
    for(int16_t y_it = y; y_it < lower_end; y_it++)
    {
        if(y_it > height_)
        {
            return;
        }
        
        drawHLine(x, y_it, width, color);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawXLine(int x0, int y0, int x1, int y1, int dx,int dy, uint16_t color, int width)
{
    int p_error = 0;
    int error = 0;
    int x_step = 1;
    int y_step = 1;
    int y = y0;
    int x = x0;
    if(x1 < x0)
    {
        x_step = -1;
    }
    if(y1 < y0)
    {
        y_step = -1;
    }
    int threshold = dx - 2 * dy;
    int e_diag = -2 * dx;
    int e_square = 2 * dy;
    int length = dx;
    
    for(int p = 0; p < length ; p++)
    {
        drawXMurphyLine(x, y, dx ,dy, p_error, width, x_step, y_step, error, color);
        if(error > threshold)
        {
            y += y_step;
            error += e_diag;
            if(p_error > threshold)
            {
                drawXMurphyLine(x, y, dx, dy, p_error + e_diag + e_square,
                               width, x_step, y_step, error, color);
                p_error += e_diag;
            }
            p_error += e_square;
        }
        error += e_square;
        x += x_step;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawYLine(int x0, int y0, int x1, int y1, int dx,int dy, uint16_t color, int width)
{
    int p_error = 0;
    int error = 0;
    int x_step = 1;
    int y_step = 1;
    int y = y0;
    int x = x0;
    if(x1 < x0)
    {
        x_step = -1;
    }
    if(y1 < y0)
    {
        y_step = -1;
    }
    int threshold = dy - 2 * dx;
    int e_diag = -2 * dy;
    int e_square = 2 * dx;
    int length = dy;
    
    for(int p = 0; p < length ; p++)
    {
        setPixel(x, y, color);
        drawYMurphyLine(x, y, dx ,dy, p_error, width, x_step, y_step, error, color);
        if(error > threshold)
        {
            x += x_step;
            error += e_diag;
            if(p_error > threshold)
            {
                drawYMurphyLine(x, y, dx, dy, p_error + e_diag + e_square,
                                width, x_step, y_step, error, color);
                p_error += e_diag;
            }
            p_error += e_square;
        }
        error += e_square;
        y += y_step;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawXMurphyLine(int x0, int y0, int dx, int dy, int error_init, int width, int x_step, int y_step,
                                    int width_init, uint16_t color)
{
    int threshold = dx - 2 * dy;
    int e_diag = -2 * dx;
    int e_square = 2 * dy;
    int wthr = 2 * width * sqrt(dx * dx + dy * dy);
    
    int x = x0;
    int y = y0;
    int error = error_init;
    int tk = dx + dy - width_init;
    
    while(tk <= wthr)
    {
        setPixel(x, y, color);
        if(error > threshold)
        {
            x -= x_step;
            error += e_diag;
            tk += 2 * dy;
        }
        error += e_square;
        y += y_step;
        tk += 2 * dx;
    }
    
    x = x0;
    y = y0;
    error = -error_init,
    tk = dx + dy + width_init;
    
    while(tk <= wthr)
    {
        setPixel(x, y, color);
        if(error > threshold)
        {
            x += x_step;
            error += e_diag;
            tk += 2 * dy;
        }
        error += e_square;
        y -= y_step;
        tk += 2 * dx;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::drawYMurphyLine(int x0, int y0, int dx, int dy, int error_init, int width, int x_step,
                                    int y_step, int width_init, uint16_t color)
{
    int threshold = dy - 2 * dx;
    int e_diag = -2 * dy;
    int e_square = 2 * dx;
    int wthr = 2 * width * sqrt(dy * dy + dx * dx);
    
    int x = x0;
    int y = y0;
    int error = error_init;
    int tk = dy + dx - width_init;
    
    while(tk <= wthr)
    {
        setPixel(x, y, color);
        if(error > threshold)
        {
            y -= y_step;
            error += e_diag;
            tk += 2 * dx;
        }
        error += e_square;
        x += x_step;
        tk += 2 * dy;
    }
    
    x = x0;
    y = y0;
    error = -error_init,
    tk = dy + dx + width_init;
    
    while(tk <= wthr)
    {
        setPixel(x, y, color);
        if(error > threshold)
        {
            y += y_step;
            error += e_diag;
            tk += 2 * dx;
        }
        error += e_square;
        x -= x_step;
        tk += 2 * dy;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::bottomFlatTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                                       uint16_t color)
{
    float invslope1 = (x1 - x0) / (y1 - y0);
    float invslope2 = (x2 - x0) / (y2 - y0);
    
    int16_t currx1 = x0;
    int16_t currx2 = x0;
    
    for(int16_t y = y0; y <= y1; y++)
    {
        drawLine(currx1, y, currx2, y, color, 1);
        currx1 += invslope1;
        currx2 += invslope2;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ST7735_Canvas::topFlatTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                                    uint16_t color)
{
    float invslope1 = (x2 - x0) / (y2 - y0);
    float invslope2 = (x2 - x1) / (y2 - y1);
    
    int16_t currx1 = x2;
    int16_t currx2 = x2;
    
    for(int16_t y = y2; y > y0; y--)
    {
        drawLine(currx1, y, currx2, y, color, 1);
        currx1 -= invslope1;
        currx2 -= invslope2;
    }
}
