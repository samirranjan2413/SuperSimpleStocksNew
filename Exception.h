#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string.h>

class Exception
{
public:
   char message[1000];

	Exception(char *msg)
	{   
		message[0] = '\0';
		strncpy(message, msg, 999);
	}
};

#endif