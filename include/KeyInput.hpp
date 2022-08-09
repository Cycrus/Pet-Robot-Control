/**********************************************************************
 * KeyInput.hpp
 * 
 * A class for non-blocking input from a keyboard.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#ifndef KEYINPUT_HPP
#define KEYINPUT_HPP

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string>
#include <stdio.h>

enum ButtonState {RELEASE, PRESS, HOLD, ERROR};

#define K_0 82
#define K_1 79
#define K_2 80
#define K_3 81
#define K_4 75
#define K_5 76
#define K_6 77
#define K_7 71
#define K_8 72
#define K_9 73
#define K_DOT 83
#define K_ENTER 96
#define K_PLUS 78
#define K_MINUS 74
#define K_BACKSPACE 14
#define K_EQUALS 13
#define K_TAB 15
#define K_ESC 1
#define K_DIVIDE 98
#define K_MULTIPLY 55
#define K_NUMLOCK 69

class KeyInput
{
    public:
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Constructor. Calls initializing function to connect to set keyboard.
        ///
        /// @param keyboard_path    The path to the Unix file of the keyboard input stream.
        ///                         Bsp: "/dev/input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.1:1.0-event-kbd"
        /// @param is_blocking      Decides if the process is blocked when calling getKey() until a button is pressed.
        //
        KeyInput(std::string keyboard_path, bool is_blocking);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Deleted copy constructor.
        //
        KeyInput(const KeyInput&) = delete;
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Default destructor.
        //
        ~KeyInput() = default;
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Initializes the keyboard input stream by opening a connection to the given file.
        ///
        /// @param keyboard_path    The path to the Unix file of the keyboard input stream.
        ///                         Bsp: "/dev/input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.1:1.0-event-kbd"
        /// @param is_blocking      Decides if the process is blocked when calling getKey() until a button is pressed.
        //
        void init(std::string keyboard_path, bool is_blocking);
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Grabs a key if one is currently pressed and stores it in the internal key member variables.
        /// It can be read with getCode() and getState().
        /// If no key is pressed the stored code is 0 and state is ButtonState::ERROR.
        //
        void getKey();
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Returns the code (identity) of the last stored key grabbed by getKey(). See definition list above. Please note,
        /// that those codes are not equivalent to ASCII codes.
        ///
        /// @return     The code of the last stored key.
        //
        int getCode();
        
        //-----------------------------------------------------------------------------------------------------------------
        ///
        /// Returns the state (value) of the last stored key grabbed by getKey(). This state can be RELEASE, PRESS or HOLD.
        /// It can also be ERROR if no key is pressed. Please see enum at top of the file.
        ///
        /// @return     The state of the last stored key.
        //
        ButtonState getState();
    
    private:
        struct input_event key_;
        std::string keyboard_path_;
        bool is_blocking_;
        int connection_id_;
};

#endif // KEYINPUT_HPP
