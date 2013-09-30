#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "ps3RawDefines.h"
#ifdef USERTMA
#include "RTMA_config.h"
#include "RTMA.h"
#include "RTMAThread.h"

const int cycle_time = 0.03; // seconds

extern INPUT_DOF_DATA dofData[MAX_CONTROLLERS];
extern int hasJoysticks[MAX_CONTROLLERS];

static RTMA_Module rtma;
//static int serial =1;
extern int keep_going;

pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t rtma_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

#ifdef USERTMA

void SendPS3Message(int m_type, char *data, unsigned dSize)
{
  static CMessage M;
  pthread_mutex_lock( &rtma_mutex );
  M.Set(m_type, data, dSize);  
  rtma.SendMessage(&M);
  pthread_mutex_unlock( &rtma_mutex );
}

void *RTMA_Thread(void *threadConfig)
{
  CMessage inMsg;
  CMessage PingAckMessage( MT_PING_ACK);
  static MDF_SAMPLE_GENERATED sample_gen;
  int j;

  PingAckMessage.AllocateData( sizeof(MDF_PING_ACK));

  THREAD_CONFIG_STRUCT *inConfig = (THREAD_CONFIG_STRUCT*) threadConfig;
  PS3_RAW_CONFIG *config = inConfig->ps3_config;
  char *mm_ip = inConfig->mm_ip;
  rtma.InitVariables(MID_PS3_RAW_MODULE, 0);
	
  while(keep_going) {
		
	try {
	  if( mm_ip == NULL) {
		fprintf(stdout, "Connecting to RTMA at default IP and port... ");
		rtma.ConnectToMMM();
	  } else {
		fprintf(stdout, "Connecting to RTMA at %s... ", mm_ip);
		rtma.ConnectToMMM(mm_ip);
	  }
	  fprintf(stdout, "okay.\n");

      rtma.Subscribe(MT_EXIT);
      rtma.Subscribe(MT_PING);

	  if( !config->free_run) {
		rtma.Subscribe(MT_SAMPLE_GENERATED);
	  }
		
	  SendPS3Message(MT_PS3_RAW_CONFIG, (char *) config, sizeof(MDF_PS3_RAW_CONFIG));
	  
	  while(keep_going) 
      {
        bool got_msg = rtma.ReadMessage( &inMsg, 0.03);
        if( got_msg) {
        if (inMsg.msg_type == MT_EXIT) {
        
            if ((inMsg.dest_mod_id == 0) || (inMsg.dest_mod_id == rtma.GetModuleID()))
            {
                fprintf(stdout,"got exit!\n");
                rtma.SendSignal(MT_EXIT_ACK);
                rtma.DisconnectFromMMM();
                keep_going = false;
                break;
            }
        }
        else if (inMsg.msg_type == MT_PING) {
        
          char MODULE_NAME[] = "ps3RawModule";
          MDF_PING *pg = (MDF_PING *) inMsg.GetDataPointer();
          if ( (strcasecmp(pg->module_name, MODULE_NAME) == 0) || 
               (strcasecmp(pg->module_name, "*") == 0) || 
               (inMsg.dest_mod_id == rtma.GetModuleID()) )
          {
            MDF_PING_ACK *pa = (MDF_PING_ACK *) PingAckMessage.GetDataPointer();
            
            memset(pa,0,sizeof(MDF_PING_ACK));        
            for (int i = 0; i < strlen(MODULE_NAME); i++)
            {
              pa->module_name[i] = MODULE_NAME[i];
            }

            rtma.SendMessage( &PingAckMessage);
          }
        }
            else if (inMsg.msg_type == MT_SAMPLE_GENERATED) {
            if (!config->free_run) {
                    inMsg.GetData(&sample_gen);
                for(j = 0; j < MAX_CONTROLLERS; j++) {
                  if(hasJoysticks[j]) {
                    dofData[j].sample_header = sample_gen.sample_header;
                    pthread_mutex_lock( &data_mutex );
                    SendPS3Message(MT_INPUT_DOF_DATA, (char *) &(dofData[j]), sizeof(MDF_INPUT_DOF_DATA));
                    pthread_mutex_unlock( &data_mutex );
                  }
                }			  
              }
            } 
        }
        
        if (config->free_run) {
              for (j = 0 ; j < MAX_CONTROLLERS; j++) {
                if (hasJoysticks[j]) {
                  dofData[j].sample_header.SerialNo = 0; //SampleNo;
                  dofData[j].sample_header.Flags = 0;
                  fprintf(stderr, "|");
                  pthread_mutex_lock( &data_mutex );
                  SendPS3Message(MT_INPUT_DOF_DATA, (char *) &(dofData[j]), sizeof(MDF_INPUT_DOF_DATA));
                  fprintf(stderr, ">");
                  pthread_mutex_unlock( &data_mutex );
                  fprintf(stderr, "-");
                }
          }
        }
	  } // end while
	}
	catch(UPipeClosedException) {
	  fprintf(stderr, "Reconnecting to RTMA\n");
	  Sleep(500);
	}
	catch(UPipeException)	{
	  fprintf(stderr, "Cannot connect to RTMA, waiting to reconnect\n");
	  Sleep(500);
	}
  }
}

#endif
