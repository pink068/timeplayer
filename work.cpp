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


int Say5Numbers(void)
{
	char buffer[200];
	char rbuffer[20];
	int i;
	
	for( i = 0; i<5; i++)
	{
      rbuffer[i] = rand()%10;
      rbuffer[i] +=48;
    }
	
	sprintf(buffer,"sox resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/silence_1.wav numbers.wav", rbuffer[0],rbuffer[1],rbuffer[2],rbuffer[3],rbuffer[4]);
//    cout << buffer << endl; 

	system(buffer);
	if(do_sound) system("aplay -q numbers.wav");
	return 0;
}

