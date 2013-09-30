#ifndef __RTMA_THREAD_H__
#define __RTMA_THREAD_H__

#include "ps3RawDefines.h"

typedef struct {
  PS3_RAW_CONFIG *ps3_config;
  char *mm_ip;
} THREAD_CONFIG_STRUCT;

void SendPS3Message(int m_type, char *data, unsigned dSize);
void *RTMA_Thread(void *threadConfig);

#endif
