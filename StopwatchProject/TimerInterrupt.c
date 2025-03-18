/*F ----------------------------------------------------------------------------
  NAME :      TimerInterrupt.c

  DESCRIPTION :
              Handles 10ms interrupt from timer and time units rollover

  FUNCTIONS :
              [1] Timer A0 interrupt handler
                INPUTS :    none
                RETURNS :   void
                  a) disable interrupts
                  b) increment time by 10ms
                  c) handle rollover for milliseconds
                  d) handle rollover for seconds
                  e) handle rollover for minutees
                  f) handle rollover for hours
                  g) enable interrupts

*F ---------------------------------------------------------------------------*/

#include "TimerInterrupt.h"

uint8_t weekday = 0;

struct time clockTime = {0, 0, 0};
struct time stopwatchTime = {0, 0, 0};
struct time alarmTime = {0, 0, 0};

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)    // Timer0 A0 1ms interrupt service routine
{
  __bic_SR_register(GIE); /* Clear GIE bit, disabling interrupts */

  clockTime.milliSeconds += 10; /* add 10ms to the ms count */
  /* increment time units and deal with rollovers */
  if (clockTime.milliSeconds >= 1000){
   clockTime.milliSeconds = 0;
    clockTime.seconds++;
    if (clockTime.seconds >= 60){
      clockTime.seconds = 0;
      clockTime.minutes++;
      if(clockTime.minutes >= 60){
        clockTime.minutes = 0;
        clockTime.hours++;
        if(clockTime.hours >= 24){
          clockTime.hours = 0;
        }
      }
    }
  }
  __bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}