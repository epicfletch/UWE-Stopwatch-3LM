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

#include "StopwatchLap.h"

// Digit values to display (these hold the frozen snapshot)
unsigned char minutesOne, minutesTwo, minutesThree, minutesFour;
unsigned char secondsOne, secondsTwo, secondsThree, secondsFour;
unsigned char millisecondsOne, millisecondsTwo, millisecondsThree, millisecondsFour;
 
void stopwatchLapValue(){
    minutesOne = digit[stopwatchTime.minutes / 10][0];
    minutesTwo = digit[stopwatchTime.minutes / 10][1];
    minutesThree = digit[stopwatchTime.minutes % 10][0];
    minutesFour = digit[stopwatchTime.minutes % 10][1];
 
    secondsOne = digit[stopwatchTime.seconds / 10][0];
    secondsTwo = digit[stopwatchTime.seconds / 10][1];
    secondsThree = digit[stopwatchTime.seconds % 10][0];
    secondsFour = digit[stopwatchTime.seconds % 10][1];
 
    millisecondsOne = digit[stopwatchTime.milliSeconds / 100][0];
    millisecondsTwo = digit[stopwatchTime.milliSeconds / 100][1];
    millisecondsThree = digit[(stopwatchTime.milliSeconds % 100) / 10][0];
    millisecondsFour = digit[(stopwatchTime.milliSeconds % 100) / 10][1];
}
 
void stopwatchLap(){
    LCDMEM[4] = minutesOne;
    LCDMEM[5] = minutesTwo;
    LCDMEM[6] = minutesThree;
    LCDMEM[7] = minutesFour;
 
    LCDMEM[7] |= symbols[0][0];
 
    LCDMEM[8] = secondsOne;
    LCDMEM[9] = secondsTwo;
    LCDMEM[10] = secondsThree;
    LCDMEM[11] = secondsFour;
 
    LCDMEM[11] |= symbols[3][0];
 
    LCDMEM[2] = millisecondsOne;
    LCDMEM[3] = millisecondsTwo;
    LCDMEM[18] = millisecondsThree;
    LCDMEM[19] = millisecondsFour;
    //__delay_cycles(8000000);
}