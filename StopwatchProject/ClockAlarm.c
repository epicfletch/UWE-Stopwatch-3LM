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
<<<<<<< HEAD
#include "TimeDateSettingFSM.h"
=======
#include "TimerInterrupt.h"
>>>>>>> 4b1903dc933d8dd1d6f2eaa7959d490bd8c47b87

int alarmState = 0;

void updateAlarmTime(){
    LCDMEM[4] = digit[alarmTime.hours / 10][0];
    LCDMEM[5] = digit[alarmTime.hours / 10][1];
    LCDMEM[6] = digit[alarmTime.hours % 10][0];
    LCDMEM[7] = digit[alarmTime.hours % 10][1];

    LCDMEM[7] |= symbols[0][0];

    LCDMEM[8] = digit[alarmTime.minutes / 10][0];
    LCDMEM[9] = (LCDMEM[9] & 0b00000100) | (digit[alarmTime.minutes / 10][1] & ~0b00000100);
    LCDMEM[10] = digit[alarmTime.minutes % 10][0];
    LCDMEM[11] = digit[alarmTime.minutes % 10][1];

    LCDMEM[2] = dayOfWeek[setTime.weekDay][0];
    LCDMEM[3] = dayOfWeek[setTime.weekDay][1];
    LCDMEM[18] = dayOfWeek[setTime.weekDay][2];
    LCDMEM[19] = dayOfWeek[setTime.weekDay][3];
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
    P4OUT ^= GREEN_LED;               // Set P4.0 on  (Green LED)
    __delay_cycles(8000000); 
}

void snooze(){
    snoozeFlag = 1;
}