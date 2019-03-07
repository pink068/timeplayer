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




int MakeDTGFile(void)
{
	// get current time
	// convert to wav
	struct tm * mytime;
	time_t mysecs;
	char buffer[200];
	char tbuffer[200];
	
	mysecs = time(NULL);
	mytime = gmtime(&mysecs);

	strftime(tbuffer, 20, "%d%H%M", mytime);
	sprintf(buffer,"sox resources/timeis.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/dtg.wav", tbuffer[0],tbuffer[1],tbuffer[2],tbuffer[3],tbuffer[4],tbuffer[5]);
	system(buffer);
	
 return 0;
}



int ProcessLine(char * line)
{
	char localbuffer[2000];
    strncpy(localbuffer,&line[1],20);	
	
	switch (line[0])
	{
		case 'C':
		  cout << "---- Saying Callsign" << endl; 
	      if(do_sound) system("aplay -q resources/callsign.wav");
		  break;

		case 'D':
		  cout << "---- Saying DTG" << endl; 
		  MakeDTGFile();
	      if(do_sound) system("aplay -q resources/dtg.wav");
		  break;

		case 'G':
		  cout << "---- Saying group of 5" << endl; 
		  SayAsGroups(localbuffer);
	      
		  break;	
		  
	    case 'F':
		  cout << "---- Changing Frequency "; 
		  cout << localbuffer << endl;
          if(live_hardware)   Rig.Command( RADIO_FREQ, localbuffer);
          break;
	  
		case 'P':
		  cout << "---- Changing Power "; 
		  cout << localbuffer << endl;
          if(live_hardware)   Rig.Command( RADIO_POWER, localbuffer);
		  break;


		case 'T':
		  cout << "---- Saying Time" << endl; 
		  MakeTimeFile();
	      if(do_sound) system("aplay -q resources/nowtime.wav");
		  break;


		  
		default:
		  cout << "Letter not recognised\n"; 
		  break;
		
	}
	return 0;
}










int ProcessScript(char * filename)
{
	// open the file
	// read a line
	// process the line
	// loop till ended

  string line;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
	  ProcessLine((char*)line.c_str());
      
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
	return 0;
	
}



int ProcessFile(int entrytime)
{
  char filename[20];
 // printf("%04d Running commands\n",entrytime);

  sprintf(filename,"scripts/%04d.txt",entrytime);
  if (fileExists(filename))
  {  
	ProcessScript(filename);
  }
  else
  {
    printf("%04d No specific commands to process\n",entrytime);
    sprintf(filename,"scripts/24%2d.txt",entrytime%60);  
    if (fileExists(filename))
    {  
	  ProcessScript(filename);
    }
    else
    {
      printf("%04d No hourly commands to process\n",entrytime);
    }  
  }
  
  return 0;
}

 


int Playsound(int entrytime)
{
  char filename[20];
  char commandbuffer[100];

  sprintf(filename,"resources/%04d.wav",entrytime);

  if (fileExists(filename))
  {
	sprintf(commandbuffer,"aplay -q %04d.wav",entrytime);
	printf("%04d Playing\[%s]\n",entrytime,commandbuffer);	

	if(do_sound) system(commandbuffer);
	
  }
  else
  {
	printf("%04d No specific sound to play\n",entrytime);
	sprintf(filename,"resources/24%02d.wav",entrytime%60);  
	if (fileExists(filename))
	{
	  sprintf(commandbuffer,"aplay -q %s",filename);
      printf("%04d Playing hourly [%s]\n",entrytime,commandbuffer );	

      if(do_sound) system(commandbuffer);		
	  
	}  // end of if exists
	else
	{
      printf("%04d No hourly sound to play\n",entrytime);	  
    } 
  }   // end of else

  return 0;  
}

bool fileExists(const char* file) {
    struct stat buf;
    return (stat(file, &buf) == 0);
}


int WriteToFile(char * buffer, char * filename)
{
	ofstream myfile;
	myfile.open (filename);
    myfile << buffer;
    myfile.close();
    return 0;	
}


