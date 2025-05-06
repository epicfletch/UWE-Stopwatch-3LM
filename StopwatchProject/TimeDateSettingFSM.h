/*H ----------------------------------------------------------------------------
  FILENAME :  TimeDateSettingFSM.h

  DESCRIPTION :
              Header file for Time/date setting FSM

 AUTHOR :     Louie Williams


 INCLUDES : Defines.h,
ButtonInterrupts.h
LCD.h
Date.h
HardwareSetup.h
board.h
TimerInterrupt.h
msp430fr4133.h

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef TimeDateSettingFSM_H
#define TimeDateSettingFSM_H
#include "ButtonInterrupts.h"
#include "Defines.h"
#include "LCD.h"
#include "Date.h"
#include "HardwareSetup.h"
#include "board.h"
#include "TimerInterrupt.h"
#include "msp430fr4133.h"

/* structure for the set time which is assigned to the clock time and displayed on the LCD in clock mode*/
struct timeSet
{
  uint8_t month;
  uint8_t weekDay;
  uint8_t day;
  uint8_t minutes;
  uint8_t hours;
};


struct timeSet setTime;
void TimeDateSettingFSM(void);

#endif