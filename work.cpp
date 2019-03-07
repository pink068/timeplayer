#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "serial.h"
#include "library.h"
#include <time.h>

using namespace std;


int MakeTimeFile(void)
{
	// get current time
	// convert to wav
	struct tm * mytime;
	time_t mysecs;
	char buffer[200];
	
	mysecs = time(NULL);
	mytime = gmtime(&mysecs);
	sprintf(buffer, "echo \"%2d %02d and %2d seconds\" |text2wave -o resources/nowtime.wav",mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
	system(buffer);	
 return 0;
}


