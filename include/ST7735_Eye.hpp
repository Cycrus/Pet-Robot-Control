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
        /// @param canvas_width          The width of the canvas the eye is placed in.
        /// @param canvas_height         The height of the canvas the eye is placed in.
        /// @param background_color      The color of the transparent background, will not be visible later on.
        /// @param eye_color             The color of the eye.
        /// @param glare_color           The color of the glare on the eye.
        //
        ST7735_Eye(int16_t eye_side,
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
        
        void blit(ST7735_Canvas &canvas, int16_t x, int16_t y);
        
        void update();
        
        void setUpperEyelid(int16_t percentage);
        void moveUpperEyelid(int16_t value);
        
        void setLowerEyelid(int16_t percentage);
        void moveLowerEyelid(int16_t value);
        
        void setEyePos(int16_t x, int16_t y);
        void moveEye(int16_t x, int16_t y);
        
        void setEyebrowDepth(int16_t depth);
        void moveEyebrowDepth(int16_t depth);
        
        void setEyebrowAngle(int16_t angle);
        void moveEyebrowAngle(int16_t angle);
                
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
        
        int16_t MAX_UPPER_EYELID_ ;
        int16_t MIN_UPPER_EYELID_;
        int16_t upper_eyelid_;
        
        int16_t MIN_X_;
        int16_t MIN_Y_;
        int16_t MAX_X_;
        int16_t MAX_Y_;
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
        
        void drawEye();
        void drawLowerEyelid();
        void drawEyebrow();
};

#endif // ST7735_EYE_HPP
