/*H ----------------------------------------------------------------------------
  FILENAME :  StopwatchFSM.h

  DESCRIPTION :
              Header file for the finite state machine for the stopwatch

 AUTHOR :     Ethan Evans

 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef StopwatchFSM_H
#define StopwatchFSM_H

#include "Defines.h"
#include "LCD.h"
#include "TimerInterrupt.h"
#include "ButtonInterrupts.h"

extern uint8_t stopwatchState;

void StopwatchFSM();
void StopwatchLapValue();
void StopwatchLap();
void StopwatchRun();
void StopwatchStopped();
void ZeroStopwatch();

#endif