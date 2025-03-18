/*F ----------------------------------------------------------------------------
  NAME :      ClockNormal.c

  DESCRIPTION :
              Functions to control the behaviour of the clock in its normal state

  FUNCTIONS :
              [1] 
                INPUTS :    none
                RETURNS :   void
                  a) 
*F ---------------------------------------------------------------------------*/

#include "ClockNormal.h"

void updateClock(){
    LCDMEM[4] = digit[clockTime.hours / 10][0];
    LCDMEM[5] = digit[clockTime.hours / 10][1];
    LCDMEM[6] = digit[clockTime.hours % 10][0];
    LCDMEM[7] = digit[clockTime.hours % 10][1];

    LCDMEM[7] |= symbols[0][0];

    LCDMEM[8] = digit[clockTime.minutes / 10][0];
    LCDMEM[9] = digit[clockTime.minutes / 10][1];
    LCDMEM[10] = digit[clockTime.minutes % 10][0];
    LCDMEM[11] = digit[clockTime.minutes % 10][1];

    LCDMEM[2] = dayOfWeek[weekday][0];
    LCDMEM[3] = dayOfWeek[weekday][1];
    LCDMEM[18] = dayOfWeek[weekday][2];
    LCDMEM[19] = dayOfWeek[weekday][3];
    //__delay_cycles(8000000);
}