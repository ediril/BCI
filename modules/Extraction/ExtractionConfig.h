#ifndef __PVA_CONFIGURATION_H__
#define __PVA_CONFIGURATION_H__

#define MAX_REDUCED_SPIKE_CHANS 200

// Extraction module constants
#define MAX_EM_DIMENSIONS    MAX_CONTROL_DIMS // e.g. [x, y, z, gripper] or [x, rot, fingers] or whatever you want. This is only a maximum for declared fixed size arrays. Not all dimenions are necessarily used.


#define MT_EM_START_SESSION		  1600
#define MT_EM_END_SESSION		  1601
#define MT_EM_FREEZE			  1602
#define MT_EM_RESET_STATE		  1603
#define MT_EM_UNFREEZE			  1604
#define MT_EM_START_TRIAL		  1605
#define MT_EM_END_TRIAL			  1606
#define MT_EM_DISCARD_TRIAL		  1607
#define MT_EM_ADAPT_NOW			  1608
#define MT_EM_FEEDBACK			  1609
#define MT_EM_MOD_DEPTH_CUTOFF	  1610
#define MT_EM_PAUSE_COLLECTION	  1611
#define MT_EM_RESUME_COLLECTION	  1612
#define MT_EM_GET_PDS			  1613
#define MT_EM_SET_PDS			  1614
#define MT_EM_AGGREGATE_DATA_NOW  1615 //Send whenever you want
#define MT_EM_RESET_AGGREGATION	  1616 //Send before unfreezing the EM (if suitable)
#define MT_EM_CORRECT_DRIFT_NOW   1617
#define MT_EM_UPDATE_DRIFT_CORRECTION 1618
#define MT_RELOAD_PVA_CONFIG 1619

// <- ExtractionModule
#define MT_EM_READY				  1650
#define MT_EM_FROZEN			  1651
#define MT_EM_ADAPT_DONE		  1652
#define MT_EM_ADAPT_FAILED		  1653
#define MT_EM_MOD_DEPTH_FAILED	  1654
#define MT_EM_MOD_DEPTH_SUCCEEDED 1655
#define MT_EM_PDS				  1656
#define MT_EM_ALREADY_FROZEN	  1657
#define MT_EM_DRIFT_CORRECTED     1658

// Attention study.
//#define MT_ATTENTION			  1659




// ExtractionModule data formats
typedef struct {
  //  char SubjectName[MAX_SUBJECTNAME_LENGTH];		// [string] 
  //  char Filename2Load[MAX_FILENAME_LENGTH];		// [string]
  //  char Filename2Save[MAX_FILENAME_LENGTH];		// [string]
  //  char ConfigFilename[MAX_FILENAME_LENGTH];		// [string]
  double Dimensions[MAX_EM_DIMENSIONS];           // [1xN] dimension mask of dimensions to be used when predicting (e.g. [1 0 1] means use X and Z dimensions)
  //  int  NumConfiguredDimensions;                   // number of dimensions (out of MAX_EM_DIMENSIONS) that are configured to be used in communicating with the EM (e.g. 3 if only doing x,y,z prediction or 4 if doing x,y,z,g)

  //  int reserved;

  //  int  CumulativeUpdates;							// [bool]

  //  double AverageTargetDistance[MAX_EM_DIMENSIONS];// distance from initial pos to target for each dimension, averaged across targets
  //  char ModulationMode[MAX_EM_DIMENSIONS];         // [character field] specifies modulation mode of each dimension (e.g. 'VVVP' means velocity modulation for x,y,z and position for gripper)
} EM_PARAMS;

typedef EM_PARAMS MDF_EM_START_SESSION;

#define MT_RELOAD_CONFIGURATION 1004  

typedef EM_PARAMS MDF_RELOAD_CONFIGURATION;


typedef struct {
  int regressionGroups[MAX_EM_DIMENSIONS];
} EM_PROCEDURE_MESSAGE;

typedef EM_PROCEDURE_MESSAGE MDF_EM_RESET_AGGREGATION;
typedef EM_PROCEDURE_MESSAGE MDF_EM_RESUME_COLLECTION;
typedef EM_PROCEDURE_MESSAGE MDF_EM_AGGREGATE_DATA_NOW;
typedef EM_PROCEDURE_MESSAGE MDF_EM_PAUSE_COLLECTION;



typedef struct {
    double initial_position[MAX_EM_DIMENSIONS];      // [mm]
    double initial_velocity[MAX_EM_DIMENSIONS];      // [mm/sec]
    double target_position[MAX_EM_DIMENSIONS];       // [mm]
  int reset_history;                               // boolean, whether to forget spike history
    int reserved;                                    // for 64-bit alignment
} MDF_EM_RESET_STATE;

typedef struct {
	int data_index;
	int reserved;
} MDF_EM_START_TRIAL;

//typedef double MDF_EM_AGGREGATE_DATA_NOW; // A flag that indicates what the data is for (b0 estimation or regular estimation)

typedef struct {
	int first_data_index;
	int last_data_index;
} MDF_EM_ADAPT_NOW; // Includes data between first_data_index and last_data_index in adaptation, where indices are labels on the data points that were specified in the START_TRIAL message

typedef struct {
    double drift_correction[MAX_EM_DIMENSIONS];
} MDF_EM_UPDATE_DRIFT_CORRECTION;

/* typedef struct { */
/*     SAMPLE_HEADER sample_header; */
/* 	double pos[MAX_EM_DIMENSIONS];					//[mm] or some application-specific unit */
/* 	double target_pos[MAX_EM_DIMENSIONS];			//[mm] or some application-specific unit */
/* } MDF_EM_FEEDBACK; */

/* typedef struct { */
/*     double drift_correction[MAX_EM_DIMENSIONS]; */
/* } MDF_EM_DRIFT_CORRECTED; */

typedef double   MDF_EM_MOD_DEPTH_CUTOFF;
typedef char	 MDF_EM_SET_PDS[];
typedef char	 MDF_EM_PDS[];

/// Indicator for attention level.
//typedef double	 MDF_ATTENTION;

typedef struct 
{
  double Norm2RealFactor[MAX_EM_DIMENSIONS];
  double ModDepthCutoff;
  double RSquaredCutoff;
  double PredictFRFilter[33];
  double AdaptFRFilter[33];
  double TargetFilter[33];
  double RegressionGroups[MAX_EM_DIMENSIONS];
  char tag[64];
  double ControlledDims[MAX_EM_DIMENSIONS];
  double numAdaptReps;
  // double laterAdaptPdWeight;
						
} PVAConfig;

#define MT_PVA_CONFIG 382

typedef PVAConfig MDF_PVA_CONFIG;

typedef struct 
{
  char tag[64];
  double PV[MAX_REDUCED_SPIKE_CHANS * 8]; // max controlled dims
  int usedIndices[MAX_REDUCED_SPIKE_CHANS];
  

} PVAState;

#define MT_PVA_STATE 383

typedef PVAState MDF_PVA_STATE;


typedef struct
{
  char targTag[64];

  double attenuationLevel[MAX_REDUCED_SPIKE_CHANS];

} PVAAttenuateCommand;

#define MT_DECISION 384

#define MT_TRAINING_BEGIN 385

#define MT_DO_IT_DECIDER 386
#define MT_PVA_ATTENUATE_COMMAND 387
typedef PVAAttenuateCommand MDF_PVA_ATTENUATE_COMMAND;



#endif
