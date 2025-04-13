/*H ----------------------------------------------------------------------------
  FILENAME :  ClockFSM.h

  DESCRIPTION :
              Header file for Clock Finite state machine 

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef ClockFSM_H
#define ClockFSM_H

#include "ClockNormal.h"
#include "Chime.h"
#include "ClockAlarm.h"
#include "Defines.h"
#include "msp430fr4133.h"
#include "Date.h"


extern uint8_t clockState;

void clockFSM();

#endif