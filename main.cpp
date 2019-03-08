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
bool live_hardware = false;
bool do_sound=true;



RadioControl Rig;

int main(int argc, char *argv[])
{
  char entrytime[40];

  time_t t;
  struct tm *tmp;
  int inttime;
  int intlastcheck;
  
    if(argc>1) 
    {
		do_sound=true;
//		strcpy(entrytime,argv[1]);
		inttime=atoi(argv[1]);
		ProcessFile(inttime);
        Playsound(inttime);  
        exit(0);
	}
  
    if(live_hardware) Rig.Initialise();


    while(1)
    {

      t = time(NULL);
      tmp = localtime(&t);
      strftime(entrytime,18,"%H%M",tmp);
      inttime = atoi(entrytime);

      if(inttime == intlastcheck)
      {
      // already checked this minute
      //       putchar('.');
        sleep(1);
        Say5Numbers();
      }
      else
      {
        // not done. do it
        printf("%4d Checking.\n",inttime);
        intlastcheck = inttime;


        ProcessFile(inttime);
        Playsound(inttime);            
        
        printf(".... Waiting for next time check\n");
      }     // end of 'if lastcheck'
   }  // end of main while
  return 0;
}
