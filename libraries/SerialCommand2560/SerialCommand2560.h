/******************************************************************************* 
SerialCommand2560 - An Arduino library to tokenize and parse commands received over
a serial port. 
Copyright (C) 2011 Steven Cogswell  <steven.cogswell@gmail.com>
http://husks.wordpress.com  
Modified by Evan Allen on January 6 2014

Version 20110523B.
forked to Version 20140106   

Version History:
May 11 2011 - Initial version
May 13 2011 -	Prevent overwriting bounds of SerialCommandCallback[] array in addCommand()
			defaultHandler() for non-matching commands
January 6 2014 - specialized version for the atmega2560 (has max commands and delimiters at
                        a reasonable level, now it canbe used in conjunction with 
                        SerialCommand328 which has different values (could be an ifdef)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************************/
#ifndef SerialCommand2560_h
#define SerialCommand2560_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <string.h>

#define SERIALCOMMANDBUFFER 100
#define MAXSERIALCOMMANDS	20
#define MAXDELIMETER 10

#define SERIALCOMMANDDEBUG 1
#undef SERIALCOMMANDDEBUG      // Comment this out to run the library in debug mode (verbose messages)

class SerialCommand2560
{
	public:
		SerialCommand2560();      // Constructor
		void clearBuffer();   // Sets the command buffer to all '\0' (nulls)
		char *next();         // returns pointer to next token found in command buffer (for getting arguments to commands)
		void readSerial();    // Main entry point.  
		void addCommand(char *, void(*)());   // Add commands to processing dictionary
		void addDefaultHandler(void (*function)());    // A handler to call when no valid command received. 
	
	private:
		char inChar;          // A character read from the serial stream 
		char buffer[SERIALCOMMANDBUFFER];   // Buffer of stored characters while waiting for terminator character
		char bufPos;                        // Current position in the buffer
		char delim[MAXDELIMETER];           // null-terminated list of character to be used as delimeters for tokenizing (default " ")
		char term;                          // Character that signals end of command (default '\r')
		char *token;                        // Returned token from the command buffer as returned by strtok_r
		char *last;                         // State variable used by strtok_r during processing
		typedef struct _callback {
			char command[SERIALCOMMANDBUFFER];
			void (*function)();
		} SerialCommandCallback;            // Data structure to hold Command/Handler function key-value pairs
		int numCommand;
		SerialCommandCallback CommandList[MAXSERIALCOMMANDS];   // Actual definition for command/handler array
		void (*defaultHandler)();           // Pointer to the default handler function 
};

#endif //SerialCommand2560_h