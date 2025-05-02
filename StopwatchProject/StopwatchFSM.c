/*F ----------------------------------------------------------------------------
  NAME :      StopwatchFSM.c

  DESCRIPTION :
              Controls what state the stopwatch mode is in 

  Author: Ethan Evans

  FUNCTIONS :
              [1] Finite state machine for the stopwatch mode
                INPUTS :    none
                RETURNS :   void
                  a) displays 00:00.00 on stopwatch
                  b) displays the stopwatch counting up
                  c) displays the time that it was when button was pressed but continues to count in the background
                  d) dispkay the time that it was when the button was pressed but does not continue to count in the background
*F ---------------------------------------------------------------------------*/

#include "StopwatchFSM.h"
#include "Defines.h"
#include "StopwatchRunning.h"
#include "msp430fr4133.h"
#include "Date.h"

uint8_t stopwatchState = STOPWATCH_ZERO;

void StopwatchFSM(){
    LCDCTL0 |= LCD4MUX | LCDON;               
    while(1){
        switch (stopwatchState){
            case STOPWATCH_ZERO:
                ZeroStopwatch();
                if(startStopFlag == 1){
                    stopwatchState = STOPWATCH_RUNNING;
                    startStopFlag = 0;
                    lapResetFlag = 0;
                }
                else {
                    stopwatchState = STOPWATCH_ZERO;
                    lapResetFlag = 0;
                }
                break;
            case STOPWATCH_RUNNING:
                StopwatchRun();
                if(startStopFlag == 1){
                    stopwatchState = STOPWATCH_STOPPED;
                    stopwatchStopped();
                    startStopFlag = 0;
                }
                else if (lapResetFlag == 1){
                    stopwatchState = STOPWATCH_LAP;
                    StopwatchLapValue();                         //Placed here so it isnt repeatedly called within STOPWATCH_LAP mode
                    lapResetFlag = 0;
                }
                else {
                    stopwatchState = STOPWATCH_RUNNING;
                }
                break;
            case STOPWATCH_LAP:
                if(startStopFlag == 1){
                    stopwatchState = STOPWATCH_STOPPED;
                    StopwatchStopped();
                    startStopFlag = 0;
                }
                else if (lapResetFlag == 1){
                    StopwatchLapValue();
                    stopwatchState = STOPWATCH_LAP;
                    lapResetFlag = 0;
                }
                else {
                    stopwatchState = STOPWATCH_LAP;
                    StopwatchLap();
                }
                break;
            case STOPWATCH_STOPPED:
                if(startStopFlag == 1){
                    stopwatchState = STOPWATCH_RUNNING;
                    startStopFlag = 0;
                    lapResetFlag = 0;
                }
                else if(lapResetFlag == 1){
                    stopwatchState = STOPWATCH_ZERO;
                    lapResetFlag = 0;
                }
                else {
                    stopwatchState = STOPWATCH_STOPPED;
                }
                break;
            default:
        }
    }
}