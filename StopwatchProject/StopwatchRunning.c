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

#include "StopwatchRunning.h"

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
