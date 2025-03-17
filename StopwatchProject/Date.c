// /*F ----------------------------------------------------------------------------
//   NAME :      Date.c

//   DESCRIPTION :
//               Functions to control the behaviour of the date

//   FUNCTIONS :
//               [1] 
//                 INPUTS :    none
//                 RETURNS :   void
//                   a) 
// *F ---------------------------------------------------------------------------*/

#include "Date.h"

void updateDate(){
    LCDMEM[4] = digit[alarmTime.hours / 10][0];
    LCDMEM[5] = digit[alarmTime.hours / 10][1];
    LCDMEM[6] = digit[alarmTime.hours % 10][0];
    LCDMEM[7] = digit[alarmTime.hours % 10][1];

    LCDMEM[7] |= symbols[3][0];

    LCDMEM[8] = digit[alarmTime.minutes / 10][0];
    LCDMEM[9] = digit[alarmTime.minutes / 10][1];
    LCDMEM[10] = digit[alarmTime.minutes % 10][0];
    LCDMEM[11] = digit[alarmTime.minutes % 10][1];

    LCDMEM[11] |= symbols[3][0];

    LCDMEM[2] = dayOfWeek[2][0];
    LCDMEM[3] = dayOfWeek[2][1];
    LCDMEM[18] = dayOfWeek[2][2];
    LCDMEM[19] = dayOfWeek[2][3];
}
