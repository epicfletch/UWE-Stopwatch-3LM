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
                  d) toggles on and off the chime
                  e) alarm is active 
                  f) chime is active
*F ---------------------------------------------------------------------------*/

#include "ClockFSM.h"
#include "Chime.h"
#include "ClockAlarm.h"
#include "Defines.h"

uint8_t clockState = CLOCK_NORMAL;
int chimeToggleFlag = 0;
int chimeFlag = 0;

void ClockFSM(){
    while(1){
        if(chimeToggleFlag == 1){
            clockState = CLOCK_CHIME_TOGGLE;
            chimeToggleFlag = 0;
        }   
        if(chimeFlag == 1){
            clockState = CLOCK_CHIME;
            chimeFlag = 0;
        }        
        switch (clockState){
            case CLOCK_NORMAL: /* normal clock display */
                UpdateClock();
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
                UpdateDate();
                /* determine transitions */
                if(P1IN & START_STOP){
                    clockState = CLOCK_NORMAL; 
                }
                else{
                    if(modeFlag == 1){
                        clockState = CLOCK_CHIME_TOGGLE;
                        modeFlag = 0;
                    }
                    clockState = CLOCK_DATE;
                }
                break;
            case CLOCK_ALARM_TIME: /* displays the alarm time */
                UpdateAlarmTime();
                /* determine transitions */
                if(P2IN & LAP_RESET){
                    clockState = CLOCK_NORMAL;
                }
                else{
                    if(startStopFlag == 1){
                        startStopFlag = 0;
                        clockState = CLOCK_ALARM_TOGGLE;
                    }
                    else{
                        clockState = CLOCK_ALARM_TIME;
                    }
                }
                break;
            case CLOCK_ALARM_TOGGLE: /* toggles alarm on and off */
                AlarmToggle();
                /* determine transitions */
                
                if(P2IN & LAP_RESET){
                    clockState = CLOCK_NORMAL;
                }
                else {
                    if(startStopFlag == 1){
                        startStopFlag = 0;
                        clockState = CLOCK_ALARM_TOGGLE;
                    }
                    else{
                        clockState = CLOCK_ALARM_TIME;
                    }
                }

                break;
            case CLOCK_CHIME_TOGGLE: /* toggles chime on and off */
                ChimeToggle();
                /* determine transitions */
                if(!(P1IN & START_STOP)){
                    clockState = CLOCK_DATE;
                }
                else{
                    clockState = CLOCK_NORMAL;
                }
                break;
            case CLOCK_ALARM:
                if(alarmState == 1){
                    Alarm();
                    if(lapResetFlag == 1){
                        Snooze();
                        clockState = CLOCK_NORMAL;
                    }    
                }
                else{}
                clockState = CLOCK_NORMAL;
                break;
            case CLOCK_CHIME:
                if(chimeState == 1){
                    Chime();
                }
                clockState = CLOCK_NORMAL;
                break;
            default:
        }
    }
}