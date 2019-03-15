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
int PlayFile(string filename);

int PlayFile(string filename)
{
	char buffer[100];
	sprintf(buffer, "aplay -q %s",(char*)filename.c_str());
 	if(do_sound) system(buffer);
	return 0;
}



int Say (char * inbuffer)
{ // say a phrase that we dont have prepared as a wav.
	char buffer[2000];
	sprintf(buffer, "echo \"%s\" |pico2wave -l=\"en-GB\" -wtemp.wav",inbuffer);
//	cout << buffer << endl; 
	system(buffer);
    PlayFile("temp.wav");	
	return 0;
}


int Say5Numbers(void)// say a random 5 number sequence, 
{
	char buffer[200];
	char rbuffer[20];
	int i;
	
	for( i = 0; i<5; i++)
	{
      rbuffer[i] = rand()%10;
      rbuffer[i] +=48;
    }
	
	sprintf(buffer,"sox resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/silence_1.wav temp.wav", 
	               rbuffer[0],rbuffer[1],rbuffer[2],rbuffer[3],rbuffer[4]);
	system(buffer);
	PlayFile("temp.wav");
	return 0;
}



int SayPower(void)
{
	char buffer[200];
	sprintf(buffer,"sox resources/p.wav resources/%c.wav resources/%c.wav resources/silence_1.wav temp.wav", power[0],power[1]);
	system(buffer);	
	PlayFile("temp.wav");
 return 0;
}




int SayTime(void)   // create a wav of the current time.
{                        // this is low quality voice
	// get current time
	// convert to wav
	struct tm * mytime;
	time_t mysecs;
	char buffer[200];
	
	mysecs = time(NULL);
	mytime = gmtime(&mysecs);
	sprintf(buffer, "echo \"%2d %02d and %2d seconds\" |pico2wave -l=\"en-GB\" -wtemp.wav",mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
	system(buffer);	
	PlayFile("temp.wav");
 return 0;
}



int SayAsGroups(char * inbuffer)  // take a variable length string of letters and say as phonetics in groups of 5
{                                 // padded with z
	// get current time
	// convert to wav
	char buffer[200];
	int len;
	int i;
	
	for(int i = 0; inbuffer[i]; i++)
	{
      inbuffer[i] = tolower(inbuffer[i]);
	  if(inbuffer[i]<'a') inbuffer[i]='a';
	  if(inbuffer[i]>'z') inbuffer[i]='z';
	  
    }
	
	len = strlen(inbuffer);
	strcat(inbuffer,"zzzzz");
	for (i=0;i<len;i+=5)
	{
		strncpy(buffer,&inbuffer[i],5);
		sprintf(buffer,"sox resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/silence_1.wav temp.wav", buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
		system(buffer);
		PlayFile("temp.wav");
	}	
 return 0;
}





int SayDTG(void) // makes a standard 6 number DTG wav file in the good voice.
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
	sprintf(buffer,"sox resources/timeis.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/%c.wav resources/silence_1.wav temp.wav", tbuffer[0],tbuffer[1],tbuffer[2],tbuffer[3],tbuffer[4],tbuffer[5]);
	system(buffer);
	PlayFile("temp.wav");
 return 0;
}



int ProcessLine(char * line)  // process the line of script passed in
{
	char localbuffer[2100];
    strncpy(localbuffer,&line[1],2000);	
	
	switch (line[0])
	{
		case 'C':
		  cout << "---- Saying Callsign" << endl; 
	      PlayFile("wavs/callsign.wav");
		  break;

		case 'D':
		  cout << "---- Saying DTG" << endl; 
		  SayDTG();
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

		case 'N':
		  if( strcmp(localbuffer,"on")==0)
		  {
			  // if "Non" enable numbers anything else turns it off
		      cout << "---- Setting Number Mode ON" << endl; 
			  saynumbers=true;
		  }
		  else
		  {
			  saynumbers=false;			  
		      cout << "---- Setting Number Mode ON" << endl; 
		  }
		  break;

	  
		case 'P':
		  strncpy(power,localbuffer,4);
		  cout << "---- Changing Power "; 
		  cout << localbuffer << endl;
		  
          if(live_hardware)   Rig.Command( RADIO_POWER, localbuffer);
		  break;

		case 'R':
		  cout << "---- Reporting Power" << endl; 
		  SayPower();
		  break;

		case 'S':
		  cout << "---- Saying Text" << endl; 
		  Say(localbuffer);
		  break;


		case 'T':
		  cout << "---- Saying Time" << endl; 
		  SayTime();
		  break;


		  
		default:
		  cout << "Letter not recognised\n"; 
		  break;
		
	}
	return 0;
}










int ProcessScript(char * filename) // read a script file , base on time input, 
{                                  // and send each line for processing
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



int ProcessFile(int entrytime)  // check to see if script exists and send for processing
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

 


int Playsound(int entrytime) // check for sound existing and play if it does.
{
  char filename[20];
  char commandbuffer[100];

  sprintf(filename,"wavs/%04d.wav",entrytime);

  if (fileExists(filename))
  {
	sprintf(commandbuffer,"aplay -q %04d.wav",entrytime);
	printf("%04d Playing\[%s]\n",entrytime,commandbuffer);	

	if(do_sound) system(commandbuffer);
	
  }
  else
  {
	printf("%04d No specific sound to play\n",entrytime);
	sprintf(filename,"wavs/24%02d.wav",entrytime%60);  
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



