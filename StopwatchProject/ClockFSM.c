/*F ----------------------------------------------------------------------------
  NAME :      ClockFSM.c

  DESCRIPTION :
              Controls what state the clock mode is in 

  INPUTS :    none

  RETURNS :   void

  FUNCTIONS :
              [1]

*F ---------------------------------------------------------------------------*/

#include "ClockFSM.h"
#include "Defines.h"

uint8_t clockState = CLOCK_NORMAL;

void clockFSM(){
    switch (clockState){
        case CLOCK_NORMAL:
            
            break;
        case CLOCK_DATE:

            break;
        case CLOCK_ALARM_TIME:

            break;
        case CLOCK_ALARM_TOGGLE:

            break;
        default:
    }
}