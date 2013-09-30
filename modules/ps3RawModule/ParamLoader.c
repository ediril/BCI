#include <stdio.h>
#include <string.h>
#include "ParamLoader.h"
#include "RTMA_config.h"
#include "ps3RawDefines.h"

void ParamLoader(char *filename, PS3_RAW_CONFIG *params)
{
  static FILE *paramFile;
  static int index;
  static char buf[128];
  static int i, whichController;
  static int whichStick, val;
  static double scale, offset;

  for (index = 0; index < PS3_N_SENSORS; index++)
    {
      params->stickCommandDOFMap[index] = -1;
    }
  for (index = 0; index < PS3_N_SENSORS; index++)
    {
      params->stickCommandJointMap[index] = -1; 
    }
  
  paramFile = fopen(filename, "r");

  if (!paramFile) {
	fprintf(stderr, "bad param file %s!!\n", filename);
  }
  while(!feof(paramFile)) {
	fscanf(paramFile, "%s", buf);
	
	if(!strcmp(buf, "stick_dof_map")) {
	  fscanf(paramFile, "%d %d %lf %lf", &whichStick, &val, &scale, &offset); 
	  params->stickCommandDOFMap[whichStick] = val;
	  params->stickScale[whichStick] = scale;
	  params->stickOffset[whichStick] = offset;
	}
	if(!strcmp(buf, "stick_joint_map")) {
	  fscanf(paramFile, "%d %d %lf %lf" , &whichStick, &val, &scale, &offset);
	  params->stickCommandJointMap[whichStick] = val;
	  params->stickScale[whichStick] = scale;
	  params->stickOffset[whichStick] = offset;
	}
	if(!strcmp(buf, "inertial_dof_map")) {
	  fscanf(paramFile, "%d %d %lf %lf", &whichStick, &val, &scale, &offset); 		  
	  params->accelDOFMap[whichStick] = val;
	  params->accelScale[whichStick] = scale;
	  params->accelOffset[whichStick] = offset;
	}
	if(!strcmp(buf, "use_controller")) {
	  fscanf(paramFile, "%d", &whichController);
	  params->use_controller[whichController] = 1;
	}
	if(!strcmp(buf,"dof_scale")) {
	  fscanf(paramFile, "%d  %d %lf", &whichStick, &val, &scale);
	  for(i=whichStick;i<=val;i++) {
		params->DOFscale[i] = scale;
	  }	  
	}
	if(!strcmp(buf, "tag")) {
	  fscanf(paramFile, "%s", &params->tag);
	}
	if(!strcmp(buf, "free_run")) {
	  fscanf(paramFile, "%d", &params->free_run);
	}
  }
  fclose(paramFile);
}
