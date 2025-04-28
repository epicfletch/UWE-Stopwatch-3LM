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
*F ---------------------------------------------------------------------------*/

#include "ClockFSM.h"
#include "Chime.h"
#include "ClockAlarm.h"
#include "Defines.h"
<<<<<<< HEAD
#include "msp430fr4133.h"
#include "Date.h"
#include "ProcessSwitching.h"
#include "TimeDateSettingFSM.h"
=======
>>>>>>> 4b1903dc933d8dd1d6f2eaa7959d490bd8c47b87

uint8_t clockState = CLOCK_NORMAL;
int chimeToggleFlag = 0;

void clockFSM(){
    while(1){
        if(chimeToggleFlag == 1){
            clockState = CLOCK_CHIME_TOGGLE;
            chimeToggleFlag = 0;
        }    
        switch (clockState){
            case CLOCK_NORMAL: /* normal clock display */
                updateClock();
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
                updateDate();
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
                updateAlarmTime();
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
                alarmToggle();
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
                chimeToggle();
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
                    alarm();
                    if(lapResetFlag == 1){
                        snooze();
                    }    
                }
                else{}
                clockState = CLOCK_NORMAL;
                break;
            case CLOCK_CHIME:
                if(chimeState == 1){
                    chime();
                }
                else{}
                clockState = CLOCK_NORMAL;
                break;
            default:
        }
        if(modeFlag == 1){
        //processSwitching();
        //runProcess(current_process);
        //timeDateSettingFSM();
        modeFlag = 0;
        }
    }
}