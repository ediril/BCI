

// RTMA configuation file. Lists specific module-, message- and host- ID-s
// that are used by the real-time application components.
//
// Message type ID-s below 100 are reserved for RTMA system use.
// (These include things like CONNECT, DISCONNECT, SUBSCRIBE, UNSUBSCRIBE etc.)
//
// Message type-ID names start with MT_
//
//
// Module ID-s below 10 are reserved for RTMA system.
// (These include the Message Manager (Module 0), Network Relay Module (Module 1),
//  Application Manager (Module 2), Command Module (Module 3), and maybe others
//  in the future)
//
// Module ID names start with MID_
//
// Host ID-s 0 and 0x7FFF (32767) are reserved.
// (0 means "local host" and 0x7FFF means "all hosts")
//
// Host ID names start with HID_

#ifndef __RTMA_CONFIG_H_
#define __RTMA_CONFIG_H_

/////////////////////////////////////////////////////////////////////////////////
//                       Host ID-s (start from 1)
/////////////////////////////////////////////////////////////////////////////////
#define HID_MAIN_HOST   1

/////////////////////////////////////////////////////////////////////////////////
//         Module ID-s (start from 10) - Make sure to look in RTMA_common_config to avoid conflicts
/////////////////////////////////////////////////////////////////////////////////
#define MID_EXEC_MOD         10 // Executive module
//#define MID_GUI_MOD          11 // GUI module
#define MID_SPM_MOD          20 // Spike Processing Module
#define MID_SPM_MOD1         21 // Raw Spike Processing Module 1
#define MID_SPM_MOD2         22 // Raw Spike Processing Module 2
#define MID_SPM_MOD3         23 // Raw Spike Processing Module 3
#define MID_SPM_MOD4         24 // Raw Spike Processing Module 4

#define MID_IO_MOD           60 // I/O module
#define MID_DENSO_MOD        80 // DENSO Robot module
#define MID_DENSO_TRY        81 // DENSO Robot module
#define MID_WATCHDOG         97 // Watchdog module that tracks system delay and
#define MID_SILICON_MONKEY   72
#define MID_WAM              73
#define MID_OPTOTRAK         74
#define MID_SIMPLE_PLANNER 76

#define MID_EXTRACTION_MOD   50 // Extraction module

#define MID_VIZ              85
#define MID_HANDY_DANDY      86
#define MID_DRIFTY           93
#define MID_THE_DECIDER      94
#define MID_PS3_COMMAND_MODULE 95
#define MID_PS3_RAW_MODULE   96
#define MID_SILICON_MONKEY_BRAIN 91
#define MID_PS3_MODULE       92
#define MID_TEST_MOD		 99 // Testing module

/////////////////////////////////////////////////////////////////
// Common definitions
#include "common_defs.h"

typedef char STRING_DATA[];

#define MAX_FILENAME_LENGTH    256


// Includes to get type ID-s of modules that do not define them in this file
#include "modules.h"
#include "bci_config.h"

/////////////////////////////////////////////////////////////////////////////////
//                       Message type ID-s (start from 100)
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//        --> EXEC MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_XM_ABORT_SESSION         171

#define MT_PROCEED_TO_Failure             196
#define MT_PROCEED_TO_NextState        198

#define MT_PAUSE_EXPERIMENT 180
#define MT_RESUME_EXPERIMENT 181

/////////////////////////////////////////////////////////////////////////////////
//        <-- EXEC MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_TRIAL_EVENT                  100
//typedef TRIAL_EVENT MDF_TRIAL_EVENT;
typedef struct {
  double event_time; // RTMA AbsTime when event occurred
  int event_code;    // One of the TE_ codes below
  int reserved;
} MDF_TRIAL_EVENT;

#define MT_TRIAL_CONFIG                 101
typedef struct {
	int rep_no;      // Repetition number, starting at 1
	int trial_no;    // Trial number, starting at 1
	int num_reward_states;
	int reserved;
} MDF_TRIAL_CONFIG;

#define MT_TRIAL_STATUS                 102
typedef struct {
	int success;     // 0 = failure, 1 = success
	int reserved;
} MDF_TRIAL_STATUS;


/////////////////////////////////////////////////////////////////////////////////
// >-< EXEC MODULE (Messages that are generated internally in XM by the EventHook)
/////////////////////////////////////////////////////////////////////////////////
#define MT_WASHING_WITH_MONKEYS     133


/////////////////////////////////////////////////////////////////////////////////
//        --> GUI MODULE
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//        <-- GUI MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_LICKING_BEGIN       150
#define MT_LICKING_END         151


/////////////////////////////////////////////////////////////////////////////////
//        <-- ROBOT_CONTROL
/////////////////////////////////////////////////////////////////////////////////
#define MT_ROBOT_ACTUAL_STATE 934
#define MT_ROBOT_CONTROL_STATE 935
#define MT_ROBOT_CONTROL_SPACE_ACTUAL_STATE 936
#define MT_GRASP_EVENT 937

typedef ROBOT_ACTUAL_STATE                 MDF_ROBOT_ACTUAL_STATE;
typedef ROBOT_CONTROL_STATE                MDF_ROBOT_CONTROL_STATE;
typedef ROBOT_CONTROL_SPACE_ACTUAL_STATE   MDF_ROBOT_CONTROL_SPACE_ACTUAL_STATE;
//typedef GRASP_EVENT                        MDF_GRASP_EVENT;
/////////////////////////////////////////////////////////////////////////////////
//        --> ROBOT CONTROL
/////////////////////////////////////////////////////////////////////////////////
#define MT_ROBOT_CONTROL_CONFIG 938
typedef ROBOT_CONTROL_CONFIG    MDF_ROBOT_CONTROL_CONFIG;


/////////////////////////////////////////////////////////////////////////////////
//        --> AWESOME IO MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_GIVE_REWARD 600
typedef struct {
	double duration_ms;
    double num_clicks;
} MDF_GIVE_REWARD;

#define NUM_ANALOG_STREAM_CHANS 12
#define ASC_MONKEY_KNOB 0   // ASC = Analog Stream Channel
#define ASC_MONKEY_DOOR 1
#define ASC_ROBOT_KNOB  2
#define ASC_ROBOT_DOOR  3
#define ASC_ARMREST_LF  4
#define ASC_ARMREST_LB  5
#define ASC_ARMREST_RF  6
#define ASC_ARMREST_RB  7
#define ASC_JOYPAD_LEFT_UD 8
#define ASC_JOYPAD_LEFT_LR 9
#define ASC_JOYPAD_RIGHT_UD 10
#define ASC_JOYPAD_RIGHT_LR 11

#define MT_IO_START_STREAM  601
typedef struct {
	struct {
		double high[NUM_ANALOG_STREAM_CHANS];
		double low[NUM_ANALOG_STREAM_CHANS];
	} limits;               // Outgoing data will be scaled 0..1 according to the limits
	int reserved;           // 64-bit alignment padding
	int internal_sampling;  // If true, generate samples using internal timing. If false, generate sample when SAMPLE_GENERATED message received
	double sample_interval; // Desired sample interval when using internal sampling
} MDF_IO_START_STREAM;
#define MT_IO_STOP_STREAM   602

/////////////////////////////////////////////////////////////////////////////////
//        <-- AWESOME IO MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_JOYPAD_R1	          610
#define MT_JOYPAD_R2		      611
#define MT_JOYPAD_X	              612
#define MT_JOYPAD_PAD_BUTTON      613
#define MT_READY_BUTTON           614


#define MT_ANALOG_STREAM          620
typedef struct {
	SAMPLE_HEADER sample_header;
	double sample_interval; // in seconds
	double data[NUM_ANALOG_STREAM_CHANS];
} MDF_ANALOG_STREAM;
#define MT_IO_STREAM_STARTED      621
#define MT_IO_STREAM_STOPPED      622

/////////////////////////////////////////////////////////////////////////////////
//        <-- Knob Module
/////////////////////////////////////////////////////////////////////////////////
typedef struct {
	double source_time; // Abs RTMA time when analog sample that caused the event was generated
	double event_time;  // Abs RTMA time when Knob module detected the event
	int sample_no;      // Sample number of analog sample that caused the event
} KNOB_EVENT_DATA;
#define MT_KNOB_TOUCHED             640
typedef KNOB_EVENT_DATA MDF_KNOB_TOUCHED;
#define MT_KNOB_TURNED              641
typedef KNOB_EVENT_DATA MDF_KNOB_TURNED;
#define MT_KNOB_ANTI_TURNED         642
typedef KNOB_EVENT_DATA MDF_KNOB_ANTI_TURNED;
#define MT_KNOB_OVER_TURNED         643
typedef KNOB_EVENT_DATA MDF_KNOB_OVER_TURNED;
#define MT_DOOR_MOVED               644
typedef KNOB_EVENT_DATA MDF_DOOR_MOVED;
#define MT_DOOR_OPENED              645
typedef KNOB_EVENT_DATA MDF_DOOR_OPENED;
#define MT_DOOR_ANTI_OPENED         646
typedef KNOB_EVENT_DATA MDF_DOOR_ANTI_OPENED;
#define MT_DOOR_OVER_OPENED         647
typedef KNOB_EVENT_DATA MDF_DOOR_OVER_OPENED;
#define MT_KNOB_MOVED               648
typedef KNOB_EVENT_DATA MDF_KNOB_MOVED;
#define MT_DOOR_UN_OPENED           649
typedef KNOB_EVENT_DATA MDF_DOOR_UN_OPENED;
#define MT_KNOB_RELEASED            650
typedef KNOB_EVENT_DATA MDF_KNOB_RELEASED;

#define MT_PAD_PRESSED              660
typedef KNOB_EVENT_DATA MDF_PAD_PRESSED;
#define MT_PAD_STEADY               661
typedef KNOB_EVENT_DATA MDF_PAD_STEADY;
#define MT_PAD_PERTURBED            662
typedef KNOB_EVENT_DATA MDF_PAD_PERTURBED;
#define MT_PAD_RELEASED             663
typedef KNOB_EVENT_DATA MDF_PAD_RELEASED;


/////////////////////////////////////////////////////////////////////////////////
//        --> DENSO MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_DENSO_CONFIG         800    // Set config parameters in the DENSO module
#define MT_DENSO_INITIALIZE     801    // Initialize controller and turn motors on
#define MT_DENSO_MOVE           802    // Move to a position
#define MT_DENSO_HALT           803    // Halt the current movement
#define MT_DENSO_SET_SPEED      804    // Set the speed of subsequent moves
#define MT_DENSO_WIGGLE         806    // Wiggle the base joint (to test that the robot is working)
#define MT_DENSO_MOVE_CONTINUE  807

typedef struct {
	int position_no; // Position number (1 to N)
	int movement_id; // An ID that will be sent back in the DENSO_MOVE_COMPLETE, DENSO_MOVE_FAILED or DENSO_MOVE_INVALID messages
} MDF_DENSO_MOVE;

typedef struct {
	double speed;
} MDF_DENSO_SET_SPEED;

typedef MDF_DENSO_MOVE  MDF_DENSO_MOVE_CONTINUE;


/////////////////////////////////////////////////////////////////////////////////
//        <-- DENSO MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_DENSO_READY          850    // Response to MT_DENSO_INITIALIZE when robot is ready to move
#define MT_DENSO_NOT_READY      851    // Response to MT_DENSO_INITIALIZE when robot failed to initialize
#define MT_DENSO_MOVE_COMPLETE  852    // Response to MT_DENSO_MOVE when move is complete
#define MT_DENSO_MOVE_FAILED    853    // Response to MT_DENSO_MOVE when move failed
#define MT_DENSO_MOVE_INVALID   854    // Response to MT_DENSO_MOVE when move parameters are invalid
#define MT_DENSO_HALTED         855    // Response to MT_DENSO_HALT
typedef STRING_DATA MDF_DENSO_NOT_READY;
typedef struct {
	int movement_id; // The ID from the DENSO_MOVE message
	int reserved;    // 64-bit alignment
} RESPONSE_DATA_TO_DENSO_MOVE;
typedef RESPONSE_DATA_TO_DENSO_MOVE   MDF_DENSO_MOVE_COMPLETE;
typedef RESPONSE_DATA_TO_DENSO_MOVE   MDF_DENSO_MOVE_FAILED;
typedef RESPONSE_DATA_TO_DENSO_MOVE   MDF_DENSO_MOVE_INVALID;
typedef RESPONSE_DATA_TO_DENSO_MOVE   MDF_DENSO_HALTED;


/////////////////////////////////////////////////////////////////////////////////
//        --> EXTRACTION MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_KILL_KILL_KILL_EM       300
/////////////////////////////////////////////////////////////////////////////////
//        <-- EXTRACTION MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_EM_MOVEMENT_COMMAND     350
typedef MOVEMENT_COMMAND_DATA MDF_EM_MOVEMENT_COMMAND;

#define MT_EM_AUX_MOVEMENT_COMMAND     355
typedef MOVEMENT_COMMAND_DATA MDF_EM_AUX_MOVEMENT_COMMAND;

#define MT_COMPOSITE_MOVEMENT_COMMAND 366
typedef MOVEMENT_COMMAND_DATA MDF_COMPOSITE_MOVEMENT_COMMAND;

#define MT_ROBOT_MOVEMENT_COMMAND 351
typedef MOVEMENT_COMMAND_DATA MDF_ROBOT_MOVEMENT_COMMAND;

#define MT_PLANNER_MOVEMENT_COMMAND 352
typedef MOVEMENT_COMMAND_DATA MDF_PLANNER_MOVEMENT_COMMAND;

#define MT_PLANNER_STATE  353
typedef PLANNER_STATE MDF_PLANNER_STATE;

#define MT_PLAN_PROCESSOR_STATE 354
typedef PLAN_PROCESSOR_STATE MDF_PLAN_PROCESSOR_STATE;
/////////////////////////////////////////////////////////////////////////////////
//        --> FAKE MONKEY MODULE
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//        <-- FAKE MONKEY MODULE
/////////////////////////////////////////////////////////////////////////////////
#define MT_FM_MOVEMENT_COMMAND     430
typedef MOVEMENT_COMMAND_DATA MDF_FM_MOVEMENT_COMMAND;

/////////////////////////////////////////////////////////////////////////////////
//        --> JOYPAD MONKEY MODULE
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//        <-- JOYPAD MONKEY MODULE
/////////////////////////////////////////////////////////////////////////////////
//#define MT_JM_MOVEMENT_COMMAND     480
//typedef MOVEMENT_COMMAND_DATA MDF_JM_MOVEMENT_COMMAND;
#define MT_OVERRIDE_COMMAND 480
typedef OVERRIDE_COMMAND MDF_OVERRIDE_COMMAND;
#define MT_JVEL_COMMAND 481
typedef JVEL_COMMAND MDF_JVEL_COMMAND;


/////////////////////////////////////////////////////////////////////////////////
//        --> WATCHDOG MODULE
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//        <-- WATCHDOG MODULE
/////////////////////////////////////////////////////////////////////////////////
#define NUM_COMPONENT_DELAYS    6
#define MT_COMPONENT_DELAY_MSG_TYPES  200 // Message for sending out a list of message types that are used for component delay calculation
typedef int  MDF_COMPONENT_DELAY_MSG_TYPES[NUM_COMPONENT_DELAYS];
typedef struct {
	SAMPLE_HEADER sample_header;
    double Components[NUM_COMPONENT_DELAYS];
	double Total;
} DELAY_DATA;
#define MT_ESTIMATED_DELAY     201 // Delay estimated when each sample is arrives
typedef DELAY_DATA  MDF_ESTIMATED_DELAY;

#define MT_MEASURED_DELAY      202 // Measured delay for each sample after the response arrives
typedef DELAY_DATA  MDF_MEASURED_DELAY;


/////////////////////////////////////////////////////////////////////////////////
#define MT_NOOP      998
#define MT_KEYBOARD  1002 // Causes all matlab modules to go to K>> prompt for debugging
#define MT_CLEAR_FUNCTION 1003  // Causes subscribed Matlab modules to clear the named function, so it can be fixed at runtime
typedef char MDF_CLEAR_FUNCTION[];


#define MT_LATE_ADAPT_NOW 1005



#define MT_DUMMY_MESSAGE  2000

#define MT_TARG_CLOUD 1006

typedef struct {
  SAMPLE_HEADER sample_header;
  double cloud[MAX_CONTROL_DIMS * MAX_D_COLS];
  int nTargs;
  int spacer;
} TARG_CLOUD;

typedef TARG_CLOUD MDF_TARG_CLOUD;


/* #define MT_SECONDARY_VEL_COMMANDS 1007 */

/* typedef struct { */
/*   SAMPLE_HEADER sample_header; */
/*   double targ_vel_matrix[MAX_CONTROL_DIMS * MAX_D_COLS]; */
/*   int nTargs; */
/*   int spacer; */
/* } SECONDARY_VEL_COMMANDS; */

#define MT_ATTENTION 1659
typedef double MDF_ATTENTION;


#define MT_RELOAD_CONFIGURATION 1004

//typedef SECONDARY_VEL_COMMANDS MDF_SECONDARY_VEL_COMMANDS;


#endif //_RTMA_CONFIG_H_
