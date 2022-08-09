/**********************************************************************
 * KeyInput.cpp
 * 
 * Implementation of the KeyInput class.
 * 
 * Author: Cyril Marx
 * Created: August 2022
 **********************************************************************/

#include "KeyInput.hpp"
#include <iostream>

KeyInput::KeyInput(std::string keyboard_path, bool is_blocking)
{
    connection_id_ = -1;
    init(keyboard_path, is_blocking);
}

//-----------------------------------------------------------------------------------------------------------------
void KeyInput::init(std::string keyboard_path, bool is_blocking)
{
    if(connection_id_ != -1)
    {
	connection_id_ = -1;
    }
    
    keyboard_path_ = keyboard_path;
    is_blocking_ = is_blocking;

    connection_id_ = open(keyboard_path_.c_str(), O_RDONLY);

    if(!is_blocking_)
    {
	fcntl(connection_id_, F_SETFL, O_NONBLOCK);
    }
        
}

//-----------------------------------------------------------------------------------------------------------------
void KeyInput::getKey()
{
    struct input_event new_key, final_key;
    ssize_t buffer;
    
    if(access(keyboard_path_.c_str(), F_OK) != 0 || connection_id_ == -1)
    {
	init(keyboard_path_, is_blocking_);
    }

    buffer = read(connection_id_, &new_key, sizeof new_key);

    final_key = new_key;

    if(buffer == (ssize_t)-1)
    {
	if(errno == EINTR)
	{
	    std::cout << "error" << std::endl;
	}
    }
    else
    {
	if(buffer != sizeof final_key)
	{
	    std::cout << "error" << std::endl;
	}
    }

    key_ = final_key;
}

//-----------------------------------------------------------------------------------------------------------------
int KeyInput::getCode()
{
    if(key_.type == EV_KEY)
        return key_.code;
    
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
ButtonState KeyInput::getState()
{
    if(key_.type == EV_KEY)
        return static_cast<ButtonState>(key_.value);
        
    return ButtonState::ERROR;
}
