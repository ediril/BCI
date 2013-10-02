#include "common_defs.h"
#include "spike_types.h"

// ============================================================================
// Module ID-s
// ============================================================================
#define MID_GROBOT_RAW_FEEDBACK     19
#define MID_GROBOT_FEEDBACK         18
#define MID_DIGITAL_IO              17
#define MID_TASK_JUDGE              16
#define MID_SI_MOVEMENT             15
#define MID_INPUT_TRANSFORM         14
#define MID_SIMPLE_ARBITRATOR       13
#define MID_OUTPUT_TRANSFORM        12
#define MID_FEEDBACK_TRANSFORM      11
#define MID_SAMPLE_GENERATOR        29
#define MID_VIRTUAL_FIXTURING       28
#define MID_CANNED_MOVEMENT         27
#define MID_HAND_VIZ                30
#define MID_IDLE_MONKEY             36
#define MID_CALIBRATION             37
#define MID_SSH_CONTROLLER          35
#define MID_IDLE_DETECTOR           38
#define MID_ARDUINO_IO              39
#define MID_POSITION_CONTROLLER     40
#define MID_JOINT_CONTROLLER        42

#define MID_WAM_BHAND				25

// <EM Override config from MD_GUI - Mike>
#define MID_EM_OVERRIDE_CONFIG		31
//</Mike>
#define MID_OPTO_MPL_CTRL           32
#define MID_OBSTACLE_COURSE         33
#define MID_SKELETON_CTRL           34

//RG additions - SegmentPercepts & Stimulator Control
#define MID_GROBOT_SEGMENT_PERCEPTS	56
#define MID_CERESTIM_CONFIG			57
#define MID_CERESTIM_CONTROL		58


#define MID_COMMAND_SPACE_FEEDBACK_GUI  89
#define MID_MESSAGE_WATCHER             88

// ============================================================================
// Message ID-s
// ============================================================================

//RG additions - SegmentPercepts & Stimulator Control
#define MT_GROBOT_SEGMENT_PERCEPTS	1888
#define MT_CERESTIM_CONFIG_MODULE   1889
#define MT_CERESTIM_CONFIG_CHAN		1890



#define MT_GROBOT_COMMAND         1700
#define MT_GROBOT_RAW_FEEDBACK    1701
#define MT_GROBOT_FEEDBACK        1702
#define MT_COMMANDSPACE_FEEDBACK  1703
#define MT_GROBOT_BYPASS          1704
#define MT_GROBOT_END_BYPASS      1707
// <Cyber Glove and microstrain messages - Mike>
#define MT_MICROSTRAIN_DATA		  1705
#define MT_GLOVE_DATA			  1706
// </Mike>

// <EM Override config from MD_GUI - Mike>
#define MT_EM_OVERRIDE_CONFIG	  1708
//</Mike>
#define MT_OPTO_CNTRL_CMD         1709
#define MT_OPTO_POS_CMD           1712
#define MT_KIN_POS_CMD            1713
#define MT_KINECT_SKELETON        1711
#define MT_SESSION_CONFIG         1710

#define MT_RAW_SPIKECOUNT         1750
#define MT_SPM_SPIKECOUNT         1751
#define MT_SAMPLE_GENERATED       1752 // Notifies whoever cares that a spike count sample has been generated
#define MT_SAMPLE_RESPONSE        1753
#define MT_RESET_SAMPLE_ALIGNMENT 1754

#define MT_SYNCH_NOW              1800
#define MT_SYNCH_START            1801
#define MT_SYNCH_DONE             1802

#define MT_INPUT_DOF_DATA         1850
typedef INPUT_DOF_DATA MDF_INPUT_DOF_DATA;

#define MT_OPERATOR_MOVEMENT_COMMAND               1900 // joystick
typedef MOVEMENT_COMMAND_DATA MDF_OPERATOR_MOVEMENT_COMMAND;

#define MT_FIXTURED_MOVEMENT_COMMAND               1910
typedef MOVEMENT_COMMAND_DATA MDF_FIXTURED_MOVEMENT_COMMAND;

#define MT_SHADOW_COMPOSITE_MOVEMENT_COMMAND     1919
typedef MOVEMENT_COMMAND_DATA MDF_SHADOW_COMPOSITE_MOVEMENT_COMMAND;

#define MT_FIXTURED_COMPOSITE_MOVEMENT_COMMAND     1920
typedef MOVEMENT_COMMAND_DATA MDF_FIXTURED_COMPOSITE_MOVEMENT_COMMAND;

#define MT_PROBOT_FEEDBACK			1930
#define MAX_PROBOT_FEEDBACK_DIMS 	7
typedef struct {
  SAMPLE_HEADER sample_header;
  double tool_pos[MAX_PROBOT_FEEDBACK_DIMS];
  double wrist_pos[MAX_PROBOT_FEEDBACK_DIMS];
} MDF_PROBOT_FEEDBACK;

#define MT_CHANGE_TOOL				1940
#define MT_CHANGE_TOOL_INVALID      1941
#define MT_CHANGE_TOOL_COMPLETE     1942
#define MT_CHANGE_TOOL_FAILED       1943

#define MT_TASK_STATE_CONFIG		1950
#define MT_JUDGE_VERDICT			1960
#define MT_END_TASK_STATE			1970
#define MT_RAW_SAMPLE_RESPONSE		1980
#define MT_CODE_VERSION				1990
#define MT_TRIAL_DATA_SAVED         2080
#define MT_EM_DECODER_CONFIGURATION 2090
#define MT_SPM_FIRINGRATE           2100
#define MT_LOAD_DECODER_CONFIG      2110
#define MT_APP_START                2120
#define MT_APP_START_COMPLETE       2121    // signal
#define MT_MODULE_START             2125
#define MT_MODULE_START_COMPLETE    2126    // signal
#define MT_EXIT_ACK                 2130    // signal
#define MT_PING                     2140
#define MT_PING_ACK                 2141
#define MT_XM_START_SESSION         2150
#define MT_DEBUG_VECTOR             2160
#define MT_SPM_SPIKE_SNIPPET        2170
#define MT_SPM_SPIKE_TIMES          2171
#define MT_XM_END_OF_SESSION        2180    // signal
#define MT_IDLY_LABELLING           2190
#define MT_IDLY_RESET_LABELLING     2200    // signal
#define MT_EM_DRIFT_CORRECTION      2210
#define MT_ARTIFACT_REJECTED        2220    // signal
#define MT_PLAY_SOUND               2230
#define MT_WAM_FEEDBACK				2240
#define MT_WAM_HAND_FEEDBACK        2242
#define MT_IDLE                     2250
#define MT_IDLE_DETECTION_ENDED     2251    // signal
#define MT_PLANNER_CONTROL_CONFIG   2260
#define MT_ROBOT_JOINT_COMMAND      2270
#define MT_IDLEGATED_MOVEMENT_COMMAND    2280


// ============================================================================
// Message Data Formats
// ============================================================================
#define MAX_GROBOT_JOINTS        28
#define MAX_GROBOT_COMMAND_DIMS  18 // big enough to support joint control (i.e. 17 joints)
#define MAX_GROBOT_FEEDBACK_DIMS 18
#define MAX_OPTO_CTRL_JOINTS     6
#define MAX_OPTO_POS             4
#define MAX_KIN_POS              4
#define NUM_FINGER_DIMS          10
#define KINECT_JOINTS            20
#define MAX_JOINT_DIMS           8
// ============================================================================
// Possible ways for us to control the MPL
// i.e. modes of the GROBOT_COMMAND Message
// They all begin with MPL_AT_ which stands for MPL Actuation Type
// ============================================================================
#define MPL_AT_ARM_EPV_FING_JV   0
#define MPL_AT_ARM_EPV_FING_JP   1
#define MPL_AT_ARM_JV_FING_JP    2
#define MPL_AT_ALL_JV            3
#define MPL_AT_ALL_JP            4
#define MPL_AT_ARM_EPP_FING_JP   5

typedef struct {
  SAMPLE_HEADER sample_header;
  double command[MAX_GROBOT_COMMAND_DIMS];
  int mode;
  int reserved;
} MDF_GROBOT_COMMAND;

typedef struct {
  double command[MAX_GROBOT_COMMAND_DIMS];
  int mode;
  int reserved;
} MDF_GROBOT_BYPASS;

typedef struct {
  double Cmd[MAX_OPTO_CTRL_JOINTS];
} MDF_OPTO_CNTRL_CMD;

typedef struct {
  double Cmd[MAX_OPTO_POS];
} MDF_OPTO_POS_CMD;

typedef struct {
  double Cmd[MAX_KIN_POS];
} MDF_KIN_POS_CMD;

typedef struct {
  double x[KINECT_JOINTS];
  double y[KINECT_JOINTS];
  double z[KINECT_JOINTS];
  double w[KINECT_JOINTS];
  int Which;
  int Reserved;
} MDF_KINECT_SKELETON;

typedef struct {
    double ind_force[3];
	double mid_force[3];
	double rng_force[3];
	double lit_force[3];
	double thb_force[3];

	double ind_accel[3];
	double mid_accel[3];
	double rng_accel[3];
	double lit_accel[3];
	double thb_accel[3];
} MDF_GROBOT_SEGMENT_PERCEPTS;

typedef struct {
    int configID;
	int afcf;
	double pulses;		//unsigned char required by API
	double amp1;		//unsigned char required by API
	double amp2;		//unsigned char required by API
	double width1;		//unsigned short required by API
	double width2;		//unsigned short required by API
	double frequency;	//unsigned short required by API
	double interphase;	//unsigned short required by API
} MDF_CERESTIM_CONFIG_MODULE;

typedef struct {
    int stop;
	int group_stimulus;
	int group_numChans;
	int group_channel[16];
	int group_pattern[16];

	int manual_stimulus;
	int manual_channel;
	int manual_pattern;
} MDF_CERESTIM_CONFIG_CHAN;

typedef struct {
    double j_ang[MAX_GROBOT_JOINTS];
    double j_vel[MAX_GROBOT_JOINTS];
    double j_trq[MAX_GROBOT_JOINTS];
} MDF_GROBOT_RAW_FEEDBACK;

typedef struct {
  SAMPLE_HEADER sample_header;
  double position[MAX_GROBOT_FEEDBACK_DIMS];
  double velocity[MAX_GROBOT_FEEDBACK_DIMS];
  double force[MAX_GROBOT_FEEDBACK_DIMS];
  double cori_matrix[9];
} MDF_GROBOT_FEEDBACK;

#define MAX_DATA_DIR_LEN 128

typedef struct {
  char data_dir[MAX_DATA_DIR_LEN];
} MDF_SESSION_CONFIG;

// Cyber glove: Handles the 29 inputs from the cyber glove and microstrain arm
#define MAX_CYBER_GLOVE_DIMS 30
typedef struct {
  SAMPLE_HEADER sample_header;
  double data[MAX_CYBER_GLOVE_DIMS];
} MDF_GLOVE_DATA;
typedef struct {
  SAMPLE_HEADER sample_header;
  double data[MAX_CYBER_GLOVE_DIMS];
} MDF_MICROSTRAIN_DATA;

// EM Override Config from MD_GUI
#define MAX_EM_CHANNELS 1728
typedef struct {
  int chosen_channel_mask[MAX_EM_CHANNELS];
} MDF_EM_OVERRIDE_CONFIG;

typedef struct {
	int next_tool_id;
	int reserved;
} MDF_CHANGE_TOOL;

typedef struct {
	int tool_id;
	int reserved;
} MDF_CHANGE_TOOL_COMPLETE;

#define MAX_FINGER_DIMS     10
#define MAX_PERCEPT_DIMS    15
#define MAX_HAND_DIMS       MAX_FINGER_DIMS+MAX_PERCEPT_DIMS
typedef struct {
	int    id;
    int    rep_num;
    int    use_for_calib;
	int    target_combo_index;
    int    timed_out_conseq;
    int    idle_gateable;
    int    reach_offset;
    int    relax_arm;
    double idle_timeout;
    double ts_time;
	double target[MAX_CONTROL_DIMS+MAX_PERCEPT_DIMS];
	double coriMatrix[9];
	double idle_target[MAX_CONTROL_DIMS];
    double trans_threshold;
	double ori_threshold;
    double trans_threshold_f;
	double ori_threshold_f;
	double finger_threshold[MAX_HAND_DIMS];
    int    finger_threshold_judging_method[MAX_HAND_DIMS];
    int    finger_threshold_judging_polarity[MAX_HAND_DIMS];
    int    trans_threshold_judging_polarity;
    int    ori_threshold_judging_polarity;
    int    trans_threshold_f_judging_polarity;
    int    ori_threshold_f_judging_polarity;
    double timeout;
    char   tags[TAG_LENGTH];
} MDF_TASK_STATE_CONFIG;

typedef struct {
	int  id;
	int  reserved;
	char reason[TAG_LENGTH];
} MDF_JUDGE_VERDICT;

typedef struct {
	int  id;
	int  outcome;
	char reason[TAG_LENGTH];
} MDF_END_TASK_STATE;

typedef struct {
  int source_index;    		// a zero-based index in the range 0..(N-1) for N spike sources (e.g. separate acquisition boxes)
  int reserved;        		// for 64-bit alignment
  double source_timestamp;	// [seconds]source timestamp of the event that caused this count to happen
} MDF_RAW_SAMPLE_RESPONSE;

typedef struct {
	char module_name[TAG_LENGTH];
	char version[TAG_LENGTH];
} MDF_CODE_VERSION;

typedef struct {
  SAMPLE_HEADER sample_header;
  double source_timestamp;// [seconds] source timestamp of the event that caused this count to happen
  double count_interval;  // [seconds]
  double rates[MAX_TOTAL_SPIKE_CHANS];
} MDF_SPM_FIRINGRATE;

typedef unsigned char MDF_EM_DECODER_CONFIGURATION[];

typedef struct {
  char full_path[MAX_DATA_DIR_LEN];
} MDF_LOAD_DECODER_CONFIG;

typedef struct {
    int  load_calibration;
    int  calib_session_id;
    int  num_reps;
    int  reserved;
    char subject_name[TAG_LENGTH];
} MDF_XM_START_SESSION;

typedef struct {
    char  module_name[TAG_LENGTH];
} MDF_PING;

typedef struct {
    char  module_name[TAG_LENGTH];
} MDF_PING_ACK;

typedef struct {
    double data[32];
} MDF_DEBUG_VECTOR;

typedef struct {
    char  config[TAG_LENGTH];
} MDF_APP_START;

typedef struct {
    char  module[TAG_LENGTH];
} MDF_MODULE_START;

typedef struct {
    double  time;
    int     chan;
    int     unit;
    int     box_id;
    int     length;             // of snippet data in bytes
    short   snippet[48];
} MDF_SPM_SPIKE_SNIPPET;

#define MAX_SPIKE_TIMES_PER_PACKET 256
typedef struct {
    double time[MAX_SPIKE_TIMES_PER_PACKET];
    short  chan[MAX_SPIKE_TIMES_PER_PACKET];
    char   unit[MAX_SPIKE_TIMES_PER_PACKET];
    char   box_id[MAX_SPIKE_TIMES_PER_PACKET];  
} MDF_SPM_SPIKE_TIMES;

typedef struct {
    int     state;
    int     reserved;
} MDF_IDLY_LABELLING;

typedef struct {
  SAMPLE_HEADER sample_header;
  double        drift_correction[MAX_CONTROL_DIMS];
} MDF_EM_DRIFT_CORRECTION;

typedef struct {
    int     movement_id;
    int     num_cycles;
    int     sequence[8];
    double  amplitude[3];   // translation dims only
} MDF_DENSO_WIGGLE;

typedef struct {
    int     id;
    int     reserved;
} MDF_PLAY_SOUND;

typedef struct {
    double  time;
} MDF_ARTIFACT_REJECTED;

typedef struct {
    SAMPLE_HEADER sample_header;
    double score;
    double gain;
    int    idle;        // Actually meant to be boolean
    int    reserved;
} MDF_IDLE;

typedef ROBOT_CONTROL_SPACE_ACTUAL_STATE   MDF_WAM_FEEDBACK;
typedef ROBOT_CONTROL_SPACE_ACTUAL_STATE   MDF_WAM_HAND_FEEDBACK;

typedef struct {
  double target[MAX_CONTROL_DIMS];
  double coriMatrix[9];
} MDF_PLANNER_CONTROL_CONFIG;

typedef struct {
    SAMPLE_HEADER sample_header;
    double  pos[MAX_JOINT_DIMS];
    int     controlledDims[MAX_JOINT_DIMS];
    int     overrideDims[MAX_JOINT_DIMS];
} MDF_ROBOT_JOINT_COMMAND;

typedef MOVEMENT_COMMAND_DATA MDF_IDLEGATED_MOVEMENT_COMMAND;

