/*H ----------------------------------------------------------------------------
  FILENAME :  ClockAlarm.h

  DESCRIPTION :
              Header file for clocks different alarm states 

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/
#ifndef ClockAlarm_H
#define ClockAlarm_H

#include "Defines.h"
#include "LCD.h"
#include "TimerInterrupt.h"
#include "ButtonInterrupts.h"
#include "TimeDateSettingFSM.h"

extern int alarmState;

void updateAlarmTime();
void alarmToggle();
void alarm();
void snooze();

#endif