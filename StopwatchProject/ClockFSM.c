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

#include "ClockFSM.h"
#include "Defines.h"
#include "msp430fr4133.h"

uint8_t clockState = CLOCK_NORMAL;

void clockFSM(){
    while(1){
        switch (clockState){
            case CLOCK_NORMAL: /* normal clock display */
                updateDisplay();
                /* determine transitions */
                if(startStopFlag == 1){
                    clockState = CLOCK_DATE;
                    startStopFlag = 0;
                }
                else if(lapResetFlag == 1){
                    clockState = CLOCK_ALARM_TIME;
                    lapResetFlag = 0;
                }
                else {
                    clockState = CLOCK_NORMAL;
                }
                break;
            case CLOCK_DATE: /* displays the date */
                /* determine transitions */
                if(P1IN & START_STOP){
                    clockState = CLOCK_DATE;
                }
                else{
                    clockState = CLOCK_NORMAL;
                }
                break;
            case CLOCK_ALARM_TIME: /* displays the alarm time */
                /* determine transitions */
                if(P2IN & LAP_RESET){
                    if(P1IN & START_STOP){
                        clockState = CLOCK_ALARM_TOGGLE;
                    }
                    clockState = CLOCK_ALARM_TIME;
                }
                else{
                    clockState = CLOCK_NORMAL;
                }
                break;
            case CLOCK_ALARM_TOGGLE: /* toggles alarm on and off */
                /* determine transitions */
                if(P2IN & LAP_RESET){
                    if(startStopFlag == 1){
                        startStopFlag = 0;
                        clockState = CLOCK_ALARM_TOGGLE;

                    }
                    else{
                        clockState = CLOCK_ALARM_TIME;
                    }
                }
                else {
                    clockState = CLOCK_NORMAL;
                }
                break;
            case CLOCK_ALARM:
            
                break;
            default:
        }
    }
}
