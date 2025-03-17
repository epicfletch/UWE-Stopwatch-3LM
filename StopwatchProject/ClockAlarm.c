// /*F ----------------------------------------------------------------------------
//   NAME :      ClockAlarm.c

//   DESCRIPTION :
//               Functions to control the behaviour of the clock in its normal state

//   FUNCTIONS :
//               [1] 
//                 INPUTS :    none
//                 RETURNS :   void
//                   a) 
// *F ---------------------------------------------------------------------------*/

#include "ClockAlarm.h"

int alarmState = 0;

void updateAlarmTime(){
    LCDMEM[4] = digit[alarmTime.hours / 10][0];
    LCDMEM[5] = digit[alarmTime.hours / 10][1];
    LCDMEM[6] = digit[alarmTime.hours % 10][0];
    LCDMEM[7] = digit[alarmTime.hours % 10][1];

    LCDMEM[7] |= symbols[0][0];

    LCDMEM[8] = digit[alarmTime.minutes / 10][0];
    LCDMEM[9] = digit[alarmTime.minutes / 10][1];
    LCDMEM[10] = digit[alarmTime.minutes % 10][0];
    LCDMEM[11] = digit[alarmTime.minutes % 10][1];

    LCDMEM[2] = dayOfWeek[2][0];
    LCDMEM[3] = dayOfWeek[2][1];
    LCDMEM[18] = dayOfWeek[2][2];
    LCDMEM[19] = dayOfWeek[2][3];
}

void alarmToggle(){
    if(alarmState == 0){
        alarmState = 1;
        LCDMEM[12] = symbols[1][0];
    }
    else{
        alarmState = 0;
        LCDMEM[12] = 0;
    }
}
void alarm(){

}

void snooze(){
    
}