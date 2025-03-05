/*F ----------------------------------------------------------------------------
  NAME :      Clock.c

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

#include "Clock.h"

uint16_t milliSeconds = 0;
uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hours = 0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)    // Timer0 A0 1ms interrupt service routine
{
  __bic_SR_register(GIE); /* Clear GIE bit, disabling interrupts */

  milliSeconds += 10; /* add 10ms to the ms count */
  /* increment time units and deal with rollovers */
  if (milliSeconds >= 1000){
    milliSeconds = 0;
    seconds++;
    if (seconds >= 60){
      seconds = 0;
      minutes++;
      if(minutes >= 60){
        minutes = 0;
        hours++;
        if(hours >= 24){
          hours = 0;
        }
      }
    }
  }

  __bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}