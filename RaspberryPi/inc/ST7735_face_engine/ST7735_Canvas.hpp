/**********************************************************************
 * ST7735_Canvas.hpp
 * 
 * A class containing image information of a certain part of an ST7735
 * TFT Display. Created for easier animation handling. To be used in
 * combination with gavinlyonsrepos ST7735_TFT_RPI library
 * https://github.com/gavinlyonsrepo/ST7735_TFT_RPI
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#ifndef ST7735_CANVAS_HPP
#define ST7735_CANVAS_HPP

#include <stdint.h>
#include <vector>

#include "ST7735_TFT.hpp"

class ST7735_Canvas
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Constructor. Creates the underlying bitmap vector based on its
    /// parameters.
    ///
    /// @param width    The width of the canvas.
    /// @param height   The height of the canvas.
    /// @param color    The base color to initialize the canvas with.
    //
    ST7735_Canvas(int16_t width, int16_t height, uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Default copy constructor.
    //
    ST7735_Canvas(const ST7735_Canvas&) = default;
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Default destructor.
    //
    ~ST7735_Canvas() = default;
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Renders the canvas onto a a display to a certain position.
    ///
    /// @param display  The display to render the canvas to.
    /// @param x        The x coordinate to project the upper left corner to.
    /// @param y        The base color to initialize the canvas with.
    //
    void render(ST7735_TFT *display, int16_t x = 0, int16_t y = 0);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Fills the whole canvas with a certain color.
    ///
    /// @param color  The color to fill the canvas with.
    //
    void fill(uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Sets the color of a certain pixel on the canvas.
    ///
    /// @param x        The x coordinate of the pixel.
    /// @param y        The y coordinate of the pixel.
    /// @param color    The color to set the pixel to.
    //
    void setPixel(int16_t x, int16_t y, uint16_t color);
    void drawHLine(int16_t x, int16_t y, int16_t length, uint16_t color);
    void drawVLine(int16_t x, int16_t y, int16_t length, uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a line of a certain width onto the canvas. Uses Murphys version of the Bresenheim line drawing
    /// algorithm. Source: //Source: http://kt8216.unixcab.org/murphy/index.html
    ///
    /// @param x1       The x coordinate of the first end of the line.
    /// @param y1       The y coordinate of the first end of the line.
    /// @param x2       The x coordinate of the second end of the line.
    /// @param y2       The y coordinate of the second end of the line.
    /// @param color    The color of the line.
    /// @param width    The width of the line.
    //
    void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color, int16_t width);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws an upright rectangle onto the canvas. The corners can be rounded up.
    ///
    /// @param x        The x coordinate of the rectangle.
    /// @param y        The y coordinate of the rectangle.
    /// @param width    The width of the rectangle.
    /// @param height   The height of the rectangle.
    /// @param r        The radius of the corners of the rectangle.
    /// @param color    The color of the rectangle.
    //
    void drawRect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t r, uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws an upright ellipse onto the canvas. Algorithm is based on parametrized mathematical representation of
    /// an ellipse. Can also draw a circle if with and height are the same value.
    /// Source for filled in ellipse algorithm:
    /// https://stackoverflow.com/questions/10322341/simple-algorithm-for-drawing-filled-ellipse-in-c-c
    ///
    /// @param x            The x coordinate of the ellipse.
    /// @param y            The y coordinate of the ellipse.
    /// @param width        The width of the ellipse.
    /// @param height       The height of the ellipse.
    /// @param color        The color of the ellipse.
    /// @param thickness    The thickness of the ellipse if not filled in.
    /// @param fill         Decides if the ellipse is filled or only an outline.
    //
    void drawEllipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color, int16_t thickness,
                     bool fill);
                     
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a triangle onto the canvas.
    ///
    /// @param x0       The x coordinate of the first corner.
    /// @param y0       The y coordinate of the first corner.
    /// @param x1       The x coordinate of the second corner.
    /// @param y1       The y coordinate of the second corner.
    /// @param x2       The x coordinate of the third corner.
    /// @param y2       The y coordinate of the third corner.
    /// @param color    The color of the triangle.
    //
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Copies (partially) the content of one source canvas onto this one.
    ///
    /// @param source       The canvas to copy.
    /// @param source_x     The x coordinate of the upper left part which should be copied.
    /// @param source_y     The y coordinate of the upper left part which should be copied.
    /// @param width        The width of the content to copy.
    /// @param height       The height of the content to copy.
    /// @param target_x     The x coordinate to copy the upper left corner of the source content to.
    /// @param target_y     The y coordinate to copy the upper left corner of the source content to.
    /// @param alpha_color  Decides a color which should be used as transparent in the source canvas.
    //
    void blitCanvas(ST7735_Canvas &source, int16_t source_x, int16_t source_y, int16_t width, int16_t height,
                    int16_t target_x, int16_t target_y, uint16_t alpha_color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Returns all pixels as a 1d build-in array.
    ///
    /// @return     The bitmap array as a 1d build-in array.
    //
    uint16_t *getBitmapArray();
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Returns all pixels as a 1d stl vector.
    ///
    /// @return     The bitmap array as a 1d vector.
    //
    std::vector<uint16_t> getBitmap();
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Returns the width of the canvas.
    ///
    /// @return     The width of the canvas.
    //
    int16_t getWidth();
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Returns the height of the canvas.
    ///
    /// @return     The height of the canvas.
    //
    int16_t getHeight();
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Returns the total number of pixels in the canvas.
    ///
    /// @return     The number of pixels in the canvas.
    //
    uint16_t getPixelNum();
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Returns the color of a certain pixel on the canvas.
    ///
    /// @param x    The x coordinate of the pixel.
    /// @param y    The y coordinate of the pixel.
    ///
    /// @return     The color of the designated pixel.
    //
    uint16_t getPixelColor(int16_t x, int16_t y);
  
  private:
    std::vector<uint16_t> bitmap_;
    int16_t x_;
    int16_t y_;
    int16_t width_;
    int16_t height_;
    uint16_t pixel_num_;
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a filled in ellipse onto the canvas. Used by drawEllipse().
    /// Source:
    /// https://stackoverflow.com/questions/10322341/simple-algorithm-for-drawing-filled-ellipse-in-c-c
    ///
    /// @param x            The x coordinate of the ellipse.
    /// @param y            The y coordinate of the ellipse.
    /// @param width        The width of the ellipse.
    /// @param height       The height of the ellipse.
    /// @param color        The color of the ellipse.
    //
    void drawFilledEllipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a the outline of an ellipse onto the canvas. Used by drawEllipse().
    ///
    /// @param x            The x coordinate of the ellipse.
    /// @param y            The y coordinate of the ellipse.
    /// @param width        The width of the ellipse.
    /// @param height       The height of the ellipse.
    /// @param color        The color of the ellipse.
    /// @param thickness    The thickness of the ellipse.
    //
    void drawEllipseOutline(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color, int16_t thickness);
                            
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a normal rectangle with pointy corners. Used by drawRect().
    ///
    /// @param x            The x coordinate of the rectangle.
    /// @param y            The y coordinate of the rectangle.
    /// @param width        The width of the rectangle.
    /// @param height       The height of the rectangle.
    /// @param color        The color of the rectangle.
    //
    void drawPointyRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws line based on bresenhams algorithm which is tilted more to the x axis. Used by drawLine().
    ///
    /// @param x0           The x coordinate of the start of the line.
    /// @param y0           The y coordinate of the start of the line.
    /// @param x1           The x coordinate of the end of the line.
    /// @param y1           The y coordinate of the end of the line.
    /// @param dx           The slope of the line on the x axis.
    /// @param dy           The slope of the line on the y axis.
    /// @param color        The color of the line.
    /// @param width        The width of the line.
    //
    void drawXLine(int x0, int y0, int x1, int y1, int dx,int dy, uint16_t color, int width);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws line based on bresenhams algorithm which is tilted more to the y axis. Used by drawLine().
    ///
    /// @param x0           The x coordinate of the start of the line.
    /// @param y0           The y coordinate of the start of the line.
    /// @param x1           The x coordinate of the end of the line.
    /// @param y1           The y coordinate of the end of the line.
    /// @param dx           The slope of the line on the x axis.
    /// @param dy           The slope of the line on the y axis.
    /// @param color        The color of the line.
    /// @param width        The width of the line.
    //
    void drawYLine(int x0, int y0, int x1, int y1, int dx,int dy, uint16_t color, int width);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a line perpendicular to a bresenham line to make it thicker. Used by drawXLine().
    ///
    /// @param x0           The x coordinate of the start of the line.
    /// @param y0           The y coordinate of the start of the line.
    /// @param x1           The x coordinate of the end of the line.
    /// @param y1           The y coordinate of the end of the line.
    /// @param dx           The slope of the line on the x axis.
    /// @param dy           The slope of the line on the y axis.
    /// @param error_init   The current error of the bresenham line to initialize the perpendicular line position.
    /// @param width        The width of the line.
    /// @param x_step       A parameter changin with the orientation of the bresenham line. Required for correct
    ///                     depiction in all octants.
    /// @param y_step       A parameter changin with the orientation of the bresenham line. Required for correct
    ///                     depiction in all octants.
    /// @param color        The color of the line.
    //
    void drawXMurphyLine(int x0, int y0, int dx, int dy, int error_init, int width, int x_step, int y_step,
                         int width_init, uint16_t color);
                         
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a line perpendicular to a bresenham line to make it thicker. Used by drawYLine().
    ///
    /// @param x0           The x coordinate of the start of the line.
    /// @param y0           The y coordinate of the start of the line.
    /// @param x1           The x coordinate of the end of the line.
    /// @param y1           The y coordinate of the end of the line.
    /// @param dx           The slope of the line on the x axis.
    /// @param dy           The slope of the line on the y axis.
    /// @param error_init   The current error of the bresenham line to initialize the perpendicular line position.
    /// @param width        The width of the line.
    /// @param x_step       A parameter changin with the orientation of the bresenham line. Required for correct
    ///                     depiction in all octants.
    /// @param y_step       A parameter changin with the orientation of the bresenham line. Required for correct
    ///                     depiction in all octants.
    /// @param color        The color of the line.
    //
    void drawYMurphyLine(int x0, int y0, int dx, int dy, int error_init, int width, int x_step, int y_step,
                         int width_init, uint16_t color);
                         
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a filled in triangle with a flat bottom. Used by drawTriangle().
    ///
    /// @param x0           The x coordinate of P0 of the triangle.
    /// @param y0           The y coordinate of P0 of the triangle.
    /// @param x1           The x coordinate of P1 of the triangle.
    /// @param y1           The y coordinate of P1 of the triangle.
    /// @param x2           The x coordinate of P2 of the triangle.
    /// @param y2           The y coordinate of P2 of the triangle.
    /// @param color        The color of the triangle.
    //
    void bottomFlatTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    
    //-----------------------------------------------------------------------------------------------------------------
    ///
    /// Draws a filled in triangle with a flat top. Used by drawTriangle().
    ///
    /// @param x0           The x coordinate of P0 of the triangle.
    /// @param y0           The y coordinate of P0 of the triangle.
    /// @param x1           The x coordinate of P1 of the triangle.
    /// @param y1           The y coordinate of P1 of the triangle.
    /// @param x2           The x coordinate of P2 of the triangle.
    /// @param y2           The y coordinate of P2 of the triangle.
    /// @param color        The color of the triangle.
    //
    void topFlatTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
};

#endif //ST7735_CANVAS_HPP
