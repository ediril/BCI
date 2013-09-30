namespace Dragonfly {

    ref class MT
    {
    public:
        static const int EXIT = 0;
        static const int KILL = 1;
        static const int ACKNOWLEDGE = 2;
        static const int FAIL_SUBSCRIBE = 6;
        static const int FAILED_MESSAGE = 7;
        static const int MM_ERROR = 83;
        static const int MM_INFO = 84;
        static const int CONNECT = 13;
        static const int DISCONNECT = 14;
        static const int SUBSCRIBE = 15;
        static const int UNSUBSCRIBE = 16;
        static const int PAUSE_SUBSCRIPTION = 85;
        static const int RESUME_SUBSCRIPTION = 86;
        static const int SHUTDOWN_DRAGONFLY = 17;
        static const int SHUTDOWN_APP = 18;
        static const int FORCE_DISCONNECT = 82;
        static const int CORE_MODULE_REINIT_ACK = 25;
        static const int MODULE_READY = 26;
        static const int DYNAMIC_DD_READ_ERR = 90;
        static const int DEBUG_TEXT = 91;
        static const int AM_EXIT = 30;
        static const int START_APP = 31;
        static const int STOP_APP = 32;
        static const int RESTART_APP = 33;
        static const int KILL_APP = 34;
        static const int AM_RE_READ_CONFIG_FILE = 89;
        static const int AM_GET_APP_NAME = 92;
        static const int SLAVE_START_APP = 64;
        static const int SLAVE_START_APP_ACK = 65;
        static const int SLAVE_STOP_APP = 66;
        static const int SLAVE_KILL_APP = 67;
        static const int SLAVE_RESTART_APP = 68;
        static const int AM_ERROR = 35;
        static const int AM_ACKNOWLEDGE = 36;
        static const int FAIL_START_APP = 37;
        static const int FAIL_STOP_APP = 38;
        static const int FAIL_KILL_APP = 39;
        static const int APP_START_COMPLETE = 2121;
        static const int APP_SHUTODWN_COMPLETE = 41;
        static const int APP_RESTART_COMPLETE = 42;
        static const int APP_KILL_COMPLETE = 43;
        static const int ALL_MODULES_READY = 44;
        static const int CORE_MODULE_REINIT = 45;
        static const int AM_CONFIG_FILE_DATA = 46;
        static const int AM_APP_NAME = 93;
        static const int SLAVE_ALL_MODULES_READY = 69;
        static const int SLAVE_FAIL_START_APP = 70;
        static const int SLAVE_FAIL_STOP_APP = 71;
        static const int SLAVE_FAIL_KILL_APP = 72;
        static const int SLAVE_APP_SHUTODWN_COMPLETE = 74;
        static const int SLAVE_APP_RESTART_COMPLETE = 75;
        static const int SLAVE_APP_KILL_COMPLETE = 76;
        static const int SLAVE_AM_ERROR = 77;
        static const int APP_ERROR = 47;
        static const int SM_EXIT = 48;
        static const int CLOCK_SYNC = 49;
        static const int TIMER_EXPIRED = 50;
        static const int TIMED_OUT = 73;
        static const int SET_TIMER_FAILED = 51;
        static const int TM_EXIT = 52;
        static const int SET_TIMER = 53;
        static const int CANCEL_TIMER = 54;
        static const int LM_EXIT = 55;
        static const int MM_READY = 94;
        static const int LM_READY = 96;
        static const int SAVE_MESSAGE_LOG = 56;
        static const int MESSAGE_LOG_SAVED = 57;
        static const int PAUSE_MESSAGE_LOGGING = 58;
        static const int RESUME_MESSAGE_LOGGING = 59;
        static const int RESET_MESSAGE_LOG = 60;
        static const int DUMP_MESSAGE_LOG = 61;
        static const int TIMING_TEST = 62;
        static const int PS3_BUTTON_PRESS = 2135;
        static const int PS3_BUTTON_RELEASE = 2136;
        static const int PS3_STICK_READING = 2137;
        static const int PS3_RAW_CONFIG = 6543;
        static const int PS3_SIMPLE_BUTTON_PRESS = 6544;
        static const int PS3_SIMPLE_BUTTON_RELEASE = 6545;
        static const int PS3_GENERIC_DATA = 6546;
        static const int EM_START_SESSION = 1600;
        static const int EM_END_SESSION = 1601;
        static const int EM_FREEZE = 1602;
        static const int EM_RESET_STATE = 1603;
        static const int EM_UNFREEZE = 1604;
        static const int EM_START_TRIAL = 1605;
        static const int EM_END_TRIAL = 1606;
        static const int EM_DISCARD_TRIAL = 1607;
        static const int EM_ADAPT_NOW = 1608;
        static const int EM_FEEDBACK = 1609;
        static const int EM_MOD_DEPTH_CUTOFF = 1610;
        static const int EM_PAUSE_COLLECTION = 1611;
        static const int EM_RESUME_COLLECTION = 1612;
        static const int EM_GET_PDS = 1613;
        static const int EM_SET_PDS = 1614;
        static const int EM_AGGREGATE_DATA_NOW = 1615;
        static const int EM_RESET_AGGREGATION = 1616;
        static const int EM_CORRECT_DRIFT_NOW = 1617;
        static const int EM_UPDATE_DRIFT_CORRECTION = 1618;
        static const int RELOAD_PVA_CONFIG = 1619;
        static const int EM_READY = 1650;
        static const int EM_FROZEN = 1651;
        static const int EM_ADAPT_DONE = 1652;
        static const int EM_ADAPT_FAILED = 1653;
        static const int EM_MOD_DEPTH_FAILED = 1654;
        static const int EM_MOD_DEPTH_SUCCEEDED = 1655;
        static const int EM_PDS = 1656;
        static const int EM_ALREADY_FROZEN = 1657;
        static const int EM_DRIFT_CORRECTED = 1658;
        static const int RELOAD_CONFIGURATION = 1004;
        static const int PVA_CONFIG = 382;
        static const int PVA_STATE = 383;
        static const int DECISION = 384;
        static const int TRAINING_BEGIN = 385;
        static const int DO_IT_DECIDER = 386;
        static const int PVA_ATTENUATE_COMMAND = 387;
        static const int GROBOT_SEGMENT_PERCEPTS = 1888;
        static const int CERESTIM_CONFIG_MODULE = 1889;
        static const int CERESTIM_CONFIG_CHAN = 1890;
        static const int GROBOT_COMMAND = 1700;
        static const int GROBOT_RAW_FEEDBACK = 1701;
        static const int GROBOT_FEEDBACK = 1702;
        static const int COMMANDSPACE_FEEDBACK = 1703;
        static const int GROBOT_BYPASS = 1704;
        static const int GROBOT_END_BYPASS = 1707;
        static const int MICROSTRAIN_DATA = 1705;
        static const int GLOVE_DATA = 1706;
        static const int EM_OVERRIDE_CONFIG = 1708;
        static const int OPTO_CNTRL_CMD = 1709;
        static const int OPTO_POS_CMD = 1712;
        static const int KIN_POS_CMD = 1713;
        static const int KINECT_SKELETON = 1711;
        static const int SESSION_CONFIG = 1710;
        static const int RAW_SPIKECOUNT = 1750;
        static const int SPM_SPIKECOUNT = 1751;
        static const int SAMPLE_GENERATED = 1752;
        static const int SAMPLE_RESPONSE = 1753;
        static const int RESET_SAMPLE_ALIGNMENT = 1754;
        static const int SYNCH_NOW = 1800;
        static const int SYNCH_START = 1801;
        static const int SYNCH_DONE = 1802;
        static const int INPUT_DOF_DATA = 1850;
        static const int OPERATOR_MOVEMENT_COMMAND = 1900;
        static const int FIXTURED_MOVEMENT_COMMAND = 1910;
        static const int SHADOW_COMPOSITE_MOVEMENT_COMMAND = 1919;
        static const int FIXTURED_COMPOSITE_MOVEMENT_COMMAND = 1920;
        static const int PROBOT_FEEDBACK = 1930;
        static const int CHANGE_TOOL = 1940;
        static const int CHANGE_TOOL_INVALID = 1941;
        static const int CHANGE_TOOL_COMPLETE = 1942;
        static const int CHANGE_TOOL_FAILED = 1943;
        static const int TASK_STATE_CONFIG = 1950;
        static const int JUDGE_VERDICT = 1960;
        static const int END_TASK_STATE = 1970;
        static const int RAW_SAMPLE_RESPONSE = 1980;
        static const int CODE_VERSION = 1990;
        static const int TRIAL_DATA_SAVED = 2080;
        static const int EM_DECODER_CONFIGURATION = 2090;
        static const int SPM_FIRINGRATE = 2100;
        static const int LOAD_DECODER_CONFIG = 2110;
        static const int APP_START = 2120;
        static const int MODULE_START = 2125;
        static const int MODULE_START_COMPLETE = 2126;
        static const int EXIT_ACK = 2130;
        static const int PING = 2140;
        static const int PING_ACK = 2141;
        static const int XM_START_SESSION = 2150;
        static const int DEBUG_VECTOR = 2160;
        static const int SPM_SPIKE_SNIPPET = 2170;
        static const int SPM_SPIKE_TIMES = 2171;
        static const int XM_END_OF_SESSION = 2180;
        static const int IDLY_LABELLING = 2190;
        static const int IDLY_RESET_LABELLING = 2200;
        static const int EM_DRIFT_CORRECTION = 2210;
        static const int ARTIFACT_REJECTED = 2220;
        static const int PLAY_SOUND = 2230;
        static const int WAM_FEEDBACK = 2240;
        static const int WAM_HAND_FEEDBACK = 2242;
        static const int IDLE = 2250;
        static const int IDLE_DETECTION_ENDED = 2251;
        static const int PLANNER_CONTROL_CONFIG = 2260;
        static const int ROBOT_JOINT_COMMAND = 2270;
        static const int IDLEGATED_MOVEMENT_COMMAND = 2280;
        static const int XM_ABORT_SESSION = 171;
        static const int PROCEED_TO_Failure = 196;
        static const int PROCEED_TO_NextState = 198;
        static const int PAUSE_EXPERIMENT = 180;
        static const int RESUME_EXPERIMENT = 181;
        static const int TRIAL_EVENT = 100;
        static const int TRIAL_CONFIG = 101;
        static const int TRIAL_STATUS = 102;
        static const int WASHING_WITH_MONKEYS = 133;
        static const int LICKING_BEGIN = 150;
        static const int LICKING_END = 151;
        static const int ROBOT_ACTUAL_STATE = 934;
        static const int ROBOT_CONTROL_STATE = 935;
        static const int ROBOT_CONTROL_SPACE_ACTUAL_STATE = 936;
        static const int GRASP_EVENT = 937;
        static const int ROBOT_CONTROL_CONFIG = 938;
        static const int GIVE_REWARD = 600;
        static const int IO_START_STREAM = 601;
        static const int IO_STOP_STREAM = 602;
        static const int JOYPAD_R1 = 610;
        static const int JOYPAD_R2 = 611;
        static const int JOYPAD_X = 612;
        static const int JOYPAD_PAD_BUTTON = 613;
        static const int READY_BUTTON = 614;
        static const int ANALOG_STREAM = 620;
        static const int IO_STREAM_STARTED = 621;
        static const int IO_STREAM_STOPPED = 622;
        static const int KNOB_TOUCHED = 640;
        static const int KNOB_TURNED = 641;
        static const int KNOB_ANTI_TURNED = 642;
        static const int KNOB_OVER_TURNED = 643;
        static const int DOOR_MOVED = 644;
        static const int DOOR_OPENED = 645;
        static const int DOOR_ANTI_OPENED = 646;
        static const int DOOR_OVER_OPENED = 647;
        static const int KNOB_MOVED = 648;
        static const int DOOR_UN_OPENED = 649;
        static const int KNOB_RELEASED = 650;
        static const int PAD_PRESSED = 660;
        static const int PAD_STEADY = 661;
        static const int PAD_PERTURBED = 662;
        static const int PAD_RELEASED = 663;
        static const int DENSO_CONFIG = 800;
        static const int DENSO_INITIALIZE = 801;
        static const int DENSO_MOVE = 802;
        static const int DENSO_HALT = 803;
        static const int DENSO_SET_SPEED = 804;
        static const int DENSO_WIGGLE = 806;
        static const int DENSO_MOVE_CONTINUE = 807;
        static const int DENSO_READY = 850;
        static const int DENSO_NOT_READY = 851;
        static const int DENSO_MOVE_COMPLETE = 852;
        static const int DENSO_MOVE_FAILED = 853;
        static const int DENSO_MOVE_INVALID = 854;
        static const int DENSO_HALTED = 855;
        static const int KILL_KILL_KILL_EM = 300;
        static const int EM_MOVEMENT_COMMAND = 350;
        static const int EM_AUX_MOVEMENT_COMMAND = 355;
        static const int COMPOSITE_MOVEMENT_COMMAND = 366;
        static const int ROBOT_MOVEMENT_COMMAND = 351;
        static const int PLANNER_MOVEMENT_COMMAND = 352;
        static const int PLANNER_STATE = 353;
        static const int PLAN_PROCESSOR_STATE = 354;
        static const int FM_MOVEMENT_COMMAND = 430;
        static const int OVERRIDE_COMMAND = 480;
        static const int JVEL_COMMAND = 481;
        static const int COMPONENT_DELAY_MSG_TYPES = 200;
        static const int ESTIMATED_DELAY = 201;
        static const int MEASURED_DELAY = 202;
        static const int NOOP = 998;
        static const int KEYBOARD = 1002;
        static const int CLEAR_FUNCTION = 1003;
        static const int LATE_ADAPT_NOW = 1005;
        static const int DUMMY_MESSAGE = 2000;
        static const int TARG_CLOUD = 1006;
        static const int ATTENTION = 1659;
    };

    ref class MID
    {
    public:
        static const int MESSAGE_MANAGER = 0;
        static const int COMMAND_MODULE = 1;
        static const int APPLICATION_MODULE = 2;
        static const int NETWORK_RELAY = 3;
        static const int STATUS_MODULE = 4;
        static const int QUICKLOGGER = 5;
        static const int EXEC_MOD = 10;
        static const int SPM_MOD = 20;
        static const int SPM_MOD1 = 21;
        static const int SPM_MOD2 = 22;
        static const int SPM_MOD3 = 23;
        static const int SPM_MOD4 = 24;
        static const int IO_MOD = 60;
        static const int DENSO_MOD = 80;
        static const int DENSO_TRY = 81;
        static const int WATCHDOG = 97;
        static const int SILICON_MONKEY = 72;
        static const int WAM = 73;
        static const int OPTOTRAK = 74;
        static const int SIMPLE_PLANNER = 76;
        static const int EXTRACTION_MOD = 50;
        static const int VIZ = 85;
        static const int HANDY_DANDY = 86;
        static const int DRIFTY = 93;
        static const int THE_DECIDER = 94;
        static const int PS3_COMMAND_MODULE = 95;
        static const int PS3_RAW_MODULE = 96;
        static const int SILICON_MONKEY_BRAIN = 91;
        static const int PS3_MODULE = 92;
        static const int TEST_MOD = 99;
        static const int GROBOT_RAW_FEEDBACK = 19;
        static const int GROBOT_FEEDBACK = 18;
        static const int DIGITAL_IO = 17;
        static const int TASK_JUDGE = 16;
        static const int SI_MOVEMENT = 15;
        static const int INPUT_TRANSFORM = 14;
        static const int SIMPLE_ARBITRATOR = 13;
        static const int OUTPUT_TRANSFORM = 12;
        static const int FEEDBACK_TRANSFORM = 11;
        static const int SAMPLE_GENERATOR = 29;
        static const int VIRTUAL_FIXTURING = 28;
        static const int CANNED_MOVEMENT = 27;
        static const int HAND_VIZ = 30;
        static const int CALIBRATION = 37;
        static const int SSH_CONTROLLER = 35;
        static const int IDLE_DETECTOR = 38;
        static const int ARDUINO_IO = 39;
        static const int POSITION_CONTROLLER = 40;
        static const int JOINT_CONTROLLER = 42;
        static const int WAM_BHAND = 25;
        static const int EM_OVERRIDE_CONFIG = 31;
        static const int OPTO_MPL_CTRL = 32;
        static const int OBSTACLE_COURSE = 33;
        static const int SKELETON_CTRL = 34;
        static const int GROBOT_SEGMENT_PERCEPTS = 56;
        static const int CERESTIM_CONFIG = 57;
        static const int CERESTIM_CONTROL = 58;
        static const int COMMAND_SPACE_FEEDBACK_GUI = 89;
        static const int MESSAGE_WATCHER = 88;
    };

    ref class HID
    {
    public:
        static const int LOCAL_HOST = 0;
        static const int ALL_HOSTS = 32767;
        static const int MAIN_HOST = 1;
    };

    ref class MDF
    {
    public:
        ref class FAIL_SUBSCRIBE
        {
        public:
            static System::Int16 mod_id;
            static System::Int16 reserved;
            static System::Int32 msg_type;
        };

        ref class FAILED_MESSAGE
        {
        public:
            static System::Int16 dest_mod_id;
            static array<System::Int16> ^reserved = {0,0,0};
            static System::Double time_of_failure;
            ref class msg_header
            {
            public:
                static System::Int32 msg_type;
                static System::Int32 msg_count;
                static System::Double send_time;
                static System::Double recv_time;
                static System::Int16 src_host_id;
                static System::Int16 src_mod_id;
                static System::Int16 dest_host_id;
                static System::Int16 dest_mod_id;
                static System::Int32 num_data_bytes;
                static System::Int32 remaining_bytes;
                static System::Int32 is_dynamic;
                static System::Int32 reserved;
            };
        };

        static array<System::SByte> ^MM_ERROR;
        static array<System::SByte> ^MM_INFO;
        ref class CONNECT
        {
        public:
            static System::Int16 logger_status;
            static System::Int16 daemon_status;
        };

        static System::Int32 SUBSCRIBE;
        static System::Int32 UNSUBSCRIBE;
        static System::Int32 PAUSE_SUBSCRIPTION;
        static System::Int32 RESUME_SUBSCRIPTION;
        ref class FORCE_DISCONNECT
        {
        public:
            static System::Int32 mod_id;
        };

        ref class MODULE_READY
        {
        public:
            static System::Int32 pid;
        };

        static array<System::SByte> ^DYNAMIC_DD_READ_ERR;
        static array<System::SByte> ^DEBUG_TEXT;
        static array<System::SByte> ^START_APP;
        static array<System::SByte> ^STOP_APP;
        static array<System::SByte> ^RESTART_APP;
        static array<System::SByte> ^KILL_APP;
        static array<System::SByte> ^SLAVE_START_APP;
        ref class SLAVE_START_APP_ACK
        {
        public:
            static System::Int32 num_remote_hosts;
        };

        static array<System::SByte> ^SLAVE_STOP_APP;
        static array<System::SByte> ^SLAVE_KILL_APP;
        static array<System::SByte> ^SLAVE_RESTART_APP;
        static array<System::SByte> ^AM_ERROR;
        static array<System::SByte> ^FAIL_START_APP;
        static array<System::SByte> ^FAIL_STOP_APP;
        static array<System::SByte> ^FAIL_KILL_APP;
        static array<System::SByte> ^AM_CONFIG_FILE_DATA;
        static array<System::SByte> ^AM_APP_NAME;
        static array<System::SByte> ^SLAVE_FAIL_START_APP;
        static array<System::SByte> ^SLAVE_AM_ERROR;
        static array<System::SByte> ^APP_ERROR;
        ref class TIMER_EXPIRED
        {
        public:
            static System::Int32 timer_id;
        };

        ref class TIMED_OUT
        {
        public:
            static System::Int32 timer_id;
        };

        ref class SET_TIMER_FAILED
        {
        public:
            static System::Int16 mod_id;
            static System::Int32 timer_id;
            static System::Int32 snooze_time;
        };

        ref class SET_TIMER
        {
        public:
            static System::Int32 timer_id;
            static System::Int32 snooze_time;
        };

        ref class CANCEL_TIMER
        {
        public:
            static System::Int32 timer_id;
        };

        ref class SAVE_MESSAGE_LOG
        {
        public:
            static array<System::SByte> ^pathname = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 pathname_length;
        };

        ref class TIMING_TEST
        {
        public:
            static array<System::Double> ^time = {0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PS3_BUTTON_PRESS
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 val;
            static System::Int32 controllerId;
            static array<System::Int32> ^buttonMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^buttonVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelMask = {0,0};
            static System::Int32 spacer;
            static array<System::Double> ^accelVal = {0,0};
        };

        ref class PS3_BUTTON_RELEASE
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 val;
            static System::Int32 controllerId;
            static array<System::Int32> ^buttonMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^buttonVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelMask = {0,0};
            static System::Int32 spacer;
            static array<System::Double> ^accelVal = {0,0};
        };

        ref class PS3_RAW_CONFIG
        {
        public:
            static array<System::Int32> ^stickCommandDOFMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^stickCommandJointMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickScale = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickOffset = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^accelScale = {0,0};
            static array<System::Double> ^accelOffset = {0,0};
            static array<System::Double> ^DOFscale = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelDOFMap = {0,0};
            static array<System::Int32> ^use_controller = {0,0,0,0,0,0,0,0,0,0};
            static System::Int32 free_run;
            static System::Int32 spacer;
        };

        ref class PS3_SIMPLE_BUTTON_PRESS
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 controllerId;
        };

        ref class PS3_SIMPLE_BUTTON_RELEASE
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 controllerId;
        };

        ref class PS3_GENERIC_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Int32 controllerId;
            static System::Int32 spacer;
            static array<System::Double> ^dof_vals = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_START_SESSION
        {
        public:
            static array<System::Double> ^Dimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class RELOAD_CONFIGURATION
        {
        public:
            static array<System::Double> ^Dimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_RESET_AGGREGATION
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_RESUME_COLLECTION
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_AGGREGATE_DATA_NOW
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_PAUSE_COLLECTION
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_RESET_STATE
        {
        public:
            static array<System::Double> ^initial_position = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^initial_velocity = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^target_position = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 reset_history;
            static System::Int32 reserved;
        };

        ref class EM_START_TRIAL
        {
        public:
            static System::Int32 data_index;
            static System::Int32 reserved;
        };

        ref class EM_ADAPT_NOW
        {
        public:
            static System::Int32 first_data_index;
            static System::Int32 last_data_index;
        };

        ref class EM_UPDATE_DRIFT_CORRECTION
        {
        public:
            static array<System::Double> ^drift_correction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        static System::Double EM_MOD_DEPTH_CUTOFF;
        static array<System::SByte> ^EM_SET_PDS;
        static array<System::SByte> ^EM_PDS;
        ref class PVA_CONFIG
        {
        public:
            static array<System::Double> ^Norm2RealFactor = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double ModDepthCutoff;
            static System::Double RSquaredCutoff;
            static array<System::Double> ^PredictFRFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^AdaptFRFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^TargetFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^RegressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^ControlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double numAdaptReps;
        };

        ref class PVA_STATE
        {
        public:
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^PV = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^usedIndices = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PVA_ATTENUATE_COMMAND
        {
        public:
            static array<System::SByte> ^targTag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^attenuationLevel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class RAW_SPIKECOUNT
        {
        public:
            static System::Int32 source_index;
            static System::Int32 reserved;
            static System::Double source_timestamp;
            static System::Double count_interval;
            static array<System::Byte> ^counts = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class SPM_SPIKECOUNT
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double source_timestamp;
            static System::Double count_interval;
            static array<System::Byte> ^counts = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class SAMPLE_GENERATED
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double source_timestamp;
        };

        ref class SAMPLE_RESPONSE
        {
        public:
            static System::Double sample_response_timestamp;
            static System::Double sample_alignment_timestamp;
            static System::UInt32 sample_response_count;
            static System::UInt32 sample_alignment_count;
        };

        ref class INPUT_DOF_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^dof_vals = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class OPERATOR_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class FIXTURED_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class SHADOW_COMPOSITE_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class FIXTURED_COMPOSITE_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PROBOT_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^tool_pos = {0,0,0,0,0,0,0};
            static array<System::Double> ^wrist_pos = {0,0,0,0,0,0,0};
        };

        ref class GROBOT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^command = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 mode;
            static System::Int32 reserved;
        };

        ref class GROBOT_BYPASS
        {
        public:
            static array<System::Double> ^command = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 mode;
            static System::Int32 reserved;
        };

        ref class OPTO_CNTRL_CMD
        {
        public:
            static array<System::Double> ^Cmd = {0,0,0,0,0,0};
        };

        ref class OPTO_POS_CMD
        {
        public:
            static array<System::Double> ^Cmd = {0,0,0,0};
        };

        ref class KIN_POS_CMD
        {
        public:
            static array<System::Double> ^Cmd = {0,0,0,0};
        };

        ref class KINECT_SKELETON
        {
        public:
            static array<System::Double> ^x = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^y = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^z = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^w = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 Which;
            static System::Int32 Reserved;
        };

        ref class GROBOT_SEGMENT_PERCEPTS
        {
        public:
            static array<System::Double> ^ind_force = {0,0,0};
            static array<System::Double> ^mid_force = {0,0,0};
            static array<System::Double> ^rng_force = {0,0,0};
            static array<System::Double> ^lit_force = {0,0,0};
            static array<System::Double> ^thb_force = {0,0,0};
            static array<System::Double> ^ind_accel = {0,0,0};
            static array<System::Double> ^mid_accel = {0,0,0};
            static array<System::Double> ^rng_accel = {0,0,0};
            static array<System::Double> ^lit_accel = {0,0,0};
            static array<System::Double> ^thb_accel = {0,0,0};
        };

        ref class CERESTIM_CONFIG_MODULE
        {
        public:
            static System::Int32 configID;
            static System::Int32 afcf;
            static System::Double pulses;
            static System::Double amp1;
            static System::Double amp2;
            static System::Double width1;
            static System::Double width2;
            static System::Double frequency;
            static System::Double interphase;
        };

        ref class CERESTIM_CONFIG_CHAN
        {
        public:
            static System::Int32 stop;
            static System::Int32 group_stimulus;
            static System::Int32 group_numChans;
            static array<System::Int32> ^group_channel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^group_pattern = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 manual_stimulus;
            static System::Int32 manual_channel;
            static System::Int32 manual_pattern;
        };

        ref class GROBOT_RAW_FEEDBACK
        {
        public:
            static array<System::Double> ^j_ang = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^j_vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^j_trq = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class GROBOT_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^position = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^velocity = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^force = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^cori_matrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class SESSION_CONFIG
        {
        public:
            static array<System::SByte> ^data_dir = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class GLOVE_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MICROSTRAIN_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_OVERRIDE_CONFIG
        {
        public:
            static array<System::Int32> ^chosen_channel_mask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class CHANGE_TOOL
        {
        public:
            static System::Int32 next_tool_id;
            static System::Int32 reserved;
        };

        ref class CHANGE_TOOL_COMPLETE
        {
        public:
            static System::Int32 tool_id;
            static System::Int32 reserved;
        };

        ref class TASK_STATE_CONFIG
        {
        public:
            static System::Int32 id;
            static System::Int32 rep_num;
            static System::Int32 use_for_calib;
            static System::Int32 target_combo_index;
            static System::Int32 timed_out_conseq;
            static System::Int32 idle_gateable;
            static System::Int32 reach_offset;
            static System::Int32 relax_arm;
            static System::Double idle_timeout;
            static System::Double ts_time;
            static array<System::Double> ^target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^coriMatrix = {0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^idle_target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double trans_threshold;
            static System::Double ori_threshold;
            static System::Double trans_threshold_f;
            static System::Double ori_threshold_f;
            static array<System::Double> ^finger_threshold = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^finger_threshold_judging_method = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^finger_threshold_judging_polarity = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 trans_threshold_judging_polarity;
            static System::Int32 ori_threshold_judging_polarity;
            static System::Int32 trans_threshold_f_judging_polarity;
            static System::Int32 ori_threshold_f_judging_polarity;
            static System::Double timeout;
            static array<System::SByte> ^tags = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class JUDGE_VERDICT
        {
        public:
            static System::Int32 id;
            static System::Int32 reserved;
            static array<System::SByte> ^reason = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class END_TASK_STATE
        {
        public:
            static System::Int32 id;
            static System::Int32 outcome;
            static array<System::SByte> ^reason = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class RAW_SAMPLE_RESPONSE
        {
        public:
            static System::Int32 source_index;
            static System::Int32 reserved;
            static System::Double source_timestamp;
        };

        ref class CODE_VERSION
        {
        public:
            static array<System::SByte> ^module_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^version = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class SPM_FIRINGRATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double source_timestamp;
            static System::Double count_interval;
            static array<System::Double> ^rates = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        static array<System::Byte> ^EM_DECODER_CONFIGURATION;
        ref class LOAD_DECODER_CONFIG
        {
        public:
            static array<System::SByte> ^full_path = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class XM_START_SESSION
        {
        public:
            static System::Int32 load_calibration;
            static System::Int32 calib_session_id;
            static System::Int32 num_reps;
            static System::Int32 reserved;
            static array<System::SByte> ^subject_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PING
        {
        public:
            static array<System::SByte> ^module_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PING_ACK
        {
        public:
            static array<System::SByte> ^module_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class DEBUG_VECTOR
        {
        public:
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class APP_START
        {
        public:
            static array<System::SByte> ^config = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MODULE_START
        {
        public:
            static array<System::SByte> ^module = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class SPM_SPIKE_SNIPPET
        {
        public:
            static System::Double time;
            static System::Int32 chan;
            static System::Int32 unit;
            static System::Int32 box_id;
            static System::Int32 length;
            static array<System::Int16> ^snippet = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class SPM_SPIKE_TIMES
        {
        public:
            static array<System::Double> ^time = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int16> ^chan = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^unit = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^box_id = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class IDLY_LABELLING
        {
        public:
            static System::Int32 state;
            static System::Int32 reserved;
        };

        ref class EM_DRIFT_CORRECTION
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^drift_correction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class DENSO_WIGGLE
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 num_cycles;
            static array<System::Int32> ^sequence = {0,0,0,0,0,0,0,0};
            static array<System::Double> ^amplitude = {0,0,0};
        };

        ref class PLAY_SOUND
        {
        public:
            static System::Int32 id;
            static System::Int32 reserved;
        };

        ref class ARTIFACT_REJECTED
        {
        public:
            static System::Double time;
        };

        ref class IDLE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double score;
            static System::Double gain;
            static System::Int32 idle;
            static System::Int32 reserved;
        };

        ref class WAM_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^CoriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class WAM_HAND_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^CoriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class PLANNER_CONTROL_CONFIG
        {
        public:
            static array<System::Double> ^target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^coriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class ROBOT_JOINT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0};
            static array<System::Int32> ^overrideDims = {0,0,0,0,0,0,0,0};
        };

        ref class IDLEGATED_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class TRIAL_EVENT
        {
        public:
            static System::Double event_time;
            static System::Int32 event_code;
            static System::Int32 reserved;
        };

        ref class TRIAL_CONFIG
        {
        public:
            static System::Int32 rep_no;
            static System::Int32 trial_no;
            static System::Int32 num_reward_states;
            static System::Int32 reserved;
        };

        ref class TRIAL_STATUS
        {
        public:
            static System::Int32 success;
            static System::Int32 reserved;
        };

        ref class ROBOT_ACTUAL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^Jpos = {0,0,0,0,0,0,0};
            static array<System::Double> ^Jvel = {0,0,0,0,0,0,0};
            static array<System::Double> ^Cpos = {0,0,0};
            static array<System::Double> ^Cori = {0,0,0};
            static array<System::Double> ^Cforce = {0,0,0};
            static array<System::Double> ^Ctrq = {0,0,0};
            static array<System::Double> ^Cvel = {0,0,0};
            static array<System::Double> ^CangVel = {0,0,0};
            static array<System::Double> ^Hpos = {0,0,0,0};
            static array<System::Double> ^Hstrain = {0,0,0,0};
            static array<System::Double> ^Jtrq = {0,0,0};
        };

        ref class ROBOT_CONTROL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            ref class autoControl
            {
            public:
                ref class sample_header
                {
                public:
                    static System::Int32 SerialNo;
                    static System::Int32 Flags;
                    static System::Double DeltaTime;
                };
                static array<System::Double> ^targetPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            };
            ref class overrideCommand
            {
            public:
                static array<System::Double> ^DOFCommand = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^JposCommand = {0,0,0,0,0,0,0};
                static System::Int32 controllerId;
                static System::Int32 j0nks;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^actualControlPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^actualControlVel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoControlPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoControlVel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoPosControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoVelControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthPosImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthVelImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^intrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^intrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^overrideDimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::UInt32 actualCommandComposition;
            static System::Int32 blank;
        };

        ref class ROBOT_CONTROL_SPACE_ACTUAL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^CoriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class ROBOT_CONTROL_CONFIG
        {
        public:
            static array<System::Double> ^target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^coriMatrix = {0,0,0,0,0,0,0,0,0};
            ref class trialEvent
            {
            public:
                static System::Double event_time;
                static System::Int32 event_code;
                static System::Int32 reserved;
            };
            ref class autoControlParams
            {
            public:
                static array<System::Double> ^virtualPadPosition = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^centralPointPosition = {0,0,0};
                static array<System::Double> ^posMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^posMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^velMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^velMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static System::Double graspingGraspApertureTarget;
                static System::Double graspingOpenApertureTarget;
                static System::Double graspingIntermediateApertureTarget;
                static System::Double maxApproachSwingAngle;
                static System::Double graspTooCloseIfClosedRadius;
            };
            static array<System::Double> ^autoPosControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoVelControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthPosImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthVelImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^importantDOF = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class GIVE_REWARD
        {
        public:
            static System::Double duration_ms;
            static System::Double num_clicks;
        };

        ref class IO_START_STREAM
        {
        public:
            ref class limits
            {
            public:
                static array<System::Double> ^high = {0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^low = {0,0,0,0,0,0,0,0,0,0,0,0};
            };
            static System::Int32 reserved;
            static System::Int32 internal_sampling;
            static System::Double sample_interval;
        };

        ref class ANALOG_STREAM
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class KNOB_TOUCHED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class KNOB_TURNED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class KNOB_ANTI_TURNED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class KNOB_OVER_TURNED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class DOOR_MOVED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class DOOR_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class DOOR_ANTI_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class DOOR_OVER_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class KNOB_MOVED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class DOOR_UN_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class KNOB_RELEASED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class PAD_PRESSED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class PAD_STEADY
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class PAD_PERTURBED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class PAD_RELEASED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class DENSO_MOVE
        {
        public:
            static System::Int32 position_no;
            static System::Int32 movement_id;
        };

        ref class DENSO_SET_SPEED
        {
        public:
            static System::Double speed;
        };

        ref class DENSO_MOVE_CONTINUE
        {
        public:
            static System::Int32 position_no;
            static System::Int32 movement_id;
        };

        static array<System::SByte> ^DENSO_NOT_READY;
        ref class DENSO_MOVE_COMPLETE
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class DENSO_MOVE_FAILED
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class DENSO_MOVE_INVALID
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class DENSO_HALTED
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class EM_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_AUX_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class COMPOSITE_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class ROBOT_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PLANNER_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PLANNER_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^targetPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PLAN_PROCESSOR_STATE
        {
        public:
            static array<System::Double> ^D = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class FM_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class OVERRIDE_COMMAND
        {
        public:
            static array<System::Double> ^DOFCommand = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^JposCommand = {0,0,0,0,0,0,0};
            static System::Int32 controllerId;
            static System::Int32 j0nks;
        };

        ref class JVEL_COMMAND
        {
        public:
            static array<System::Double> ^cmd = {0,0,0,0,0,0,0,0,0,0,0};
        };

        static array<System::Int32> ^COMPONENT_DELAY_MSG_TYPES = {0,0,0,0,0,0};
        ref class ESTIMATED_DELAY
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^Components = {0,0,0,0,0,0};
            static System::Double Total;
        };

        ref class MEASURED_DELAY
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^Components = {0,0,0,0,0,0};
            static System::Double Total;
        };

        static array<System::SByte> ^CLEAR_FUNCTION;
        ref class TARG_CLOUD
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^cloud = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 nTargs;
            static System::Int32 spacer;
        };

        static System::Double ATTENTION;
    };

    ref class MESSAGE_HEADER
    {
    public:
        static System::Int32 msg_type;
        static System::Int32 msg_count;
        static System::Double send_time;
        static System::Double recv_time;
        static System::Int16 src_host_id;
        static System::Int16 src_mod_id;
        static System::Int16 dest_host_id;
        static System::Int16 dest_mod_id;
        static System::Int32 num_data_bytes;
        static System::Int32 remaining_bytes;
        static System::Int32 is_dynamic;
        static System::Int32 reserved;
    };

    ref class defines
    {
    public:
        static const int MAX_MODULES = 200;
        static const int DYN_MOD_ID_START = 100;
        static const int MAX_HOSTS = 5;
        static const int MAX_MESSAGE_TYPES = 10000;
        static const int MIN_STREAM_TYPE = 9000;
        static const int MAX_TIMERS = 100;
        static const int MAX_INTERNAL_TIMERS = 20;
        static const int MAX_DRAGONFLY_MSG_TYPE = 99;
        static const int MAX_DRAGONFLY_MODULE_ID = 9;
        static const char DF_MSG_HEADER_FIELDS[] = "MSG_TYPE	msg_type; 	MSG_COUNT	msg_count; 	double	send_time; 	double	recv_time; 	HOST_ID		src_host_id; 	MODULE_ID	src_mod_id; 	HOST_ID		dest_host_id; 	MODULE_ID	dest_mod_id; 	int			num_data_bytes; 	int			remaining_bytes; 	int			is_dynamic; 	int			reserved";
        static const int MAX_CONTIGUOUS_MESSAGE_DATA = 9000;
        static const int MID_MESSAGE_MANAGER = 0;
        static const int MID_COMMAND_MODULE = 1;
        static const int MID_APPLICATION_MODULE = 2;
        static const int MID_NETWORK_RELAY = 3;
        static const int MID_STATUS_MODULE = 4;
        static const int MID_QUICKLOGGER = 5;
        static const int HID_LOCAL_HOST = 0;
        static const int HID_ALL_HOSTS = 32767;
        static const int ALL_MESSAGE_TYPES = 2147483647;
        static const int MT_EXIT = 0;
        static const int MT_KILL = 1;
        static const int MT_ACKNOWLEDGE = 2;
        static const int MT_FAIL_SUBSCRIBE = 6;
        static const int MT_FAILED_MESSAGE = 7;
        static const int MT_MM_ERROR = 83;
        static const int MT_MM_INFO = 84;
        static const int MT_CONNECT = 13;
        static const int MT_DISCONNECT = 14;
        static const int MT_SUBSCRIBE = 15;
        static const int MT_UNSUBSCRIBE = 16;
        static const int MT_PAUSE_SUBSCRIPTION = 85;
        static const int MT_RESUME_SUBSCRIPTION = 86;
        static const int MT_SHUTDOWN_DRAGONFLY = 17;
        static const int MT_SHUTDOWN_APP = 18;
        static const int MT_FORCE_DISCONNECT = 82;
        static const int MT_CORE_MODULE_REINIT_ACK = 25;
        static const int MT_MODULE_READY = 26;
        static const int MT_DYNAMIC_DD_READ_ERR = 90;
        static const int MT_DEBUG_TEXT = 91;
        static const int MT_AM_EXIT = 30;
        static const int MT_START_APP = 31;
        static const int MT_STOP_APP = 32;
        static const int MT_RESTART_APP = 33;
        static const int MT_KILL_APP = 34;
        static const int MT_AM_RE_READ_CONFIG_FILE = 89;
        static const int MT_AM_GET_APP_NAME = 92;
        static const int MT_SLAVE_START_APP = 64;
        static const int MT_SLAVE_START_APP_ACK = 65;
        static const int MT_SLAVE_STOP_APP = 66;
        static const int MT_SLAVE_KILL_APP = 67;
        static const int MT_SLAVE_RESTART_APP = 68;
        static const int MT_AM_ERROR = 35;
        static const int MT_AM_ACKNOWLEDGE = 36;
        static const int MT_FAIL_START_APP = 37;
        static const int MT_FAIL_STOP_APP = 38;
        static const int MT_FAIL_KILL_APP = 39;
        static const int MT_APP_START_COMPLETE = 2121;
        static const int MT_APP_SHUTODWN_COMPLETE = 41;
        static const int MT_APP_RESTART_COMPLETE = 42;
        static const int MT_APP_KILL_COMPLETE = 43;
        static const int MT_ALL_MODULES_READY = 44;
        static const int MT_CORE_MODULE_REINIT = 45;
        static const int MT_AM_CONFIG_FILE_DATA = 46;
        static const int MT_AM_APP_NAME = 93;
        static const int MT_SLAVE_ALL_MODULES_READY = 69;
        static const int MT_SLAVE_FAIL_START_APP = 70;
        static const int MT_SLAVE_FAIL_STOP_APP = 71;
        static const int MT_SLAVE_FAIL_KILL_APP = 72;
        static const int MT_SLAVE_APP_SHUTODWN_COMPLETE = 74;
        static const int MT_SLAVE_APP_RESTART_COMPLETE = 75;
        static const int MT_SLAVE_APP_KILL_COMPLETE = 76;
        static const int MT_SLAVE_AM_ERROR = 77;
        static const int MT_APP_ERROR = 47;
        static const int MT_SM_EXIT = 48;
        static const int MT_CLOCK_SYNC = 49;
        static const int MT_TIMER_EXPIRED = 50;
        static const int MT_TIMED_OUT = 73;
        static const int MT_SET_TIMER_FAILED = 51;
        static const int MT_TM_EXIT = 52;
        static const int MT_SET_TIMER = 53;
        static const int MT_CANCEL_TIMER = 54;
        static const int MT_LM_EXIT = 55;
        static const int MT_MM_READY = 94;
        static const int MT_LM_READY = 96;
        static const int MT_SAVE_MESSAGE_LOG = 56;
        static const int MAX_LOGGER_FILENAME_LENGTH = 256;
        static const int MT_MESSAGE_LOG_SAVED = 57;
        static const int MT_PAUSE_MESSAGE_LOGGING = 58;
        static const int MT_RESUME_MESSAGE_LOGGING = 59;
        static const int MT_RESET_MESSAGE_LOG = 60;
        static const int MT_DUMP_MESSAGE_LOG = 61;
        static const int MT_TIMING_TEST = 62;
        static const int MAX_TIMING_TEST_TIME_POINTS = 12;
        static const int HID_MAIN_HOST = 1;
        static const int MID_EXEC_MOD = 10;
        static const int MID_SPM_MOD = 20;
        static const int MID_SPM_MOD1 = 21;
        static const int MID_SPM_MOD2 = 22;
        static const int MID_SPM_MOD3 = 23;
        static const int MID_SPM_MOD4 = 24;
        static const int MID_IO_MOD = 60;
        static const int MID_DENSO_MOD = 80;
        static const int MID_DENSO_TRY = 81;
        static const int MID_WATCHDOG = 97;
        static const int MID_SILICON_MONKEY = 72;
        static const int MID_WAM = 73;
        static const int MID_OPTOTRAK = 74;
        static const int MID_SIMPLE_PLANNER = 76;
        static const int MID_EXTRACTION_MOD = 50;
        static const int MID_VIZ = 85;
        static const int MID_HANDY_DANDY = 86;
        static const int MID_DRIFTY = 93;
        static const int MID_THE_DECIDER = 94;
        static const int MID_PS3_COMMAND_MODULE = 95;
        static const int MID_PS3_RAW_MODULE = 96;
        static const int MID_SILICON_MONKEY_BRAIN = 91;
        static const int MID_PS3_MODULE = 92;
        static const int MID_TEST_MOD = 99;
        static const char check_flag_bits[] = "( A, bitmask)  (((A) & (bitmask)) == (bitmask))";
        static const char clear_flag_bits[] = "( A, bitmask)  ((A) &= ~(bitmask))";
        static const char set_flag_bits[] = "( A, bitmask)    ((A) |= (bitmask))";
        static const int SF_ALIGNMENT = 1;
        static const int SF_UNFREEZE = 2;
        static const int SF_IRREGULAR = 4;
        static const int SF_FRACTINT = 8;
        static const int MAX_CONTROL_DIMS = 18;
        static const int MAX_EM_DIMS = 18;
        static const int TAG_LENGTH = 64;
        static const int NUM_D_COLS = 16;
        static const int MAX_D_COLS = 32;
        static const int MAX_INPUT_DOFS = 21;
        static const int MAX_FILENAME_LENGTH = 256;
        static const int PS3_B_L1 = 10;
        static const int PS3_B_L2 = 8;
        static const int PS3_B_R1 = 11;
        static const int PS3_B_R2 = 9;
        static const int PS3_B_LDIR = 7;
        static const int PS3_B_RDIR = 5;
        static const int PS3_B_UDIR = 4;
        static const int PS3_B_DDIR = 6;
        static const int PS3_B_TRIANGLE = 12;
        static const int PS3_B_SQUARE = 15;
        static const int PS3_B_CIRCLE = 13;
        static const int PS3_B_X = 14;
        static const int PS3_B_SELECT = 0;
        static const int PS3_B_START = 3;
        static const int PS3_B_L3 = 1;
        static const int PS3_B_R3 = 2;
        static const int PS3_C_LSTICKH = 0;
        static const int PS3_C_LSTICKV = 1;
        static const int PS3_C_RSTICKH = 2;
        static const int PS3_C_RSTICKV = 3;
        static const int PS3_C_L1 = 14;
        static const int PS3_C_L2 = 12;
        static const int PS3_C_R1 = 15;
        static const int PS3_C_R2 = 13;
        static const int PS3_C_LDIR = 11;
        static const int PS3_C_RDIR = 9;
        static const int PS3_C_UDIR = 8;
        static const int PS3_C_DDIR = 10;
        static const int PS3_C_TRIANGLE = 16;
        static const int PS3_C_SQUARE = 19;
        static const int PS3_C_CIRCLE = 17;
        static const int PS3_C_X = 18;
        static const int PS3_N_SENSORS = 21;
        static const int PS3_N_ACCEL = 2;
        static const int BUTTON_PRESS = 2135;
        static const int BUTTON_RELEASE = 2136;
        static const int STICK_READING = 2137;
        static const int MT_PS3_BUTTON_PRESS = 2135;
        static const int MT_PS3_BUTTON_RELEASE = 2136;
        static const int MT_PS3_STICK_READING = 2137;
        static const double DOF_SCALE = 0.3;
        static const double JOINT_SCALE = 0.3;
        static const int MAX_CONTROLLERS = 10;
        static const int MT_PS3_RAW_CONFIG = 6543;
        static const int MT_PS3_SIMPLE_BUTTON_PRESS = 6544;
        static const int MT_PS3_SIMPLE_BUTTON_RELEASE = 6545;
        static const int MT_PS3_GENERIC_DATA = 6546;
        static const int MAX_REDUCED_SPIKE_CHANS = 200;
        static const int MAX_EM_DIMENSIONS = 18;
        static const int MT_EM_START_SESSION = 1600;
        static const int MT_EM_END_SESSION = 1601;
        static const int MT_EM_FREEZE = 1602;
        static const int MT_EM_RESET_STATE = 1603;
        static const int MT_EM_UNFREEZE = 1604;
        static const int MT_EM_START_TRIAL = 1605;
        static const int MT_EM_END_TRIAL = 1606;
        static const int MT_EM_DISCARD_TRIAL = 1607;
        static const int MT_EM_ADAPT_NOW = 1608;
        static const int MT_EM_FEEDBACK = 1609;
        static const int MT_EM_MOD_DEPTH_CUTOFF = 1610;
        static const int MT_EM_PAUSE_COLLECTION = 1611;
        static const int MT_EM_RESUME_COLLECTION = 1612;
        static const int MT_EM_GET_PDS = 1613;
        static const int MT_EM_SET_PDS = 1614;
        static const int MT_EM_AGGREGATE_DATA_NOW = 1615;
        static const int MT_EM_RESET_AGGREGATION = 1616;
        static const int MT_EM_CORRECT_DRIFT_NOW = 1617;
        static const int MT_EM_UPDATE_DRIFT_CORRECTION = 1618;
        static const int MT_RELOAD_PVA_CONFIG = 1619;
        static const int MT_EM_READY = 1650;
        static const int MT_EM_FROZEN = 1651;
        static const int MT_EM_ADAPT_DONE = 1652;
        static const int MT_EM_ADAPT_FAILED = 1653;
        static const int MT_EM_MOD_DEPTH_FAILED = 1654;
        static const int MT_EM_MOD_DEPTH_SUCCEEDED = 1655;
        static const int MT_EM_PDS = 1656;
        static const int MT_EM_ALREADY_FROZEN = 1657;
        static const int MT_EM_DRIFT_CORRECTED = 1658;
        static const int MT_RELOAD_CONFIGURATION = 1004;
        static const int MT_PVA_CONFIG = 382;
        static const int MT_PVA_STATE = 383;
        static const int MT_DECISION = 384;
        static const int MT_TRAINING_BEGIN = 385;
        static const int MT_DO_IT_DECIDER = 386;
        static const int MT_PVA_ATTENUATE_COMMAND = 387;
        static const int MAX_SPIKE_SOURCES = 3;
        static const int MAX_SPIKE_CHANS_PER_SOURCE = 96;
        static const int MAX_UNITS_PER_CHAN = 6;
        static const int MAX_TOTAL_SPIKE_CHANS_PER_SOURCE = 576;
        static const int MAX_TOTAL_SPIKE_CHANS = 1728;
        static const int RAW_COUNTS_PER_SAMPLE = 2;
        static const int MSEC_PER_RAW_SAMPLE = 10;
        static const double SAMPLE_DT = 0.02;
        static const int MID_GROBOT_RAW_FEEDBACK = 19;
        static const int MID_GROBOT_FEEDBACK = 18;
        static const int MID_DIGITAL_IO = 17;
        static const int MID_TASK_JUDGE = 16;
        static const int MID_SI_MOVEMENT = 15;
        static const int MID_INPUT_TRANSFORM = 14;
        static const int MID_SIMPLE_ARBITRATOR = 13;
        static const int MID_OUTPUT_TRANSFORM = 12;
        static const int MID_FEEDBACK_TRANSFORM = 11;
        static const int MID_SAMPLE_GENERATOR = 29;
        static const int MID_VIRTUAL_FIXTURING = 28;
        static const int MID_CANNED_MOVEMENT = 27;
        static const int MID_HAND_VIZ = 30;
        static const int MID_CALIBRATION = 37;
        static const int MID_SSH_CONTROLLER = 35;
        static const int MID_IDLE_DETECTOR = 38;
        static const int MID_ARDUINO_IO = 39;
        static const int MID_POSITION_CONTROLLER = 40;
        static const int MID_JOINT_CONTROLLER = 42;
        static const int MID_WAM_BHAND = 25;
        static const int MID_EM_OVERRIDE_CONFIG = 31;
        static const int MID_OPTO_MPL_CTRL = 32;
        static const int MID_OBSTACLE_COURSE = 33;
        static const int MID_SKELETON_CTRL = 34;
        static const int MID_GROBOT_SEGMENT_PERCEPTS = 56;
        static const int MID_CERESTIM_CONFIG = 57;
        static const int MID_CERESTIM_CONTROL = 58;
        static const int MID_COMMAND_SPACE_FEEDBACK_GUI = 89;
        static const int MID_MESSAGE_WATCHER = 88;
        static const int MT_GROBOT_SEGMENT_PERCEPTS = 1888;
        static const int MT_CERESTIM_CONFIG_MODULE = 1889;
        static const int MT_CERESTIM_CONFIG_CHAN = 1890;
        static const int MT_GROBOT_COMMAND = 1700;
        static const int MT_GROBOT_RAW_FEEDBACK = 1701;
        static const int MT_GROBOT_FEEDBACK = 1702;
        static const int MT_COMMANDSPACE_FEEDBACK = 1703;
        static const int MT_GROBOT_BYPASS = 1704;
        static const int MT_GROBOT_END_BYPASS = 1707;
        static const int MT_MICROSTRAIN_DATA = 1705;
        static const int MT_GLOVE_DATA = 1706;
        static const int MT_EM_OVERRIDE_CONFIG = 1708;
        static const int MT_OPTO_CNTRL_CMD = 1709;
        static const int MT_OPTO_POS_CMD = 1712;
        static const int MT_KIN_POS_CMD = 1713;
        static const int MT_KINECT_SKELETON = 1711;
        static const int MT_SESSION_CONFIG = 1710;
        static const int MT_RAW_SPIKECOUNT = 1750;
        static const int MT_SPM_SPIKECOUNT = 1751;
        static const int MT_SAMPLE_GENERATED = 1752;
        static const int MT_SAMPLE_RESPONSE = 1753;
        static const int MT_RESET_SAMPLE_ALIGNMENT = 1754;
        static const int MT_SYNCH_NOW = 1800;
        static const int MT_SYNCH_START = 1801;
        static const int MT_SYNCH_DONE = 1802;
        static const int MT_INPUT_DOF_DATA = 1850;
        static const int MT_OPERATOR_MOVEMENT_COMMAND = 1900;
        static const int MT_FIXTURED_MOVEMENT_COMMAND = 1910;
        static const int MT_SHADOW_COMPOSITE_MOVEMENT_COMMAND = 1919;
        static const int MT_FIXTURED_COMPOSITE_MOVEMENT_COMMAND = 1920;
        static const int MT_PROBOT_FEEDBACK = 1930;
        static const int MAX_PROBOT_FEEDBACK_DIMS = 7;
        static const int MT_CHANGE_TOOL = 1940;
        static const int MT_CHANGE_TOOL_INVALID = 1941;
        static const int MT_CHANGE_TOOL_COMPLETE = 1942;
        static const int MT_CHANGE_TOOL_FAILED = 1943;
        static const int MT_TASK_STATE_CONFIG = 1950;
        static const int MT_JUDGE_VERDICT = 1960;
        static const int MT_END_TASK_STATE = 1970;
        static const int MT_RAW_SAMPLE_RESPONSE = 1980;
        static const int MT_CODE_VERSION = 1990;
        static const int MT_TRIAL_DATA_SAVED = 2080;
        static const int MT_EM_DECODER_CONFIGURATION = 2090;
        static const int MT_SPM_FIRINGRATE = 2100;
        static const int MT_LOAD_DECODER_CONFIG = 2110;
        static const int MT_APP_START = 2120;
        static const int MT_MODULE_START = 2125;
        static const int MT_MODULE_START_COMPLETE = 2126;
        static const int MT_EXIT_ACK = 2130;
        static const int MT_PING = 2140;
        static const int MT_PING_ACK = 2141;
        static const int MT_XM_START_SESSION = 2150;
        static const int MT_DEBUG_VECTOR = 2160;
        static const int MT_SPM_SPIKE_SNIPPET = 2170;
        static const int MT_SPM_SPIKE_TIMES = 2171;
        static const int MT_XM_END_OF_SESSION = 2180;
        static const int MT_IDLY_LABELLING = 2190;
        static const int MT_IDLY_RESET_LABELLING = 2200;
        static const int MT_EM_DRIFT_CORRECTION = 2210;
        static const int MT_ARTIFACT_REJECTED = 2220;
        static const int MT_PLAY_SOUND = 2230;
        static const int MT_WAM_FEEDBACK = 2240;
        static const int MT_WAM_HAND_FEEDBACK = 2242;
        static const int MT_IDLE = 2250;
        static const int MT_IDLE_DETECTION_ENDED = 2251;
        static const int MT_PLANNER_CONTROL_CONFIG = 2260;
        static const int MT_ROBOT_JOINT_COMMAND = 2270;
        static const int MT_IDLEGATED_MOVEMENT_COMMAND = 2280;
        static const int MAX_GROBOT_JOINTS = 28;
        static const int MAX_GROBOT_COMMAND_DIMS = 18;
        static const int MAX_GROBOT_FEEDBACK_DIMS = 18;
        static const int MAX_OPTO_CTRL_JOINTS = 6;
        static const int MAX_OPTO_POS = 4;
        static const int MAX_KIN_POS = 4;
        static const int NUM_FINGER_DIMS = 10;
        static const int KINECT_JOINTS = 20;
        static const int MAX_JOINT_DIMS = 8;
        static const int MPL_AT_ARM_EPV_FING_JV = 0;
        static const int MPL_AT_ARM_EPV_FING_JP = 1;
        static const int MPL_AT_ARM_JV_FING_JP = 2;
        static const int MPL_AT_ALL_JV = 3;
        static const int MPL_AT_ALL_JP = 4;
        static const int MPL_AT_ARM_EPP_FING_JP = 5;
        static const int MAX_DATA_DIR_LEN = 128;
        static const int MAX_CYBER_GLOVE_DIMS = 30;
        static const int MAX_EM_CHANNELS = 1728;
        static const int MAX_FINGER_DIMS = 10;
        static const int MAX_PERCEPT_DIMS = 15;
        static const int MAX_HAND_DIMS = 25;
        static const int MAX_SPIKE_TIMES_PER_PACKET = 256;
        static const int MT_XM_ABORT_SESSION = 171;
        static const int MT_PROCEED_TO_Failure = 196;
        static const int MT_PROCEED_TO_NextState = 198;
        static const int MT_PAUSE_EXPERIMENT = 180;
        static const int MT_RESUME_EXPERIMENT = 181;
        static const int MT_TRIAL_EVENT = 100;
        static const int MT_TRIAL_CONFIG = 101;
        static const int MT_TRIAL_STATUS = 102;
        static const int MT_WASHING_WITH_MONKEYS = 133;
        static const int MT_LICKING_BEGIN = 150;
        static const int MT_LICKING_END = 151;
        static const int MT_ROBOT_ACTUAL_STATE = 934;
        static const int MT_ROBOT_CONTROL_STATE = 935;
        static const int MT_ROBOT_CONTROL_SPACE_ACTUAL_STATE = 936;
        static const int MT_GRASP_EVENT = 937;
        static const int MT_ROBOT_CONTROL_CONFIG = 938;
        static const int MT_GIVE_REWARD = 600;
        static const int NUM_ANALOG_STREAM_CHANS = 12;
        static const int ASC_MONKEY_KNOB = 0;
        static const int ASC_MONKEY_DOOR = 1;
        static const int ASC_ROBOT_KNOB = 2;
        static const int ASC_ROBOT_DOOR = 3;
        static const int ASC_ARMREST_LF = 4;
        static const int ASC_ARMREST_LB = 5;
        static const int ASC_ARMREST_RF = 6;
        static const int ASC_ARMREST_RB = 7;
        static const int ASC_JOYPAD_LEFT_UD = 8;
        static const int ASC_JOYPAD_LEFT_LR = 9;
        static const int ASC_JOYPAD_RIGHT_UD = 10;
        static const int ASC_JOYPAD_RIGHT_LR = 11;
        static const int MT_IO_START_STREAM = 601;
        static const int MT_IO_STOP_STREAM = 602;
        static const int MT_JOYPAD_R1 = 610;
        static const int MT_JOYPAD_R2 = 611;
        static const int MT_JOYPAD_X = 612;
        static const int MT_JOYPAD_PAD_BUTTON = 613;
        static const int MT_READY_BUTTON = 614;
        static const int MT_ANALOG_STREAM = 620;
        static const int MT_IO_STREAM_STARTED = 621;
        static const int MT_IO_STREAM_STOPPED = 622;
        static const int MT_KNOB_TOUCHED = 640;
        static const int MT_KNOB_TURNED = 641;
        static const int MT_KNOB_ANTI_TURNED = 642;
        static const int MT_KNOB_OVER_TURNED = 643;
        static const int MT_DOOR_MOVED = 644;
        static const int MT_DOOR_OPENED = 645;
        static const int MT_DOOR_ANTI_OPENED = 646;
        static const int MT_DOOR_OVER_OPENED = 647;
        static const int MT_KNOB_MOVED = 648;
        static const int MT_DOOR_UN_OPENED = 649;
        static const int MT_KNOB_RELEASED = 650;
        static const int MT_PAD_PRESSED = 660;
        static const int MT_PAD_STEADY = 661;
        static const int MT_PAD_PERTURBED = 662;
        static const int MT_PAD_RELEASED = 663;
        static const int MT_DENSO_CONFIG = 800;
        static const int MT_DENSO_INITIALIZE = 801;
        static const int MT_DENSO_MOVE = 802;
        static const int MT_DENSO_HALT = 803;
        static const int MT_DENSO_SET_SPEED = 804;
        static const int MT_DENSO_WIGGLE = 806;
        static const int MT_DENSO_MOVE_CONTINUE = 807;
        static const int MT_DENSO_READY = 850;
        static const int MT_DENSO_NOT_READY = 851;
        static const int MT_DENSO_MOVE_COMPLETE = 852;
        static const int MT_DENSO_MOVE_FAILED = 853;
        static const int MT_DENSO_MOVE_INVALID = 854;
        static const int MT_DENSO_HALTED = 855;
        static const int MT_KILL_KILL_KILL_EM = 300;
        static const int MT_EM_MOVEMENT_COMMAND = 350;
        static const int MT_EM_AUX_MOVEMENT_COMMAND = 355;
        static const int MT_COMPOSITE_MOVEMENT_COMMAND = 366;
        static const int MT_ROBOT_MOVEMENT_COMMAND = 351;
        static const int MT_PLANNER_MOVEMENT_COMMAND = 352;
        static const int MT_PLANNER_STATE = 353;
        static const int MT_PLAN_PROCESSOR_STATE = 354;
        static const int MT_FM_MOVEMENT_COMMAND = 430;
        static const int MT_OVERRIDE_COMMAND = 480;
        static const int MT_JVEL_COMMAND = 481;
        static const int NUM_COMPONENT_DELAYS = 6;
        static const int MT_COMPONENT_DELAY_MSG_TYPES = 200;
        static const int MT_ESTIMATED_DELAY = 201;
        static const int MT_MEASURED_DELAY = 202;
        static const int MT_NOOP = 998;
        static const int MT_KEYBOARD = 1002;
        static const int MT_CLEAR_FUNCTION = 1003;
        static const int MT_LATE_ADAPT_NOW = 1005;
        static const int MT_DUMMY_MESSAGE = 2000;
        static const int MT_TARG_CLOUD = 1006;
        static const int MT_ATTENTION = 1659;
    };

    ref class typedefs
    {
    public:
        static System::Int16 MODULE_ID;
        static System::Int16 HOST_ID;
        static System::Int32 MSG_TYPE;
        static System::Int32 MSG_COUNT;
        ref class DF_MSG_HEADER
        {
        public:
            static System::Int32 msg_type;
            static System::Int32 msg_count;
            static System::Double send_time;
            static System::Double recv_time;
            static System::Int16 src_host_id;
            static System::Int16 src_mod_id;
            static System::Int16 dest_host_id;
            static System::Int16 dest_mod_id;
            static System::Int32 num_data_bytes;
            static System::Int32 remaining_bytes;
            static System::Int32 is_dynamic;
            static System::Int32 reserved;
        };

        ref class DF_MESSAGE
        {
        public:
            static System::Int32 msg_type;
            static System::Int32 msg_count;
            static System::Double send_time;
            static System::Double recv_time;
            static System::Int16 src_host_id;
            static System::Int16 src_mod_id;
            static System::Int16 dest_host_id;
            static System::Int16 dest_mod_id;
            static System::Int32 num_data_bytes;
            static System::Int32 remaining_bytes;
            static System::Int32 is_dynamic;
            static System::Int32 reserved;
            static array<System::SByte> ^data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        static array<System::SByte> ^STRING_DATA;
        ref class MDF_FAIL_SUBSCRIBE
        {
        public:
            static System::Int16 mod_id;
            static System::Int16 reserved;
            static System::Int32 msg_type;
        };

        ref class MDF_FAILED_MESSAGE
        {
        public:
            static System::Int16 dest_mod_id;
            static array<System::Int16> ^reserved = {0,0,0};
            static System::Double time_of_failure;
            ref class msg_header
            {
            public:
                static System::Int32 msg_type;
                static System::Int32 msg_count;
                static System::Double send_time;
                static System::Double recv_time;
                static System::Int16 src_host_id;
                static System::Int16 src_mod_id;
                static System::Int16 dest_host_id;
                static System::Int16 dest_mod_id;
                static System::Int32 num_data_bytes;
                static System::Int32 remaining_bytes;
                static System::Int32 is_dynamic;
                static System::Int32 reserved;
            };
        };

        static array<System::SByte> ^MDF_MM_ERROR;
        static array<System::SByte> ^MDF_MM_INFO;
        ref class MDF_CONNECT
        {
        public:
            static System::Int16 logger_status;
            static System::Int16 daemon_status;
        };

        static System::Int32 MDF_SUBSCRIBE;
        static System::Int32 MDF_UNSUBSCRIBE;
        static System::Int32 MDF_PAUSE_SUBSCRIPTION;
        static System::Int32 MDF_RESUME_SUBSCRIPTION;
        ref class MDF_FORCE_DISCONNECT
        {
        public:
            static System::Int32 mod_id;
        };

        ref class MDF_MODULE_READY
        {
        public:
            static System::Int32 pid;
        };

        static array<System::SByte> ^MDF_DYNAMIC_DD_READ_ERR;
        static array<System::SByte> ^MDF_DEBUG_TEXT;
        static array<System::SByte> ^MDF_START_APP;
        static array<System::SByte> ^MDF_STOP_APP;
        static array<System::SByte> ^MDF_RESTART_APP;
        static array<System::SByte> ^MDF_KILL_APP;
        static array<System::SByte> ^MDF_SLAVE_START_APP;
        ref class MDF_SLAVE_START_APP_ACK
        {
        public:
            static System::Int32 num_remote_hosts;
        };

        static array<System::SByte> ^MDF_SLAVE_STOP_APP;
        static array<System::SByte> ^MDF_SLAVE_KILL_APP;
        static array<System::SByte> ^MDF_SLAVE_RESTART_APP;
        static array<System::SByte> ^MDF_AM_ERROR;
        static array<System::SByte> ^MDF_FAIL_START_APP;
        static array<System::SByte> ^MDF_FAIL_STOP_APP;
        static array<System::SByte> ^MDF_FAIL_KILL_APP;
        static array<System::SByte> ^MDF_AM_CONFIG_FILE_DATA;
        static array<System::SByte> ^MDF_AM_APP_NAME;
        static array<System::SByte> ^MDF_SLAVE_FAIL_START_APP;
        static array<System::SByte> ^MDF_SLAVE_AM_ERROR;
        static array<System::SByte> ^MDF_APP_ERROR;
        ref class MDF_TIMER_EXPIRED
        {
        public:
            static System::Int32 timer_id;
        };

        ref class MDF_TIMED_OUT
        {
        public:
            static System::Int32 timer_id;
        };

        ref class MDF_SET_TIMER_FAILED
        {
        public:
            static System::Int16 mod_id;
            static System::Int32 timer_id;
            static System::Int32 snooze_time;
        };

        ref class MDF_SET_TIMER
        {
        public:
            static System::Int32 timer_id;
            static System::Int32 snooze_time;
        };

        ref class MDF_CANCEL_TIMER
        {
        public:
            static System::Int32 timer_id;
        };

        ref class MDF_SAVE_MESSAGE_LOG
        {
        public:
            static array<System::SByte> ^pathname = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 pathname_length;
        };

        ref class MDF_TIMING_TEST
        {
        public:
            static array<System::Double> ^time = {0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class SAMPLE_HEADER
        {
        public:
            static System::Int32 SerialNo;
            static System::Int32 Flags;
            static System::Double DeltaTime;
        };

        ref class MOVEMENT_COMMAND_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class INPUT_DOF_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^dof_vals = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class TRIAL_EVENT
        {
        public:
            static System::Double event_time;
            static System::Int32 event_code;
            static System::Int32 reserved;
        };

        ref class PLAN_PROCESSOR_STATE
        {
        public:
            static array<System::Double> ^D = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class AUTOMAGIC_CONTROLLER_PARAMS
        {
        public:
            static array<System::Double> ^virtualPadPosition = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^centralPointPosition = {0,0,0};
            static array<System::Double> ^posMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^posMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^velMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^velMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double graspingGraspApertureTarget;
            static System::Double graspingOpenApertureTarget;
            static System::Double graspingIntermediateApertureTarget;
            static System::Double maxApproachSwingAngle;
            static System::Double graspTooCloseIfClosedRadius;
        };

        ref class ROBOT_CONTROL_CONFIG
        {
        public:
            static array<System::Double> ^target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^coriMatrix = {0,0,0,0,0,0,0,0,0};
            ref class trialEvent
            {
            public:
                static System::Double event_time;
                static System::Int32 event_code;
                static System::Int32 reserved;
            };
            ref class autoControlParams
            {
            public:
                static array<System::Double> ^virtualPadPosition = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^centralPointPosition = {0,0,0};
                static array<System::Double> ^posMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^posMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^velMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^velMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static System::Double graspingGraspApertureTarget;
                static System::Double graspingOpenApertureTarget;
                static System::Double graspingIntermediateApertureTarget;
                static System::Double maxApproachSwingAngle;
                static System::Double graspTooCloseIfClosedRadius;
            };
            static array<System::Double> ^autoPosControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoVelControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthPosImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthVelImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^importantDOF = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class ROBOT_ACTUAL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^Jpos = {0,0,0,0,0,0,0};
            static array<System::Double> ^Jvel = {0,0,0,0,0,0,0};
            static array<System::Double> ^Cpos = {0,0,0};
            static array<System::Double> ^Cori = {0,0,0};
            static array<System::Double> ^Cforce = {0,0,0};
            static array<System::Double> ^Ctrq = {0,0,0};
            static array<System::Double> ^Cvel = {0,0,0};
            static array<System::Double> ^CangVel = {0,0,0};
            static array<System::Double> ^Hpos = {0,0,0,0};
            static array<System::Double> ^Hstrain = {0,0,0,0};
            static array<System::Double> ^Jtrq = {0,0,0};
        };

        ref class ROBOT_CONTROL_SPACE_ACTUAL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^CoriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class PLANNER_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^targetPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class JVEL_COMMAND
        {
        public:
            static array<System::Double> ^cmd = {0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class OVERRIDE_COMMAND
        {
        public:
            static array<System::Double> ^DOFCommand = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^JposCommand = {0,0,0,0,0,0,0};
            static System::Int32 controllerId;
            static System::Int32 j0nks;
        };

        ref class ROBOT_CONTROL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            ref class autoControl
            {
            public:
                ref class sample_header
                {
                public:
                    static System::Int32 SerialNo;
                    static System::Int32 Flags;
                    static System::Double DeltaTime;
                };
                static array<System::Double> ^targetPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            };
            ref class overrideCommand
            {
            public:
                static array<System::Double> ^DOFCommand = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^JposCommand = {0,0,0,0,0,0,0};
                static System::Int32 controllerId;
                static System::Int32 j0nks;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^actualControlPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^actualControlVel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoControlPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoControlVel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoPosControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoVelControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthPosImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthVelImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^intrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^intrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^overrideDimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::UInt32 actualCommandComposition;
            static System::Int32 blank;
        };

        ref class PS3_DATA
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 val;
            static System::Int32 controllerId;
            static array<System::Int32> ^buttonMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^buttonVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelMask = {0,0};
            static System::Int32 spacer;
            static array<System::Double> ^accelVal = {0,0};
        };

        ref class PS3_CONFIG
        {
        public:
            static array<System::Int32> ^stickCommandDOFMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^stickCommandJointMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickScale = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickOffset = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 use_controller;
            static System::Int32 use_label_controller;
        };

        ref class MDF_PS3_BUTTON_PRESS
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 val;
            static System::Int32 controllerId;
            static array<System::Int32> ^buttonMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^buttonVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelMask = {0,0};
            static System::Int32 spacer;
            static array<System::Double> ^accelVal = {0,0};
        };

        ref class MDF_PS3_BUTTON_RELEASE
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 val;
            static System::Int32 controllerId;
            static array<System::Int32> ^buttonMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^buttonVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelMask = {0,0};
            static System::Int32 spacer;
            static array<System::Double> ^accelVal = {0,0};
        };

        ref class PS3_RAW_DATA
        {
        public:
            static array<System::Int32> ^buttonMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^buttonVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousMask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^continuousVal = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelMask = {0,0};
            static array<System::Double> ^accelVal = {0,0};
            static System::Int32 controllerId;
            static System::Int32 spacer;
        };

        ref class PS3_GENERIC_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Int32 controllerId;
            static System::Int32 spacer;
            static array<System::Double> ^dof_vals = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PS3_BUTTON_DATA
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 controllerId;
        };

        ref class PS3_RAW_CONFIG
        {
        public:
            static array<System::Int32> ^stickCommandDOFMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^stickCommandJointMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickScale = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickOffset = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^accelScale = {0,0};
            static array<System::Double> ^accelOffset = {0,0};
            static array<System::Double> ^DOFscale = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelDOFMap = {0,0};
            static array<System::Int32> ^use_controller = {0,0,0,0,0,0,0,0,0,0};
            static System::Int32 free_run;
            static System::Int32 spacer;
        };

        ref class PS3_ACCEL_DATA
        {
        public:
            static System::Int32 controllerId;
            static System::Int32 ax;
            static System::Int32 ay;
            static System::Int32 az;
            static System::Double time;
            static System::Double ddx;
            static System::Double ddy;
            static System::Double ddz;
            static System::Double dx;
            static System::Double dy;
            static System::Double dz;
            static System::Double x;
            static System::Double y;
            static System::Double z;
            static System::Double roll;
            static System::Double pitch;
        };

        ref class MDF_PS3_RAW_CONFIG
        {
        public:
            static array<System::Int32> ^stickCommandDOFMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^stickCommandJointMap = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickScale = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^stickOffset = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^accelScale = {0,0};
            static array<System::Double> ^accelOffset = {0,0};
            static array<System::Double> ^DOFscale = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^accelDOFMap = {0,0};
            static array<System::Int32> ^use_controller = {0,0,0,0,0,0,0,0,0,0};
            static System::Int32 free_run;
            static System::Int32 spacer;
        };

        ref class MDF_PS3_SIMPLE_BUTTON_PRESS
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 controllerId;
        };

        ref class MDF_PS3_SIMPLE_BUTTON_RELEASE
        {
        public:
            static System::Int32 whichButton;
            static System::Int32 controllerId;
        };

        ref class MDF_PS3_GENERIC_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Int32 controllerId;
            static System::Int32 spacer;
            static array<System::Double> ^dof_vals = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_PARAMS
        {
        public:
            static array<System::Double> ^Dimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_START_SESSION
        {
        public:
            static array<System::Double> ^Dimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_RELOAD_CONFIGURATION
        {
        public:
            static array<System::Double> ^Dimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class EM_PROCEDURE_MESSAGE
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_RESET_AGGREGATION
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_RESUME_COLLECTION
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_AGGREGATE_DATA_NOW
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_PAUSE_COLLECTION
        {
        public:
            static array<System::Int32> ^regressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_RESET_STATE
        {
        public:
            static array<System::Double> ^initial_position = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^initial_velocity = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^target_position = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 reset_history;
            static System::Int32 reserved;
        };

        ref class MDF_EM_START_TRIAL
        {
        public:
            static System::Int32 data_index;
            static System::Int32 reserved;
        };

        ref class MDF_EM_ADAPT_NOW
        {
        public:
            static System::Int32 first_data_index;
            static System::Int32 last_data_index;
        };

        ref class MDF_EM_UPDATE_DRIFT_CORRECTION
        {
        public:
            static array<System::Double> ^drift_correction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        static System::Double MDF_EM_MOD_DEPTH_CUTOFF;
        static array<System::SByte> ^MDF_EM_SET_PDS;
        static array<System::SByte> ^MDF_EM_PDS;
        ref class PVAConfig
        {
        public:
            static array<System::Double> ^Norm2RealFactor = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double ModDepthCutoff;
            static System::Double RSquaredCutoff;
            static array<System::Double> ^PredictFRFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^AdaptFRFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^TargetFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^RegressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^ControlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double numAdaptReps;
        };

        ref class MDF_PVA_CONFIG
        {
        public:
            static array<System::Double> ^Norm2RealFactor = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double ModDepthCutoff;
            static System::Double RSquaredCutoff;
            static array<System::Double> ^PredictFRFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^AdaptFRFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^TargetFilter = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^RegressionGroups = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^ControlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double numAdaptReps;
        };

        ref class PVAState
        {
        public:
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^PV = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^usedIndices = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PVA_STATE
        {
        public:
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^PV = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^usedIndices = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class PVAAttenuateCommand
        {
        public:
            static array<System::SByte> ^targTag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^attenuationLevel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PVA_ATTENUATE_COMMAND
        {
        public:
            static array<System::SByte> ^targTag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^attenuationLevel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_RAW_SPIKECOUNT
        {
        public:
            static System::Int32 source_index;
            static System::Int32 reserved;
            static System::Double source_timestamp;
            static System::Double count_interval;
            static array<System::Byte> ^counts = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        static System::Byte SPIKE_COUNT_DATA_TYPE;
        ref class MDF_SPM_SPIKECOUNT
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double source_timestamp;
            static System::Double count_interval;
            static array<System::Byte> ^counts = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_SAMPLE_GENERATED
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double source_timestamp;
        };

        ref class MDF_SAMPLE_RESPONSE
        {
        public:
            static System::Double sample_response_timestamp;
            static System::Double sample_alignment_timestamp;
            static System::UInt32 sample_response_count;
            static System::UInt32 sample_alignment_count;
        };

        ref class MDF_INPUT_DOF_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^dof_vals = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_OPERATOR_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_FIXTURED_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_SHADOW_COMPOSITE_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_FIXTURED_COMPOSITE_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PROBOT_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^tool_pos = {0,0,0,0,0,0,0};
            static array<System::Double> ^wrist_pos = {0,0,0,0,0,0,0};
        };

        ref class MDF_GROBOT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^command = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 mode;
            static System::Int32 reserved;
        };

        ref class MDF_GROBOT_BYPASS
        {
        public:
            static array<System::Double> ^command = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 mode;
            static System::Int32 reserved;
        };

        ref class MDF_OPTO_CNTRL_CMD
        {
        public:
            static array<System::Double> ^Cmd = {0,0,0,0,0,0};
        };

        ref class MDF_OPTO_POS_CMD
        {
        public:
            static array<System::Double> ^Cmd = {0,0,0,0};
        };

        ref class MDF_KIN_POS_CMD
        {
        public:
            static array<System::Double> ^Cmd = {0,0,0,0};
        };

        ref class MDF_KINECT_SKELETON
        {
        public:
            static array<System::Double> ^x = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^y = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^z = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^w = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 Which;
            static System::Int32 Reserved;
        };

        ref class MDF_GROBOT_SEGMENT_PERCEPTS
        {
        public:
            static array<System::Double> ^ind_force = {0,0,0};
            static array<System::Double> ^mid_force = {0,0,0};
            static array<System::Double> ^rng_force = {0,0,0};
            static array<System::Double> ^lit_force = {0,0,0};
            static array<System::Double> ^thb_force = {0,0,0};
            static array<System::Double> ^ind_accel = {0,0,0};
            static array<System::Double> ^mid_accel = {0,0,0};
            static array<System::Double> ^rng_accel = {0,0,0};
            static array<System::Double> ^lit_accel = {0,0,0};
            static array<System::Double> ^thb_accel = {0,0,0};
        };

        ref class MDF_CERESTIM_CONFIG_MODULE
        {
        public:
            static System::Int32 configID;
            static System::Int32 afcf;
            static System::Double pulses;
            static System::Double amp1;
            static System::Double amp2;
            static System::Double width1;
            static System::Double width2;
            static System::Double frequency;
            static System::Double interphase;
        };

        ref class MDF_CERESTIM_CONFIG_CHAN
        {
        public:
            static System::Int32 stop;
            static System::Int32 group_stimulus;
            static System::Int32 group_numChans;
            static array<System::Int32> ^group_channel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^group_pattern = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 manual_stimulus;
            static System::Int32 manual_channel;
            static System::Int32 manual_pattern;
        };

        ref class MDF_GROBOT_RAW_FEEDBACK
        {
        public:
            static array<System::Double> ^j_ang = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^j_vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^j_trq = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_GROBOT_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^position = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^velocity = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^force = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^cori_matrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_SESSION_CONFIG
        {
        public:
            static array<System::SByte> ^data_dir = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_GLOVE_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_MICROSTRAIN_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_OVERRIDE_CONFIG
        {
        public:
            static array<System::Int32> ^chosen_channel_mask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_CHANGE_TOOL
        {
        public:
            static System::Int32 next_tool_id;
            static System::Int32 reserved;
        };

        ref class MDF_CHANGE_TOOL_COMPLETE
        {
        public:
            static System::Int32 tool_id;
            static System::Int32 reserved;
        };

        ref class MDF_TASK_STATE_CONFIG
        {
        public:
            static System::Int32 id;
            static System::Int32 rep_num;
            static System::Int32 use_for_calib;
            static System::Int32 target_combo_index;
            static System::Int32 timed_out_conseq;
            static System::Int32 idle_gateable;
            static System::Int32 reach_offset;
            static System::Int32 relax_arm;
            static System::Double idle_timeout;
            static System::Double ts_time;
            static array<System::Double> ^target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^coriMatrix = {0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^idle_target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Double trans_threshold;
            static System::Double ori_threshold;
            static System::Double trans_threshold_f;
            static System::Double ori_threshold_f;
            static array<System::Double> ^finger_threshold = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^finger_threshold_judging_method = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^finger_threshold_judging_polarity = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 trans_threshold_judging_polarity;
            static System::Int32 ori_threshold_judging_polarity;
            static System::Int32 trans_threshold_f_judging_polarity;
            static System::Int32 ori_threshold_f_judging_polarity;
            static System::Double timeout;
            static array<System::SByte> ^tags = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_JUDGE_VERDICT
        {
        public:
            static System::Int32 id;
            static System::Int32 reserved;
            static array<System::SByte> ^reason = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_END_TASK_STATE
        {
        public:
            static System::Int32 id;
            static System::Int32 outcome;
            static array<System::SByte> ^reason = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_RAW_SAMPLE_RESPONSE
        {
        public:
            static System::Int32 source_index;
            static System::Int32 reserved;
            static System::Double source_timestamp;
        };

        ref class MDF_CODE_VERSION
        {
        public:
            static array<System::SByte> ^module_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^version = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_SPM_FIRINGRATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double source_timestamp;
            static System::Double count_interval;
            static array<System::Double> ^rates = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        static array<System::Byte> ^MDF_EM_DECODER_CONFIGURATION;
        ref class MDF_LOAD_DECODER_CONFIG
        {
        public:
            static array<System::SByte> ^full_path = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_XM_START_SESSION
        {
        public:
            static System::Int32 load_calibration;
            static System::Int32 calib_session_id;
            static System::Int32 num_reps;
            static System::Int32 reserved;
            static array<System::SByte> ^subject_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PING
        {
        public:
            static array<System::SByte> ^module_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PING_ACK
        {
        public:
            static array<System::SByte> ^module_name = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_DEBUG_VECTOR
        {
        public:
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_APP_START
        {
        public:
            static array<System::SByte> ^config = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_MODULE_START
        {
        public:
            static array<System::SByte> ^module = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_SPM_SPIKE_SNIPPET
        {
        public:
            static System::Double time;
            static System::Int32 chan;
            static System::Int32 unit;
            static System::Int32 box_id;
            static System::Int32 length;
            static array<System::Int16> ^snippet = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_SPM_SPIKE_TIMES
        {
        public:
            static array<System::Double> ^time = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int16> ^chan = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^unit = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^box_id = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_IDLY_LABELLING
        {
        public:
            static System::Int32 state;
            static System::Int32 reserved;
        };

        ref class MDF_EM_DRIFT_CORRECTION
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^drift_correction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_DENSO_WIGGLE
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 num_cycles;
            static array<System::Int32> ^sequence = {0,0,0,0,0,0,0,0};
            static array<System::Double> ^amplitude = {0,0,0};
        };

        ref class MDF_PLAY_SOUND
        {
        public:
            static System::Int32 id;
            static System::Int32 reserved;
        };

        ref class MDF_ARTIFACT_REJECTED
        {
        public:
            static System::Double time;
        };

        ref class MDF_IDLE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double score;
            static System::Double gain;
            static System::Int32 idle;
            static System::Int32 reserved;
        };

        ref class MDF_WAM_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^CoriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_WAM_HAND_FEEDBACK
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^CoriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PLANNER_CONTROL_CONFIG
        {
        public:
            static array<System::Double> ^target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^coriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_ROBOT_JOINT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0};
            static array<System::Int32> ^overrideDims = {0,0,0,0,0,0,0,0};
        };

        ref class MDF_IDLEGATED_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_TRIAL_EVENT
        {
        public:
            static System::Double event_time;
            static System::Int32 event_code;
            static System::Int32 reserved;
        };

        ref class MDF_TRIAL_CONFIG
        {
        public:
            static System::Int32 rep_no;
            static System::Int32 trial_no;
            static System::Int32 num_reward_states;
            static System::Int32 reserved;
        };

        ref class MDF_TRIAL_STATUS
        {
        public:
            static System::Int32 success;
            static System::Int32 reserved;
        };

        ref class MDF_ROBOT_ACTUAL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^Jpos = {0,0,0,0,0,0,0};
            static array<System::Double> ^Jvel = {0,0,0,0,0,0,0};
            static array<System::Double> ^Cpos = {0,0,0};
            static array<System::Double> ^Cori = {0,0,0};
            static array<System::Double> ^Cforce = {0,0,0};
            static array<System::Double> ^Ctrq = {0,0,0};
            static array<System::Double> ^Cvel = {0,0,0};
            static array<System::Double> ^CangVel = {0,0,0};
            static array<System::Double> ^Hpos = {0,0,0,0};
            static array<System::Double> ^Hstrain = {0,0,0,0};
            static array<System::Double> ^Jtrq = {0,0,0};
        };

        ref class MDF_ROBOT_CONTROL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            ref class autoControl
            {
            public:
                ref class sample_header
                {
                public:
                    static System::Int32 SerialNo;
                    static System::Int32 Flags;
                    static System::Double DeltaTime;
                };
                static array<System::Double> ^targetPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            };
            ref class overrideCommand
            {
            public:
                static array<System::Double> ^DOFCommand = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^JposCommand = {0,0,0,0,0,0,0};
                static System::Int32 controllerId;
                static System::Int32 j0nks;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^actualControlPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^actualControlVel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoControlPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoControlVel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoPosControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoVelControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthPosImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthVelImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^intrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^intrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^overrideDimensions = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::UInt32 actualCommandComposition;
            static System::Int32 blank;
        };

        ref class MDF_ROBOT_CONTROL_SPACE_ACTUAL_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double RTMA_received_time;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^CoriMatrix = {0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_ROBOT_CONTROL_CONFIG
        {
        public:
            static array<System::Double> ^target = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^coriMatrix = {0,0,0,0,0,0,0,0,0};
            ref class trialEvent
            {
            public:
                static System::Double event_time;
                static System::Int32 event_code;
                static System::Int32 reserved;
            };
            ref class autoControlParams
            {
            public:
                static array<System::Double> ^virtualPadPosition = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^centralPointPosition = {0,0,0};
                static array<System::Double> ^posMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^posMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^velMin = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^velMax = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                static System::Double graspingGraspApertureTarget;
                static System::Double graspingOpenApertureTarget;
                static System::Double graspingIntermediateApertureTarget;
                static System::Double maxApproachSwingAngle;
                static System::Double graspTooCloseIfClosedRadius;
            };
            static array<System::Double> ^autoPosControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^autoVelControlFraction = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthPosImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^orthVelImpedance = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicVelControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^extrinsicPosControlled = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^importantDOF = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_GIVE_REWARD
        {
        public:
            static System::Double duration_ms;
            static System::Double num_clicks;
        };

        ref class MDF_IO_START_STREAM
        {
        public:
            ref class limits
            {
            public:
                static array<System::Double> ^high = {0,0,0,0,0,0,0,0,0,0,0,0};
                static array<System::Double> ^low = {0,0,0,0,0,0,0,0,0,0,0,0};
            };
            static System::Int32 reserved;
            static System::Int32 internal_sampling;
            static System::Double sample_interval;
        };

        ref class MDF_ANALOG_STREAM
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^data = {0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class KNOB_EVENT_DATA
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_KNOB_TOUCHED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_KNOB_TURNED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_KNOB_ANTI_TURNED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_KNOB_OVER_TURNED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_DOOR_MOVED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_DOOR_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_DOOR_ANTI_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_DOOR_OVER_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_KNOB_MOVED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_DOOR_UN_OPENED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_KNOB_RELEASED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_PAD_PRESSED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_PAD_STEADY
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_PAD_PERTURBED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_PAD_RELEASED
        {
        public:
            static System::Double source_time;
            static System::Double event_time;
            static System::Int32 sample_no;
        };

        ref class MDF_DENSO_MOVE
        {
        public:
            static System::Int32 position_no;
            static System::Int32 movement_id;
        };

        ref class MDF_DENSO_SET_SPEED
        {
        public:
            static System::Double speed;
        };

        ref class MDF_DENSO_MOVE_CONTINUE
        {
        public:
            static System::Int32 position_no;
            static System::Int32 movement_id;
        };

        static array<System::SByte> ^MDF_DENSO_NOT_READY;
        ref class RESPONSE_DATA_TO_DENSO_MOVE
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class MDF_DENSO_MOVE_COMPLETE
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class MDF_DENSO_MOVE_FAILED
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class MDF_DENSO_MOVE_INVALID
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class MDF_DENSO_HALTED
        {
        public:
            static System::Int32 movement_id;
            static System::Int32 reserved;
        };

        ref class MDF_EM_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_EM_AUX_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_COMPOSITE_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_ROBOT_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PLANNER_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PLANNER_STATE
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^targetPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_PLAN_PROCESSOR_STATE
        {
        public:
            static array<System::Double> ^D = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_FM_MOVEMENT_COMMAND
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static System::Double sample_interval;
            static array<System::Double> ^pos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^vel = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Int32> ^controlledDims = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::SByte> ^tag = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        };

        ref class MDF_OVERRIDE_COMMAND
        {
        public:
            static array<System::Double> ^DOFCommand = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static array<System::Double> ^JposCommand = {0,0,0,0,0,0,0};
            static System::Int32 controllerId;
            static System::Int32 j0nks;
        };

        ref class MDF_JVEL_COMMAND
        {
        public:
            static array<System::Double> ^cmd = {0,0,0,0,0,0,0,0,0,0,0};
        };

        static array<System::Int32> ^MDF_COMPONENT_DELAY_MSG_TYPES = {0,0,0,0,0,0};
        ref class DELAY_DATA
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^Components = {0,0,0,0,0,0};
            static System::Double Total;
        };

        ref class MDF_ESTIMATED_DELAY
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^Components = {0,0,0,0,0,0};
            static System::Double Total;
        };

        ref class MDF_MEASURED_DELAY
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^Components = {0,0,0,0,0,0};
            static System::Double Total;
        };

        static array<System::SByte> ^MDF_CLEAR_FUNCTION;
        ref class TARG_CLOUD
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^cloud = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 nTargs;
            static System::Int32 spacer;
        };

        ref class MDF_TARG_CLOUD
        {
        public:
            ref class sample_header
            {
            public:
                static System::Int32 SerialNo;
                static System::Int32 Flags;
                static System::Double DeltaTime;
            };
            static array<System::Double> ^cloud = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            static System::Int32 nTargs;
            static System::Int32 spacer;
        };

        static System::Double MDF_ATTENTION;
    };

}

