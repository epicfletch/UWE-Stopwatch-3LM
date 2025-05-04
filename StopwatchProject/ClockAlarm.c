/*F ----------------------------------------------------------------------------
  NAME :      ClockAlarm.c

  DESCRIPTION :
              Functions to control the behaviour of the alarm 

  FUNCTIONS :
              [1] UpdateAlarmTime
                INPUTS :    none
                RETURNS :   void
                  a) sets the LCD display to the set alarm time
              [2] alarmToggle
                INPUTS :    none
                RETURNS :   void
                  a) toggles the alarm symbol 
              [3] Alarm
                INPUTS :    none
                RETURNS :   void
                  a) toogles the green LED on or off to simulate the alarm
              [4] snooze
                INPUTS :    none
                RETURNS :   void
                  a) sets snooze flag
                
*F ---------------------------------------------------------------------------*/

#include "ClockAlarm.h"
#include "TimerInterrupt.h"

int alarmState = 0;

void UpdateAlarmTime(){
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

void AlarmToggle(){
    if(alarmState == 0){
        alarmState = 1;
        LCDMEM[12] = symbols[1][0];
    }
    else{
        alarmState = 0;
        LCDMEM[12] = 0;
    }
}
void Alarm(){
    P4OUT ^= RED_LED;          
    __delay_cycles(8000000); 
}

void Snooze(){
    snoozeFlag = 1;
}