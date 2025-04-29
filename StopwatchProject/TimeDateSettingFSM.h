/*H ----------------------------------------------------------------------------
  FILENAME :  TimeDateSettingFSM.h

  DESCRIPTION :
              Header file for Time/date setting FSM

 AUTHOR :     Louie Williams


 INCLUDES : defines.h, 

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


struct timeSet
{
  uint8_t month;
  uint8_t weekDay;
  uint8_t day;
  uint8_t minutes;
  uint8_t hours;
};

struct timeSet setTime;
void timeDateSettingFSM(void);

#endif