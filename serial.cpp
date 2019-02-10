#include <sys/ioctl.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdio.h>
#include <hamlib/rig.h>
#include "serial.h"
#include "string.h"
#include <stdlib.h>
int fd;

#define SERIAL_PORT "/dev/ttyUSB0"
#define RIG_IC78 345

RIG *my_rig; /* handle to rig (instance) */

int RadioControl::Initialise(void)
{
  int retcode; /* generic return code from functions */
//  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
//  printf("Serial Port=%i is controlling PTT\r\n",fd);


  printf("setting up serial!\n");
  hamlib_port_t myport;
  myport.type.rig = RIG_PORT_SERIAL;
  myport.parm.serial.rate = 1200;
  myport.parm.serial.data_bits = 8;
  myport.parm.serial.stop_bits = 1;
  myport.parm.serial.parity = RIG_PARITY_NONE;
  myport.parm.serial.handshake = RIG_HANDSHAKE_NONE;
  strncpy(myport.pathname, SERIAL_PORT, FILPATHLEN - 1);
  rig_load_all_backends();

  my_rig = rig_init(RIG_IC78);
  if (!my_rig)
  {
    fprintf(stderr,"Unknown rig num: %d\n", RIG_IC78);
    fprintf(stderr,"Please check riglist.h\n");
    return 1; /* whoops! something went wrong (mem alloc?) */
  }

  strncpy(my_rig->state.rigport.pathname,SERIAL_PORT,FILPATHLEN - 1);
  retcode = rig_open(my_rig);
  if (retcode != RIG_OK)
  {
    printf("rig_open: error = %s\n", rigerror(retcode));
    return 2;
  }

  printf("Port %s opened ok\n", SERIAL_PORT);
  return 0;
}




int RadioControl::Close(void)
{
  rig_close(my_rig); /* close port */
  rig_cleanup(my_rig); /* if you care about memory */
  printf("port %s closed ok \n",SERIAL_PORT);
  return 0;
}


int RadioControl::Command( int command, char * value)
{
  double freq;
  int retcode; /* generic return code from functions */

  retcode = RIG_OK;

  if (command == RADIO_FREQ)
  {
    freq = atof(value)*1000000;
    printf("change frequency to [%f]\n",freq);
    retcode = rig_set_freq(my_rig, RIG_VFO_CURR, freq);
    retcode = rig_set_mode(my_rig, RIG_VFO_CURR, RIG_MODE_USB, RIG_PASSBAND_NORMAL);
  }

  if (command == RADIO_POWER)
  {

    printf("change power to [%f]\n",atof(value));
    retcode = rig_set_freq(my_rig, RIG_LEVEL_RFPOWER, atof(value));
    retcode = rig_set_mode(my_rig, RIG_VFO_CURR, RIG_MODE_USB, RIG_PASSBAND_NORMAL);
  }

  sleep(1);
  if (retcode != RIG_OK )
  {
    printf("rig_set_error %i = %s \n", retcode, rigerror(retcode));
  }
  return retcode;
}




int RadioControl::Transmit(void)
{
   int retcode;
   retcode = rig_set_ptt(my_rig, RIG_VFO_A, RIG_PTT_ON ); /* stand back ! */

   if (retcode != RIG_OK )
   {
     printf("rig_set_ptt: error = %s \n", rigerror(retcode));
   }

  return 0;
}

int RadioControl::Receive(void)
{
   int retcode;
   retcode = rig_set_ptt(my_rig, RIG_VFO_A, RIG_PTT_OFF ); /* safe now! */

   if (retcode != RIG_OK )
   {
     printf("rig_set_ptt: error = %s \n", rigerror(retcode));
   }

  return 0;
}



