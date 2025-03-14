/*F ----------------------------------------------------------------------------
  NAME :      ClockFSM.c

  DESCRIPTION :
              Controls what state the clock mode is in 



  FUNCTIONS :
              [1] Finite state machine for the clock mode
                INPUTS :    none
                RETURNS :   void
                  a) displays the time as 24hr clock and day of the week 
                  b) displays the date
                  c) displays what time the alarm is set to
                  d) toggles on and off the alarm
*F ---------------------------------------------------------------------------*/

#include "Stopwatch.h"



uint8_t clockState = CLOCK_NORMAL;

void clockFSM(){
    LCDCTL0 |= LCD4MUX | LCDON;                                // Turn on LCD, 4-mux selected
    while(1){
        switch (clockState){
            case CLOCK_NORMAL:
                updateDisplay();
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
}