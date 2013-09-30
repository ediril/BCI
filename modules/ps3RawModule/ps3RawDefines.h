#ifndef __PS3_RAW_DEFINES_H__
#define __PS3_RAW_DEFINES_H__

#include "../../message_definitions/common_defs.h"
#include "ps3Defines.h"
#ifdef __cplusplus
extern "C" {
#endif



/* /\* button press *\/ */
/* #define PS3_B_L1 10 */
/* #define PS3_B_L2 8 */
/* #define PS3_B_R1 11 */
/* #define PS3_B_R2 9 */
/* #define PS3_B_LDIR 7 */
/* #define PS3_B_RDIR 5 */
/* #define PS3_B_UDIR 4 */
/* #define PS3_B_DDIR 6 */
/* #define PS3_B_TRIANGLE 12 */
/* #define PS3_B_SQUARE 15 */
/* #define PS3_B_CIRCLE 13 */
/* #define PS3_B_X 14 */
/* #define PS3_B_SELECT 0 */
/* #define PS3_B_START 3 */
/* #define PS3_B_L3 1 */
/* #define PS3_B_R3 2 */

/* /\* continuous *\/ */
/* #define PS3_C_LSTICKH 0 */
/* #define PS3_C_LSTICKV 1 */
/* #define PS3_C_RSTICKH 2 */
/* #define PS3_C_RSTICKV 3 */

/* #define PS3_C_L1 14 */
/* #define PS3_C_L2 12 */
/* #define PS3_C_R1 15 */
/* #define PS3_C_R2 13 */
/* #define PS3_C_LDIR 11 */
/* #define PS3_C_RDIR 9 */
/* #define PS3_C_UDIR 8 */
/* #define PS3_C_DDIR 10 */
/* #define PS3_C_TRIANGLE 16 */
/* #define PS3_C_SQUARE 19 */
/* #define PS3_C_CIRCLE 17 */
/* #define PS3_C_X 18 */


/*   /\* rotation *\/ */

/* #define PS3_C_ROLL 0 */
/* #define PS3_C_PITCH 1 */



/* #define PS3_N_SENSORS 21 */
/* #define PS3_N_ACCEL 2 */
/* #define BUTTON_PRESS  2135 */
/* #define BUTTON_RELEASE 2136 */
/* #define STICK_READING 2137 */
/* #define ACCEL_READING 2138 */



#define MAX_CONTROLLERS 10
  //#define DOF_SCALE  0.3;
  //#define JOINT_SCALE  0.3;


  typedef struct {
	//make sure you have an even number of total ints
	int buttonMask[PS3_N_SENSORS];
	int buttonVal[PS3_N_SENSORS];
	int continuousMask[PS3_N_SENSORS];
	int continuousVal[PS3_N_SENSORS];
	int accelMask[PS3_N_ACCEL];
	double accelVal[PS3_N_ACCEL];
	int controllerId;
	int spacer;
  } PS3_RAW_DATA;

  typedef struct {
    SAMPLE_HEADER sample_header;
    int controllerId;
    int spacer;
    double dof_vals[PS3_N_SENSORS];
  } PS3_GENERIC_DATA;

  typedef struct {
    int whichButton;
    int controllerId;
  } PS3_BUTTON_DATA;

  typedef struct {
	int stickCommandDOFMap[PS3_N_SENSORS];   // 19
	int stickCommandJointMap[PS3_N_SENSORS]; // 19
	char tag[TAG_LENGTH];                    // 64
	double stickScale[PS3_N_SENSORS];        // 19
	double stickOffset[PS3_N_SENSORS];       // 19
	double accelScale[PS3_N_ACCEL];          //  2
	double accelOffset[PS3_N_ACCEL];         //  2
	double DOFscale[MAX_CONTROL_DIMS];       // 13
	int accelDOFMap[PS3_N_ACCEL];            //  2
	int use_controller[MAX_CONTROLLERS];     // 10
	int free_run;                            //  1
	int spacer;
  } PS3_RAW_CONFIG;
  // not sure about spacer - remembering byte-packing issue, but not clear on details
  // have changed use_controller to array, and added free_run
  // whole thing must be a multiple of largest element - in this case 8 bytes for the doubles

typedef struct accel_state {
  int controllerId;
  int ax;
  int ay;
  int az;       // Raw accelerometer data
  double time;
  double ddx;
  double  ddy;
  double ddz; // Acceleration
  double dx;
  double dy;
  double dz;    // Speed
  double x;
  double y;
  double z;       // Position
  double roll;
  double pitch;
} PS3_ACCEL_DATA;


  typedef PS3_RAW_CONFIG MDF_PS3_RAW_CONFIG;
  typedef PS3_BUTTON_DATA MDF_PS3_SIMPLE_BUTTON_PRESS;
  typedef PS3_BUTTON_DATA MDF_PS3_SIMPLE_BUTTON_RELEASE;
  typedef PS3_GENERIC_DATA MDF_PS3_GENERIC_DATA;


#define MT_PS3_RAW_CONFIG 6543
#define MT_PS3_SIMPLE_BUTTON_PRESS 6544
#define MT_PS3_SIMPLE_BUTTON_RELEASE 6545
#define MT_PS3_GENERIC_DATA 6546

#ifdef __cplusplus
}
#endif

#endif
