#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "math.h"
#include "ps3RawDefines.h"
#include "RTMA_config.h"
#include "jsfunc.h"
#include "ParamLoader.h"
#ifdef USERTMA
#include "RTMAThread.h"
#endif

static PS3_RAW_CONFIG config;
static int lastValues[MAX_CONTROLLERS][PS3_N_SENSORS];
int keep_going = 1;
INPUT_DOF_DATA dofData[MAX_CONTROLLERS];
int hasJoysticks[MAX_CONTROLLERS];

#ifdef USERTMA
extern pthread_mutex_t data_mutex;
#endif

int main(int argc, char *argv[])
{
  int i;
  int dataReceived;
  char devstring[1023]; // = "/dev/ps3CtrRed";
  char devstrings[MAX_CONTROLLERS][512] = {"/dev/ps3CtrBlack", "/dev/ps3CtrBlue"};
  char accelstring[] = "/dev/input/hidraw0";
#ifdef USERTMA
  pthread_t rtma_thread;
#endif
  PS3_RAW_DATA data;

  //
  // Process command line arguments to require config filename
  // and to check for optional MessageManager IP
  //
  if( argc < 2) {
	printf("Missing config file command-line argument!\n");
	return -1;
  }
  char *config_path = argv[1];
  char *mm_ip = NULL;
  if( argc > 2) {
	mm_ip = argv[2];
  }

  printf("Loading config file: %s\n", config_path);
  ParamLoader(config_path, &config);

  printf("%d\n", PS3_N_SENSORS);
  fflush(stdout);

  for(i = 0; i < MAX_CONTROLLERS; i++) {
	memset(lastValues[MAX_CONTROLLERS], 0, PS3_N_SENSORS * sizeof(int));
  }

  for (i = 0; i < MAX_CONTROLLERS; i++) {
	hasJoysticks[i] = 0;
  }

  for(i = 0; i < MAX_CONTROLLERS; i++) {
	printf("%d -> %d\n", i, config.use_controller[i]);
	if (config.use_controller[i] != 1) {
	  printf("Not using joystick %d.\n", i);
	  continue;
	}

	sprintf(devstring, devstrings[i]);
	printf("Searching for joystick %d at %s...", i, devstring);
	//sprintf(accelstring, "/dev/ps3Draw%1d", i);

	if(InitJoystick(devstring,i) < 0) {
	  // no joystick i found at devstring
	  fprintf(stdout, "  not found.\n");
	  hasJoysticks[i] = 0;
	} else {
	  // found joystick i at devstring
	  fprintf(stdout, " found.\n");
	  if(config.use_controller[i] == 1) {
		hasJoysticks[i] = 1;
		printf("(using it)\n");

		if(InitAccel(accelstring, i) < 0) {
		  fprintf(stdout, "  Acceleration not working.\n");
		} else {
		  fprintf(stdout, "  Acceleration working.\n");
		}
	  }
	}
  }

  for(i = 0; i < MAX_CONTROLLERS; i++) {
	memset((char *) &dofData[i], 0, sizeof(INPUT_DOF_DATA));
	sprintf(dofData[i].tag, "ps3_%d", i);
	// fprintf(stdout, "tag %s\n", dofData[i].tag);
  }

#ifdef USERTMA
  THREAD_CONFIG_STRUCT threadConfig;
  threadConfig.ps3_config = &config;
  threadConfig.mm_ip = mm_ip;
  pthread_create(&rtma_thread, NULL, RTMA_Thread, (void *) &threadConfig);
#endif

  // initialize dofData `data.controllerId`s
  while (keep_going) {
	dataReceived = 0;

	if((dataReceived = StreamController(&data, hasJoysticks)) < 0) {
	  perror("stream controller");
	}

	if (dataReceived == STICK_READING) {
#ifdef USERTMA
	  pthread_mutex_lock( &data_mutex );
#endif

	  for (i = 0; i < PS3_N_SENSORS; i++) {
		if (lastValues[data.controllerId][i] != data.continuousVal[i])	{
		  lastValues[data.controllerId][i] = data.continuousVal[i];
	          if (config.stickCommandDOFMap[i] >= 0) {
		     dofData[data.controllerId].dof_vals[config.stickCommandDOFMap[i]] =
		     ((((double) data.continuousVal[i]) + config.stickOffset[i]) / config.stickScale[i]);
                  }
		}
	  }
	  for (i = 0; i < PS3_N_ACCEL; i++) {
		if (data.accelMask[i])	{
		  dofData[data.controllerId].dof_vals[config.accelDOFMap[i]] =
			((data.accelVal[i] + config.accelOffset[i]) / config.accelScale[i]);
		  //movementCommand.vel[config.accelDOFMap[i]] =
		  //((data.accelVal[i] + config.accelOffset[i]) / config.accelScale[i]) *
		  //config.DOFscale[config.accelDOFMap[i]];
		}
	  }
#ifdef USERTMA
	  pthread_mutex_unlock( &data_mutex );
#endif

	  //printf("* %5.2f\n", dofData[0].dof_vals[0]);

/*	  printf("%5.2lf %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf\n",
			 dofData[data.controllerId].dof_vals[0],
			 dofData[data.controllerId].dof_vals[1],
			 dofData[data.controllerId].dof_vals[2],
			 dofData[data.controllerId].dof_vals[3],
			 dofData[data.controllerId].dof_vals[12],
			 dofData[data.controllerId].dof_vals[13],
			 dofData[data.controllerId].dof_vals[14],
			 dofData[data.controllerId].dof_vals[15]);*/
	}
  }
}
