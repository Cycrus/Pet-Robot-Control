/*******************************************************************
 * COGNA FUNCTION
 *
 * Filename keyinput.h
 *
 * A library for getting keyboard events in real time.
 *
 * Author: Cyril Marx
 * Date: 02.09.2020
 *******************************************************************/

#ifndef KEYINPUT
#define KEYINPUT

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

#define RELEASE 0
#define PRESS 1
#define HOLD 2

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

//
// Function to initialize keyboard. It opens the pipe to the device file.
//
// @param bool is_blocking: A boolean value to set if the keyboard read
//                          should block the process or not. If set to
//                          0, it blocks the process. If any other number
//                          than 0, it does not.
//
// @return int:             connection number of the device or error code
//                          if something went wrong
//
int init_keyboard(bool is_blocking=0){
	const char *dev = "/dev/input/by-path/platform-fd500000.pcie-pci-0000:01:00.0-usb-0:1.1:1.0-event-kbd";

	int fd = open(dev, O_RDONLY);
	if(!is_blocking)
		fcntl(fd, F_SETFL, O_NONBLOCK);

	if(fd == -1){
	printf("[ERROR] Cannot init keyboard connection: %s\n",
			strerror(errno));

		return EXIT_FAILURE;
	}
	else
		return fd;
}

//************************************************************************

//
// Function to fetch the keyboard event.
//
// @param int connection:      A connection number, normally received by
//                             the init_keyboard function.
// @param struct input_event*: A linux input_event. The returned event
//                             is stored in this pointer.
//
// @return int:                error code, if something went wrong
//
int get_key(int connection, struct input_event *outer_event){
	struct input_event this_event;
	ssize_t buffer;

	this_event.code = 0;

	buffer = read(connection, &this_event, sizeof this_event);

	if(buffer == (ssize_t)-1){
		if(errno == EINTR){
			printf("%s.\n", strerror(errno));
			return -1;
		}
	}
	else{
		if(buffer != sizeof this_event){
			errno = EIO;
			printf("%s.\n", strerror(errno));
			return -1;
		}
	}

	*outer_event = this_event;

	return 0;
	
}

#endif
