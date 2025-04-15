/*H ----------------------------------------------------------------------------
  FILENAME :  TimerInterrupt.h

  DESCRIPTION :
              Header file for Clock 

 AUTHOR :     Josh Fletcher & Ethan Evans


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef TimerInterrupt_H
#define TimerInterrupt_H

#include "Defines.h"


extern uint8_t weekday;

struct time
{
  uint16_t milliSeconds;
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
};

extern struct time clockTime;
extern struct time stopwatchTime;
extern struct time alarmTime;


__interrupt void Timer0_A0 (void);

#endif