/*H ----------------------------------------------------------------------------
  FILENAME :  TimeDateSettingFSM.h

  DESCRIPTION :
              Header file for Time/date/alarm setting Finite state machine 

 AUTHOR :     Louie Williams


 INCLUDES : defines.h, 

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef TimeDateSettingFSM_H
#define TimeDateSettingFSM_H

#include "Defines.h"
#include "LCD.h"

extern uint8_t TimeDateState;

void timeDateSettingFSM(void);

#endif