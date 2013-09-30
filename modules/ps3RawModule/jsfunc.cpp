#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include "ps3RawDefines.h"
#ifdef USERTMA
#include "RTMAThread.h"
#endif

static int fd[10];
static int inertialfd[10];
#define NAME_LENGTH 128

int
timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
       }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
  
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
  
  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

int InitJoystick(char *dev, int id)
{
  unsigned char axes = 2;
  unsigned char buttons = 2;
  char name[NAME_LENGTH] = "Unknown";
  uint16_t btnmap[KEY_MAX - BTN_MISC + 1];
  uint8_t axmap[ABS_MAX + 1];
  //  int version = 0x000800;

  if ((fd[id] = open(dev, O_RDONLY)) < 0) { 
    return -1;
  }

  //  ioctl(fd, JSIOCGVERSION, &version);
  ioctl(fd[id], JSIOCGAXES, &axes);
  ioctl(fd[id], JSIOCGBUTTONS, &buttons);
  ioctl(fd[id], JSIOCGNAME(NAME_LENGTH), name);
  ioctl(fd[id], JSIOCGAXMAP, axmap);
  ioctl(fd[id], JSIOCGBTNMAP, btnmap);

  return(1);
}

int InitAccel(char *dev, int id)
{
  if ((inertialfd[id] = open(dev, O_RDONLY)) < 0) {
    return -1;
  }
  return(1);
}

int StreamController(PS3_RAW_DATA *data, int *whichJoysticks)
{    
  static struct js_event js;
  PS3_ACCEL_DATA prev;
  static struct timeval tv;
  static fd_set set;
  static int retval;
  static int thisRetval;
  static int offset;
  static int ret;
  static struct timeval end;
  //static struct timeval lastReadTime[PS3_N_SENSORS];
  static struct timeval lastSentTime;
  static struct timeval elTime;
  static int first = 1;
  static int i ;
  static int maxfd;
  static char buf[64];
  static double lastPitch = 0.0, lastRoll = 0.0;
  static PS3_RAW_DATA *curStickData;
  static PS3_ACCEL_DATA accelData;
  static PS3_BUTTON_DATA buttonData;
  static int messageTimeout;

  curStickData = data;
  if (first) {
	first = 0;
	memset(&prev, 0, sizeof(PS3_ACCEL_DATA));
	memset(curStickData, 0, sizeof(PS3_RAW_DATA));		    
	gettimeofday(&lastSentTime, NULL);
  }
  
  thisRetval = 0;
  messageTimeout = 0;
  FD_ZERO(&set);
  for (i = 0; i < MAX_CONTROLLERS; i++) {
	if (whichJoysticks[i]) {
	  FD_SET(fd[i], &set);

	  // need to fix inertial stuff - some system module to be loaded?
	  // in the meantime, this is a workaround to get running - AJCM
	  //FD_SET(inertialfd[i], &set);
	  //maxfd = (inertialfd[i] > fd[i] ? inertialfd[i] : fd[i]);
	  maxfd = fd[i];
	  // end this bit of workaround, but see below for more
	}
  }
  tv.tv_sec = 0;
  tv.tv_usec = 30000;
        
  if ((retval = select(maxfd + 1, &set, NULL, NULL, &tv))) {
	  
	if(retval < 0) {
	  fprintf(stderr, "select returned error\n");
	  exit(1);
	}
	
	gettimeofday(&end, NULL);
  
	timeval_subtract(&elTime, &end, &lastSentTime);
	if(elTime.tv_sec > 0 || elTime.tv_usec >= 30000) {
	  messageTimeout = 1;
	  gettimeofday(&lastSentTime, NULL);
	}
	  
	for(i = 0; i < MAX_CONTROLLERS; i++) {
	  if(whichJoysticks[i]) {

		if(FD_ISSET(fd[i], &set)) {
		  if((ret = read(fd[i], &js, sizeof(struct js_event)))) {
			if(ret != sizeof(struct js_event)) {
			  if(ret == 0) {
				break;
			  } else {
				printf("error reading\n");
				return(-1);
			  }
			}
			curStickData->controllerId = i;
			if(js.type == 2) {
#ifdef TESTING
			  //printf("stick %d %d %d\n", js.number, js.value, abs(js.value));
#endif
			  curStickData->continuousMask[js.number] = 1;
			  curStickData->continuousVal[js.number] = js.value;
			  thisRetval = STICK_READING;
			}
//  else if (js.type == 1 && js.value == 1) {
// 			  data->buttonMask[js.number] = 1;
// 			  data->buttonVal[js.number] = 1;
				
// 			  buttonData.whichButton = js.number;
// 			  buttonData.controllerId = data->controllerId;
// 			  /* This should be a callback-like structure, but no time for that.  Sorry that this isn't particularly well designed.   -sam */
// #ifdef USERTMA
// 			  SendPS3Message(MT_PS3_SIMPLE_BUTTON_PRESS, (char *) &buttonData, sizeof(MDF_PS3_SIMPLE_BUTTON_PRESS));
// #endif
// 			  thisRetval = BUTTON_PRESS;
// 			} else if (js.type == 1 && js.value ==0) {
// 			  data->buttonMask[js.number] = 1;
// 			  data->buttonVal[js.number] = 0;
				
// 			  buttonData.whichButton = js.number;
// 			  buttonData.controllerId = data->controllerId;
// #ifdef USERTMA
// 			  SendPS3Message(MT_PS3_SIMPLE_BUTTON_RELEASE, (char *) &buttonData, sizeof(MDF_PS3_SIMPLE_BUTTON_PRESS));
// #endif
// 			  thisRetval = BUTTON_RELEASE;
// 			}
		  }
		}		  
		//MULT STICKS data++;		    	    
	  }
	}
	return(thisRetval);
  } else {
	messageTimeout = 1;
	gettimeofday(&lastSentTime, NULL);
  }
  return(messageTimeout);
}
    

		// // continue workaround
		// // if(FD_ISSET(inertialfd[i], &set)) {
		// if (0) {
		//   // end workaround

		//   int nr;
		//   if((nr = read(inertialfd[i], buf, sizeof(buf)))) {
		// 	if(nr<0) {
		// 	  perror("error reading accels");
		// 	}
		// 	if( nr != 50) {
		// 	  fprintf(stderr, "bad return length %d.\n", nr);
		// 	  //			    exit(-1);
		// 	}
		// 	if(nr == 0) {
		// 	  fprintf(stderr, "accel disconnected controller %d\n", i );
		// 	  exit(1);
		// 	}
			
		// 	curStickData->controllerId = i;
			
		// 	if ( gettimeofday(&tv, NULL) ) {
		// 	  perror("gettimeofday");
		// 	}
		// 	accelData.time = tv.tv_sec + tv.tv_usec*1e-6;
		// 	accelData.ax = buf[41+offset]<<8 | buf[42+offset];
		// 	accelData.ay = buf[43+offset]<<8 | buf[44+offset];
		// 	accelData.az = buf[45+offset]<<8 | buf[46+offset];
		// 	if ( ! prev.time ) {
		// 	  prev.time = accelData.time;
		// 	  prev.ax = accelData.ax;
		// 	  prev.ay = accelData.ay;
		// 	  prev.az = accelData.az;
		// 	}
		// 	double dt = accelData.time - prev.time;
		// 	double rc_dd = 2.0;  // Time constant for highpass filter on acceleration
		// 	double alpha_dd = rc_dd / (rc_dd+dt);
		// 	accelData.ddx = alpha_dd*(prev.ddx + (accelData.ax-prev.ax)*0.01);
		// 	accelData.ddy = alpha_dd*(prev.ddy + (accelData.ay-prev.ay)*0.01);
		// 	accelData.ddz = alpha_dd*(prev.ddz - (accelData.az-prev.az)*0.01);
		// 	double rc_d = 2.0;  // Time constant for highpass filter on speed
		// 	double alpha_d = rc_d / (rc_d+dt);
		// 	accelData.dx = alpha_d*(prev.dx + accelData.ddx*dt);
		// 	accelData.dy = alpha_d*(prev.dy + accelData.ddy*dt);
		// 	accelData.dz = alpha_d*(prev.dz + accelData.ddz*dt);
		// 	double rc = 1.0;  // Time constant for highpass filter on position
		// 	double alpha = rc / (rc+dt);
		// 	accelData.x = alpha*(prev.x + accelData.dx*dt);
		// 	accelData.y = alpha*(prev.y + accelData.dy*dt);
		// 	accelData.z = alpha*(prev.z + accelData.dz*dt);
			
		// 	int a0 = 512;
		// 	accelData.pitch = atan2(accelData.ax - a0, accelData.az - a0) + 1.5708;
		// 	double azx = hypot(accelData.ax - a0, accelData.az - a0);
		// 	accelData.roll = -atan2(accelData.ay - a0, azx);
			

		// 	if(fabs(accelData.pitch  - lastPitch) > 0.03 || fabs(accelData.roll - lastRoll) > 0.03) {
			    
		// 	  curStickData->accelMask[0] = 1;
		// 	  curStickData->accelVal[0] = accelData.roll;
		// 	  curStickData->accelMask[1] = 1;
		// 	  curStickData->accelVal[1] = accelData.pitch;
		// 	  thisRetval = STICK_READING;
		// 	  prev = accelData;
		// 	  lastPitch = accelData.pitch;
		// 	  lastRoll = accelData.roll;
			    
		// 	  //   printf("%f %f %f \n", dt, curStickData->accelVal[0], curStickData->accelVal[1]);
		// 	}
		//   }  
		// }
