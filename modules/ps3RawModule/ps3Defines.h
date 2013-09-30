#ifndef __PS3_DEFINES_H__
#define __PS3_DEFINES_H__

#include "../../message_definitions/common_defs.h"
#ifdef __cplusplus
extern "C" {
#endif

/* button press */
#define PS3_B_L1 10
#define PS3_B_L2 8
#define PS3_B_R1 11
#define PS3_B_R2 9
#define PS3_B_LDIR 7
#define PS3_B_RDIR 5
#define PS3_B_UDIR 4
#define PS3_B_DDIR 6
#define PS3_B_TRIANGLE 12
#define PS3_B_SQUARE 15
#define PS3_B_CIRCLE 13
#define PS3_B_X 14
#define PS3_B_SELECT 0
#define PS3_B_START 3
#define PS3_B_L3 1
#define PS3_B_R3 2

/* continuous */
#define PS3_C_LSTICKH 0
#define PS3_C_LSTICKV 1
#define PS3_C_RSTICKH 2
#define PS3_C_RSTICKV 3

#define PS3_C_L1 14
#define PS3_C_L2 12
#define PS3_C_R1 15
#define PS3_C_R2 13
#define PS3_C_LDIR 11
#define PS3_C_RDIR 9
#define PS3_C_UDIR 8
#define PS3_C_DDIR 10
#define PS3_C_TRIANGLE 16
#define PS3_C_SQUARE 19
#define PS3_C_CIRCLE 17
#define PS3_C_X 18


#define PS3_N_SENSORS 21
#define PS3_N_ACCEL 2
#define BUTTON_PRESS  2135
#define BUTTON_RELEASE 2136
#define STICK_READING 2137

#define MT_PS3_BUTTON_PRESS BUTTON_PRESS
#define MT_PS3_BUTTON_RELEASE BUTTON_RELEASE
#define MT_PS3_STICK_READING STICK_READING

#define DOF_SCALE  0.3;
#define JOINT_SCALE  0.3;


typedef struct {
  int whichButton;
  int val;
  int controllerId;
  int buttonMask[PS3_N_SENSORS];
  int buttonVal[PS3_N_SENSORS];
  int continuousMask[PS3_N_SENSORS];
  int continuousVal[PS3_N_SENSORS];
  int accelMask[PS3_N_ACCEL];
  int spacer;
  double accelVal[PS3_N_ACCEL];
} PS3_DATA;

typedef struct {
  int stickCommandDOFMap[PS3_N_SENSORS];
  int stickCommandJointMap[PS3_N_SENSORS];
  double stickScale[PS3_N_SENSORS];
  double stickOffset[PS3_N_SENSORS];
  int use_controller;
  int use_label_controller;
} PS3_CONFIG;

  typedef PS3_DATA MDF_PS3_BUTTON_PRESS;
typedef PS3_DATA MDF_PS3_BUTTON_RELEASE;

#ifdef __cplusplus
}
#endif


#endif
