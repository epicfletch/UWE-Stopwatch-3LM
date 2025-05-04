/*F ----------------------------------------------------------------------------
 
  NAME        : TimerInterrupt.c
 
  DESCRIPTION :
      Handles 10ms interrupt from timer and updates clock and stopwatch time.
      handles alarm and snooze
      Manages time unit rollovers and adjusts stopwatch behavior based on its
      current state.
 
  AUTHOR      : Josh Fletcher & Ethan Evans
 
  FUNCTIONS   :
      [1] Timer A0 interrupt handler
          INPUTS  : none
          RETURNS : void
            a) Disable interrupts
            b) Increment clock time by 10ms
            c) Handle rollover for milliseconds, seconds, minutes, and hours
            d) handles alarm and snooze time
            d) Update stopwatch time if in RUNNING or LAP state
            e) Reset stopwatch if in ZERO state
            f) Handle rollover for stopwatch time units
            g) Enable interrupts
 
*F ---------------------------------------------------------------------------*/

#include "TimerInterrupt.h"
#include "ClockFSM.h"
#include "Defines.h"
#include "StopwatchFSM.h"
#include "TimeDateSettingFSM.h"

uint8_t weekday = 0;


struct time clockTime = {0, 0, 0, 0};
struct time stopwatchTime = {0, 0, 0, 0};
struct time alarmTime = {0, 0, 0, 1};

int i = 0;
int j = 0;
int snoozeFlag = 0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)    // Timer0 A0 10ms interrupt service routine
{
  __bic_SR_register(GIE); /* Clear GIE bit, disabling interrupts */
  if((clockTime.hours == alarmTime.hours) && (clockTime.minutes == alarmTime.minutes)){
    clockState = CLOCK_ALARM;
  }

  clockTime.milliSeconds += 10; /* add 10ms to the ms count */
  /* increment time units and deal with rollovers */
  if (clockTime.milliSeconds >= 1000){
   clockTime.milliSeconds = 0;
    clockTime.seconds++;
    if (clockTime.seconds >= 60){
      if(clockState == CLOCK_ALARM){
        i++;
        if(i > 60){
          clockState == CLOCK_NORMAL;
        }
      }
      if (snoozeFlag == 1){
        j++;
        if(j > 300){
          clockState = CLOCK_ALARM;
          snoozeFlag = 0;
        }
      }
      clockTime.seconds = 0;
      clockTime.minutes++;
      if(clockTime.minutes >= 60){
        clockTime.minutes = 0;
        clockTime.hours++;
        chimeFlag = 1;
        if(clockTime.hours >= 24){
          clockTime.hours = 0;
          setTime.day++;
          setTime.weekDay++;
        }
      }
    }
  }
  
  if ((stopwatchState == STOPWATCH_RUNNING) ||(stopwatchState == STOPWATCH_LAP)){
    stopwatchTime.milliSeconds += 10; /* add 10ms to the ms count */
  }
  else if(stopwatchState == STOPWATCH_ZERO){
    stopwatchTime.milliSeconds = 0;
    stopwatchTime.seconds = 0;
    stopwatchTime.minutes = 0;
  }
  /* increment time units and deal with rollovers */
  if (stopwatchTime.milliSeconds >= 1000){
    stopwatchTime.milliSeconds = 0;
    stopwatchTime.seconds++;
    if (stopwatchTime.seconds >= 60){
      stopwatchTime.seconds = 0;
      stopwatchTime.minutes++;
      if(stopwatchTime.minutes >= 99){
        stopwatchTime.minutes = 0;
        }
      }
    }
  __bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}