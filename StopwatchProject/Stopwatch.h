/*H ----------------------------------------------------------------------------
  FILENAME :  ClockFSM.h

  DESCRIPTION :
              Header file for Clock Finite state machine 

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef Stopwatch_H
#define Stopwatch_H

#include "Defines.h"
#include "ClockNormal.h"

extern uint8_t clockState;

void clockFSM();

#endif