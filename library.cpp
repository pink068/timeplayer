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

using namespace std;
int ProcessScript(char * filename);
int ProcessLine(string line);
extern bool live_hardware ;
extern bool do_sound;
extern RadioControl Rig;

int ProcessLine(string line)
{
	char localbuffer[20];
	line.copy(localbuffer,18,1);	
	
	switch (line.front())
	{
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

		case 'C':
		  cout << "---- Saying Callsign" << endl; 
	      if(live_hardware) system("aplay callsign.wav");
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
	  ProcessLine(line);
      
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
	return 0;
	
}



int ProcessFile(int entrytime)
{
  char filename[20];
  printf("%4d Running commands\n",entrytime);

  sprintf(filename,"%4d.txt",entrytime);
  strcpy(filename,"2359.txt");
  if (fileExists(filename))
  {  
	ProcessScript(filename);
  }
  else
  {
    printf("%4d No specific to process\n",entrytime);
    sprintf(filename,"24%2d.txt",entrytime%60);  
    if (fileExists(filename))
    {  
	  ProcessScript(filename);
    }
    else
    {
      printf("%4d No hourly to process\n",entrytime);	  
    }  
  }
  
  return 0;
}

 


int Playsound(int entrytime)
{
  char filename[20];
  char commandbuffer[100];

  sprintf(filename,"%4d.wav",entrytime);

  if (fileExists(filename))
  {
	sprintf(commandbuffer,"aplay -q %4d.wav",entrytime);
	printf("%4d Playing\[%s]\n",entrytime,commandbuffer);	

	if(do_sound) system(commandbuffer);
	
  }
  else
  {
	printf("%4d No specific sound to play\n",entrytime);
	sprintf(filename,"24%2d.wav",entrytime%60);  
	if (fileExists(filename))
	{
	  sprintf(commandbuffer,"aplay -q %s",filename);
      printf("%4d Playing hourly [%s]\n",entrytime,commandbuffer );	

      if(do_sound) system(commandbuffer);		
	  
	}  // end of if exists
  }   // end of else

  return 0;  
}

bool fileExists(const char* file) {
    struct stat buf;
    return (stat(file, &buf) == 0);
}

