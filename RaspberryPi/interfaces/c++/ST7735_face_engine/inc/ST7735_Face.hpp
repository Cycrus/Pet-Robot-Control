/**********************************************************************
 * ST7735_Face.hpp
 * 
 * A class representing the face together with all possible movements
 * shown on the ST7735 display.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#ifndef ST7735_FACE_HPP
#define ST7735_FACE_HPP

#include <stdint.h>
#include "ST7735_Eye.hpp"
#include "ST7735_TFT.hpp"

enum Emotion
{
  Neutral,
  Happy,
  Angry,
  Sad
};

class ST7735_Face
{
    public:
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Constructor. Assembles the basic face but does not render it onto the frame already.
        ///
        /// @param screen_width      The width of the screen to display the face to.
        /// @param screen_height     The height of the screen to display the face to.
        /// @param face_color        The base color of the face.
        /// @param left_eye_color    The color of the left eye.
        /// @param right_eye_color   The color of the right eye.
        /// @param accent_color      The color of certain accents, such as glares.
        //
        ST7735_Face(int16_t screen_width,
                    int16_t screen_height,
                    uint16_t face_color,
                    uint16_t left_eye_color,
                    uint16_t right_eye_color,
                    uint16_t accent_color);
                    
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Default copy constructor.
        //
        ST7735_Face(const ST7735_Face&) = default;
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Default destructor.
        //
        ~ST7735_Face() = default;

        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Renders a certain emotion onto the face.
        ///
        /// @param emotion    The emotion to render.
        /// @param strength   A float between 0 and 1 to indicate the strength of the emotion.
        //
        void setEmotion(Emotion emotion, float strength);


        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Moves the eyes to look at a certain direction.
        ///
        /// @param x    A float between -1 and 1 indicating the x direction to look at.
        /// @param y    A float between -1 and 1 indicating the y direction to look at.
        //
        void lookAt(float x, float y);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Renders the face with both eyes onto a ST7725_TFT display
        ///
        /// @param display    The display the face is rendered onto.
        //
        void render(ST7735_TFT *display);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Sets the running_ parameter to false and stops the FaceLoop() method therefore.
        //
        void stopFaceLoop();

        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Starts the face loop and sets the running_ parameter to true.
        ///
        /// @param frequency  The frequency to render the face with.
        //
        void startFaceLoop(ST7735_TFT *display, int frequency);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// A loop showing and constantly updating the face based on certain values. Acts as the main entry point.
        /// Should be changed and run on it's own thread.
        ///
        /// @param display    The display the face is rendered onto.
        /// @param frequency  The frequency to render the face with.
        //
        void faceLoop(ST7735_TFT *display, int frequency);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// A loop showing some capabilities of the face engine.
        ///
        /// @param display    The display the face is rendered onto for the demonstration.
        //
        void faceDemoLoop(ST7735_TFT *display);
        
    private:
        const uint16_t FRAME_DELAY_ = 45;
    
        uint16_t face_color_;
        uint16_t left_eye_color_;
        uint16_t right_eye_color_;
        uint16_t accent_color_;
        
        ST7735_Canvas frame_;
        ST7735_Eye left_eye_;
        ST7735_Eye right_eye_;
        
        bool running_;
};

#endif // ST7735_FACE_HPP
