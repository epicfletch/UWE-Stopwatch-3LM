/*H ----------------------------------------------------------------------------
  FILENAME :  AlarmSetFSM.h

  DESCRIPTION :
              Header file for Alarm FSM

 AUTHOR :    Louie Williams


 INCLUDES : defines.h

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef AlarmSetFSM_H
#define AlarmSetFSM_H

#include "Defines.h"
#include "TimerInterrupt.h"
#include "ClockAlarm.h"


struct alarmSet
{
  uint8_t minutes;
  uint8_t hours;
};

struct alarmSet setAlarm;

void AlarmSetFSM(void);

#endif