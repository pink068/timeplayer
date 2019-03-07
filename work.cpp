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





int SayAsGroups(char * inbuffer)
{
	// get current time
	// convert to wav
	char buffer[200];
	int len;
	int i;
	
	for(int i = 0; inbuffer[i]; i++)
	{
      inbuffer[i] = tolower(inbuffer[i]);
    }
	
	len = strlen(inbuffer);
	strcat(inbuffer,"zzzzz");
	for (i=0;i<len;i+=5)
	{
		strncpy(buffer,&inbuffer[i],5);
		sprintf(buffer,"sox resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/silence.wav resources/group.wav", buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
		system(buffer);
		if(do_sound) system("aplay -q resources/group.wav");
	}	
 return 0;
}

