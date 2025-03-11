/*H ----------------------------------------------------------------------------
  FILENAME :  Clock.h

  DESCRIPTION :
              Header file for Clock 

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef Clock_H
#define Clock_H

#include "Defines.h"

extern uint16_t milliSeconds;
extern uint8_t seconds;
extern uint8_t minutes;
extern uint8_t hours;

__interrupt void Timer0_A0 (void);

#endif