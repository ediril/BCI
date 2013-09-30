#ifndef __JSFUNC_H__
#define __JSFUNC_H__

    #include "ps3RawDefines.h"


  int InitJoystick(char *dev, int id);
  int InitAccel(char *dev, int id);
  int StreamController(PS3_RAW_DATA *data, int *hasJoysticks);



#endif
