/*F ----------------------------------------------------------------------------
  NAME :      StopwatchFSM.c

  DESCRIPTION :
              Controls the state the the chrono mode is in

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
#include "msp430fr4133.h"
#include "Date.h"

uint8_t stopwatchState = STOPWATCH_ZERO;

// Digit values to display (these hold the frozen snapshot)
unsigned char minutesHold, secondsHold, milliSecondsHold;

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
                    startStopFlag = 0;
                }
                else if (lapResetFlag == 1){
                    stopwatchState = STOPWATCH_LAP;
                    StopwatchLapValue();                         
                    lapResetFlag = 0;
                }
                else {
                    stopwatchState = STOPWATCH_RUNNING;
                }
                break;
            case STOPWATCH_LAP:
                if(startStopFlag == 1){
                    stopwatchState = STOPWATCH_STOPPED;
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
                    StopwatchStopped();
                }
                break;
            default:
        }
    }
}

void StopwatchLapValue(){
    minutesHold = stopwatchTime.minutes;
    secondsHold = stopwatchTime.seconds;
    milliSecondsHold = stopwatchTime.milliSeconds;
}
 
/*F ----------------------------------------------------------------------------
  NAME :      StopwatchLap.c

  DESCRIPTION :
              Functions to control the stopwatch to be in lap mode where the time is set to what it was when button was pressed but continues to count in the background

  FUNCTIONS :
              [1] 
                INPUTS :    none
                RETURNS :   void
                  a) 
*F ---------------------------------------------------------------------------*/
void StopwatchLap(){
    LCDMEM[4] = digit[minutesHold / 10][0];
    LCDMEM[5] = digit[minutesHold / 10][1];
    LCDMEM[6] = digit[minutesHold % 10][0];
    LCDMEM[7] = digit[minutesHold % 10][1];
 
    LCDMEM[7] |= symbols[0][0];
 
    LCDMEM[8] = digit[secondsHold / 10][0];
    LCDMEM[9] = digit[secondsHold / 10][1];
    LCDMEM[10] = digit[secondsHold % 10][0];
    LCDMEM[11] = digit[secondsHold % 10][1];
    LCDMEM[11] |= symbols[3][0];
 
    LCDMEM[2] = digit[milliSecondsHold / 100][0];
    LCDMEM[3] = digit[milliSecondsHold / 100][1];
    LCDMEM[18] = digit[(milliSecondsHold % 100) / 10][0];
    LCDMEM[19] = digit[(milliSecondsHold % 100) / 10][1];
    //__delay_cycles(8000000);
}

/*F ----------------------------------------------------------------------------
  NAME :      StopwatchRunning.c

  DESCRIPTION :
              Functions to control the stopwatch to be in running mode where it counts up.

  FUNCTIONS :
              [1] 
                INPUTS :    none
                RETURNS :   void
                  a) 
*F ---------------------------------------------------------------------------*/
void StopwatchRun(){
    LCDMEM[4] = digit[stopwatchTime.minutes / 10][0];
    LCDMEM[5] = digit[stopwatchTime.minutes / 10][1];
    LCDMEM[6] = digit[stopwatchTime.minutes % 10][0];
    LCDMEM[7] = digit[stopwatchTime.minutes % 10][1];

    LCDMEM[7] |= symbols[0][0];

    LCDMEM[8] = digit[stopwatchTime.seconds / 10][0];
    LCDMEM[9] = digit[stopwatchTime.seconds / 10][1];
    LCDMEM[10] = digit[stopwatchTime.seconds % 10][0];
    LCDMEM[11] = digit[stopwatchTime.seconds % 10][1];

    LCDMEM[11] |= symbols[3][0];

    LCDMEM[2] = digit[stopwatchTime.milliSeconds / 100][0]; 
    LCDMEM[3] = digit[stopwatchTime.milliSeconds / 100][1]; 
    LCDMEM[18] = digit[(stopwatchTime.milliSeconds % 100) / 10][0]; 
    LCDMEM[19] = digit[(stopwatchTime.milliSeconds % 100) / 10][1]; 
    //__delay_cycles(8000000);
}

/*F ----------------------------------------------------------------------------
  NAME :      StopwatchStopped.c

  DESCRIPTION :
              Functions to control the stopwatch to be in stopped mode where the number shown when button is pressed is retained

  FUNCTIONS :
              [1] 
                INPUTS :    none
                RETURNS :   void
                  a) 
*F ---------------------------------------------------------------------------*/
void StopwatchStopped(){
    LCDMEM[4] = digit[stopwatchTime.minutes / 10][0];
    LCDMEM[5] = digit[stopwatchTime.minutes / 10][1];
    LCDMEM[6] = digit[stopwatchTime.minutes % 10][0];
    LCDMEM[7] = digit[stopwatchTime.minutes % 10][1];

    LCDMEM[7] |= symbols[0][0];

    LCDMEM[8] = digit[stopwatchTime.seconds / 10][0];
    LCDMEM[9] = digit[stopwatchTime.seconds / 10][1];
    LCDMEM[10] = digit[stopwatchTime.seconds % 10][0];
    LCDMEM[11] = digit[stopwatchTime.seconds % 10][1];

    LCDMEM[11] |= symbols[3][0];

    LCDMEM[2] = digit[stopwatchTime.milliSeconds / 100][0]; 
    LCDMEM[3] = digit[stopwatchTime.milliSeconds / 100][1]; 
    LCDMEM[18] = digit[(stopwatchTime.milliSeconds % 100) / 10][0]; 
    LCDMEM[19] = digit[(stopwatchTime.milliSeconds % 100) / 10][1]; 
    //__delay_cycles(8000000);
}

/*F ----------------------------------------------------------------------------
  NAME :      StopwatchNormal.c

  DESCRIPTION :
              Function use to set the stopwatch to 00:00.00. Used for when the stop watch is reset

  FUNCTIONS :
              [1] 
                INPUTS :    none
                RETURNS :   void
                  a) 
*F ---------------------------------------------------------------------------*/
void ZeroStopwatch(){
    LCDMEM[4] = digit[0][0];
    LCDMEM[5] = digit[0][1];
    LCDMEM[6] = digit[0][0];
    LCDMEM[7] = digit[0][1];

    LCDMEM[7] |= symbols[0][0];

    LCDMEM[8] = digit[0][0];
    LCDMEM[9] = digit[0][1];
    LCDMEM[10] = digit[0][0];
    LCDMEM[11] = digit[0][1];

    LCDMEM[11] |= symbols[3][0];

    LCDMEM[2] = digit[0][0]; 
    LCDMEM[3] = digit[0][1]; 
    LCDMEM[18] = digit[0][0]; 
    LCDMEM[19] = digit[0][1]; 
    //__delay_cycles(8000000);
}
