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

int MakePowerFile(void)
{
	char buffer[200];
	sprintf(buffer,"sox resources/p.wav resources/%c.wav resources/%c.wav resources/silence_1.wav temp.wav", power[0],power[1]);
	system(buffer);	
 return 0;
}
