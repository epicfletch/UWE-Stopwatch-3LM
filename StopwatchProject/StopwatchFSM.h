/*H ----------------------------------------------------------------------------
  FILENAME :  StopwatchFSM.h

  DESCRIPTION :
              Header file for the finite state machine for the stopwatch

 AUTHOR :     Ethan Evans

 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef Stopwatch_H
#define Stopwatch_H

#include "Defines.h"
#include "StopwatchZero.h"
#include "StopwatchRunning.h"
#include "StopwatchLap.h"
#include "StopwatchStopped.h"


extern uint8_t stopwatchState;

void stopwatchFSM();

#endif