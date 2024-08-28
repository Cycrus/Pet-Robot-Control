/**********************************************************************
 * ST7735_Eye.hpp
 * 
 * A class representing one eye of a face shown on the ST7735 display.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#ifndef ST7735_EYE_HPP
#define ST7735_EYE_HPP

#include <stdint.h>
#include "ST7735_Canvas.hpp"

#define LEFT_EYE -1
#define RIGHT_EYE 1

class ST7735_Eye
{
    public:
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Constructor. Assembles the default eye.
        ///
        /// @param eye_side              Defines if the eye is a left or a right one.
        /// @param corner_radius         Defines the roundness of the eye.
        /// @param canvas_width          The width of the canvas the eye is placed in.
        /// @param canvas_height         The height of the canvas the eye is placed in.
        /// @param background_color      The color of the transparent background, will not be visible later on.
        /// @param eye_color             The color of the eye.
        /// @param glare_color           The color of the glare on the eye.
        //
        ST7735_Eye(int16_t eye_side,
                   int16_t corner_radius,
                   int16_t canvas_width,
                   int16_t canvas_height,
                   uint16_t background_color,
                   uint16_t eye_color,
                   uint16_t glare_color);
                   
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Default copy constructor.
        //
        ST7735_Eye(const ST7735_Eye&) = default;
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Default destructor.
        //
        ~ST7735_Eye() = default;
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Blits the eye with all its components onto a canvas.
        ///
        /// @param canvas    The canvas the eye is blitted on.
        /// @param x         The x position the eye is blitted onto the target canvas.
        /// @param y         The y position the eye is blitted onto the target canvas.
        //
        void blit(ST7735_Canvas &canvas, int16_t x, int16_t y);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Opens/closes the upper eyelid a certain amount. Mainly responsible for closure and openness of the eye.
        ///
        /// @param value    The amount how much the upper eyelid should be opened or closed. Negative for close, positive
        ///                 for open.
        //
        void moveUpperEyelid(int16_t value);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Opens/closes the lower eyelid a certain amount. Mainly responsible for increased emotional expression.
        /// Defaults to "happy" without eyebrows.
        ///
        /// @param value    The amount how much the lower eyelid should be opened or closed. Negative for close, positive
        ///                 for open.
        //
        void moveLowerEyelid(int16_t value);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Moves the eye a certain amount on the x and y axis.
        ///
        /// @param x    The change of positon on the x axis.
        /// @param y    The change of positon on the y axis.
        //
        void moveEye(int16_t x, int16_t y);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Moves the eyebrows up or down a certain amount. Enables a range of
        /// emotions when further down (value is higher). Defaults to "annoyed" with default eyebrow angle.
        ///
        /// @param depth    The amount the eyebrow should be lowered (positive) or raised (negative).
        //
        void moveEyebrowDepth(int16_t depth);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Rotates the eyebrows a certain angle. Is mainly enabled by lowered eyebrow. Negative values indicate more
        /// aggression & suspicion, while positive values indicate fear & devotion.
        /// Please note, that the angle is not a real radian angle, but a value for the steepness (slope) of the eyebrow.
        ///
        /// @param angle    The amount the eyebrow should be rotated.
        //
        void moveEyebrowAngle(int16_t angle);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Sets the position of the upper eyelid. Mainly responsible for closure and openness of the eye.
        ///
        /// @param percentage    The percentage how open the upper eyelid should be.
        //
        void setUpperEyelid(int16_t percentage);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Sets the position of the lower eyelid. Mainly responsible for increased emotional expression.
        /// Defaults to "happy" without eyebrows.
        ///
        /// @param percentage    The percentage how open the lower eyelid should be.
        //
        void setLowerEyelid(int16_t percentage);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Sets the position of the eye on the frame/canvas.
        ///
        /// @param x    The new x position of the eye.
        /// @param y    The new y position of the eye.
        //
        void setEyePos(int16_t x, int16_t y);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Sets the depth of the eyebrow. Mainly responsible for increased emotional expression. Enables a range of
        /// emotions when further down (value is higher). Defaults to "happy" without eyebrows.
        ///
        /// @param depth    The depth of the eyebrow into the upper eye segment.
        //
        void setEyebrowDepth(int16_t depth);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Sets the angle of the eyebrow. Mainly responsible for general emotional expression. Is mainly enabled by lowered
        /// eyebrow. Negative values indicate more aggression & suspicion, while positive values indicate fear & devotion.
        /// Please note, that the angle is not a real radian angle, but a rough estimation for the slope of the eyebrow.
        ///
        /// @param angle    The angle of the eyebrow.
        //
        void setEyebrowAngle(int16_t angle);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Getters
        //
        int16_t getX();
        int16_t getY();
        int16_t getNormX();
        int16_t getNormY();
        
        int16_t getMinX();
        int16_t getMaxX();
        int16_t getMinY();
        int16_t getMaxY();
        
        
    private:
        const uint16_t background_color_;
        const uint16_t eye_color_;
        const uint16_t glare_color_;
        
        ST7735_Canvas frame_;
        
        int16_t eye_side_;
        int16_t corner_radius_;
        
        int16_t MAX_UPPER_EYELID_ ;
        int16_t MIN_UPPER_EYELID_;
        int16_t upper_eyelid_;
        
        int16_t MIN_X_;
        int16_t MIN_Y_;
        int16_t MAX_X_;
        int16_t MAX_Y_;
        int16_t DEFAULT_MAX_X_;
        int16_t DEFAULT_MAX_Y_;
        int16_t norm_x_;
        int16_t norm_y_;
        int16_t x_;
        int16_t y_;
        
        int16_t norm_width_;
        int16_t norm_height_;
        int16_t width_;
        int16_t height_;
        
        int16_t MAX_LOWER_EYELID_;
        int16_t MIN_LOWER_EYELID_;
        int16_t lower_eyelid_;
        
        int16_t MAX_EYEBROW_DEPTH_;
        int16_t MIN_EYEBROW_DEPTH_;
        int16_t eyebrow_depth_;
        
        int16_t MAX_EYEBROW_ANGLE_;
        int16_t MIN_EYEBROW_ANGLE_;
        int16_t eyebrow_angle_;
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Updates critical parameters of the eye at once. Is called together with blit().
        //
        void update();
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Draws the shape of the eye onto the internal frame/canvas. Since upper eyelid closure is defined as the height
        /// of the eye, this function is also responsible for upper eyelid closure.
        //
        void drawEye();
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Draws the shape of the lower eyelid onto the internal frame/canvas.
        //
        void drawLowerEyelid();
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Draws the shape of the eyebrow eyelid onto the internal frame/canvas.
        //
        void drawEyebrow();
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Simulates perspective of the eye by changing it's size based on if it looks mroe to the right or the left side.
        //
        void simulatePerspective();
};

#endif // ST7735_EYE_HPP
