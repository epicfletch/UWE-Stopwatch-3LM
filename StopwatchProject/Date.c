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
#include "TimeDateSettingFSM.h"

void updateDate(){
    LCDMEM[4] = digit[setTime.month / 10][0];
    LCDMEM[5] = digit[setTime.month / 10][1];
    LCDMEM[6] = digit[setTime.month % 10][0];
    LCDMEM[7] = digit[setTime.month % 10][1];

    LCDMEM[7] |= symbols[3][0];

    LCDMEM[8] = digit[setTime.day / 10][0];
    LCDMEM[9] = digit[setTime.day / 10][1];
    LCDMEM[10] = digit[setTime.day % 10][0];
    LCDMEM[11] = digit[setTime.day % 10][1];

    LCDMEM[11] |= symbols[3][0];

    LCDMEM[2] = dayOfWeek[setTime.weekDay][0];
    LCDMEM[3] = dayOfWeek[setTime.weekDay][1];
    LCDMEM[18] = dayOfWeek[setTime.weekDay][2];
    LCDMEM[19] = dayOfWeek[setTime.weekDay][3];
}
