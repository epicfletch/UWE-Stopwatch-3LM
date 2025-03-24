/*F ----------------------------------------------------------------------------
  NAME :      TimeDateSettingFSM.c

  DESCRIPTION :
              Controls what state the Time/Date/Alarm setting mode is in 



  FUNCTIONS :
              [1] Finite state machine for the clock mode
                INPUTS :    none
                RETURNS :   void
                  a) displays the time as 24hr clock and day of the week 
                  b) displays the date
                  c) displays what time the alarm is set to
                  d) toggles on and off the alarm
*F ---------------------------------------------------------------------------*/


#include "TimeDateSettingFSM.h"
#include "Defines.h"



uint8_t TimeDateState = HOUR_SET;

void timeDateSettingFSM()
{
    //LCDCTL0 |= LCD4MUX | LCDON;                                // Turn on LCD, 4-mux selected
    while(1)
    {
        switch (TimeDateState)
        {
            case HOUR_SET:
                break;
            case MIN_SET:
                break;
            case WEEKDAY_SET:
                break;
            case MONTH_SET:
                break;
            case DAY_SET:
                break;
            default:
                break;
        }
    }
}