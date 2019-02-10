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

int Playsound(int entrytime)
{
  char filename[20];
  char commandbuffer[100];
  struct stat buf;
  char played =0;
  stat("file",&buf);

  sprintf(filename,"%4d.wav",entrytime);

  if (fileExists(filename))
  {
	printf("%4d Playing\n",entrytime);	
	sprintf(commandbuffer,"aplay -q %4d.wav",entrytime);
	system(commandbuffer);
	played =1;
  }
  else
  {
	printf("%4d No specific sound to play\n",entrytime);	  
  }
  
  if(played ==0) // if no specific message check for hourly repeating
  {
	sprintf(filename,"24%2d.wav",entrytime%60);  
	if (fileExists(filename))
	{
		printf("%s Playing hourly\n",filename);	
	    sprintf(commandbuffer,"aplay -q %s",filename);
	    system(commandbuffer);		
	}
	else
	{
		printf("%s No hourly sound to play\n",filename);	  
	}
  }

  
  return 0;  
}

bool fileExists(const char* file) {
    struct stat buf;
    return (stat(file, &buf) == 0);
}




int ProcessFile(int entrytime)
{
  printf("%4d Running commands\n",entrytime);
// read file [time].txt
// if doesnt exist read [24time].txt
// split file into lines

// loop while still lines
// process lines

  
  
  
  
  return 0;
}

 

/*
 *   char * strend;
  char localbuffer[10000];

  strcpy(localbuffer,buffer);
  char letter;
  int a;
  int limit;

  attron(COLOR_PAIR(1));

  switch(localbuffer[0])
  {
    case '(':
      // base32
//      bigbuffer[0]=0;
//     Base32String(bigbuffer, &localbuffer[1]);
//      Speak.Phonetic(bigbuffer,1);
    break;



    case ']':
      // random numbers
      // ]12
//      printf("Setting numbers string\n");
      localbuffer[0]=0;
      limit = atoi(&localbuffer[1]);
      for(a=0;a< limit;a++)
      {
        letter = (rand()%10)+48;
        localbuffer[a]=letter;
//        localbuffer[a+2]=0;
//      printf("numbers %s\n",localbuffer);
      }
      localbuffer[a]=0;
      Speak.Phonetic(localbuffer,0);
    break;


    case '}':
      // random phonetics
      // }10
      limit = atoi(&localbuffer[1]);
      for(a=0;a< limit;a++)
      {
        letter = (rand()%26)+65;
        localbuffer[a]=letter;
      }
      localbuffer[a]=0;
      Speak.Phonetic(localbuffer,1);
    break;

    case '{':
    // say in phonetics
    // {MRC18
      Speak.Phonetic( &localbuffer[1],0);
    break;

    case ';':
    //change frequency
    // ;5.245
      strend = strstr(localbuffer," ");
      if (strend ) strend[0]=0;   // null the string end
      Rig.Command( RADIO_FREQ, &localbuffer[1]);
      break;

    case '[':
    // change power
    // [50
      strend = strstr(localbuffer," ");
      if (strend ) strend[0]=0;   // null the string end
      Rig.Command( RADIO_POWER, &localbuffer[1]);
      break;

    case ':':
    // say the callsign and time.
    // :
      strftime(hour,18,"%H hours",tmp);
      strcpy(localbuffer,callsign);
      if( atoi(hour) < 10) strcat(localbuffer," Zero ");
      strcat(localbuffer,hour);
//      printf("[%s]\n",localbuffer);
      Speak.Message(localbuffer);
      break;

    default:
//      printf("default <[%s]>\n",localbuffer);
      Speak.Message(localbuffer);
      break;
  }
    // end of switch


   return 0;
}  // end of if process

*/
