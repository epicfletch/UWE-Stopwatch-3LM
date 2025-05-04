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

#include "Defines.h"
#include "ClockNormal.h"
#include "Chime.h"
#include "ClockAlarm.h"
#include "Date.h"

extern uint8_t clockState;

extern int chimeToggleFlag;
extern int chimeFlag;

void ClockFSM();

#endif