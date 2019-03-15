#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "serial.h"
#include "library.h"

using namespace std;
bool live_hardware = false; // true if we have a radio connected
bool do_sound=true;         // true if we have a sound card connected
bool saynumbers=false;      // true if numbers time filler is requested by a script command
bool station_heard=false;   // set true by reciever thread to tell main that another station was heard
char power[6];              // text buffer for tx power reporting

RadioControl Rig;			// structire to hold the hamlib comms struct

int main(int argc, char *argv[])
{
  char entrytime[40];

  time_t t;
  struct tm *tmp;
  int inttime;
  int intlastcheck;
  int counter;
  counter =0;
  
    if(argc>1) 		// if we entered a tme manually it must be a test
    {
		do_sound=true;
		inttime=atoi(argv[1]);
		ProcessFile(inttime);
        Playsound(inttime);  
        exit(0);
	}
  
   
    if(live_hardware)  // if we have hardware, initialise it, otherwise ignore
    {
		Rig.Initialise();
	}

	ProcessFile(2500); // set the power up defaults
    while(1)
    {

      t = time(NULL);		// get the sysyetm time
      tmp = localtime(&t);  // put it into a usable struct
      strftime(entrytime,18,"%H%M",tmp);// make it a short string EG 1345
      inttime = atoi(entrytime);  // make it an int 

	  if( station_heard)  
	  {
		  // if someone spoke then go quiet for a minute
		counter = -55; // -55 because numbers happen at 5 seconds, so -55 = 1 minute
	  }
	  
      if(inttime == intlastcheck)
      {
      // already checked this minute
        sleep(1); // wait a second
        counter++;   // count up by 1
//		cout << counter <<":" <<saynumbers <<endl;
        if(saynumbers==true && counter >4) // if 5 seconds passed then say a numbers group, if rquired.
        {

			Say5Numbers();
			counter =0;
		}

      }
      else
      {
        // not done. do it
        printf("%4d Checking.\n",inttime); // if the minute has changed log it.
        intlastcheck = inttime;


        ProcessFile(inttime); // see if we have a script to run
        Playsound(inttime);   // see if we have a wav file to play
        
        printf(".... Waiting for next time check\n");
      }     // end of 'if lastcheck'
   }  // end of main while
  return 0;
}
