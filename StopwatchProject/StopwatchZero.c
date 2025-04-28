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

#include "StopwatchZero.h"

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
