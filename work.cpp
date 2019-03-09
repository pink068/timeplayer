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

int Say (char * inbuffer)
{
	char buffer[2000];
	sprintf(buffer, "echo \"%s\" |text2wave -o temp.wav",inbuffer);
	cout << buffer << endl; 
	system(buffer);	
	return 0;
}
