/*F ----------------------------------------------------------------------------
  NAME :      HardwareSetup.c

  DESCRIPTION :
              Functions file for microcontroller hardware setup

  INPUTS :    none

  RETURNS :   void

  FUNCTIONS :
              [1]   Disable watchdog function
              [2]   Setup clock with 16MHz frequency
              [3]   Setup LED and Button GPIO pins
              [4]   Setup interrupt on button press
              [5]   Setup timer interrupt with 10ms frequency

*F ---------------------------------------------------------------------------*/

#include "HardwareSetup.h"

DisableWatchdog(){
  WDTCTL = WDTPW | WDTHOLD; /* Disable watchdog timer */
}

SetupClock(){
  /* sets clock speed to 16MHz*/
  __bis_SR_register(SCG0);                   /* Disable FLL */
  
  CSCTL0 = 0x00;                             /* Clear DCO and MOD bits */
  CSCTL1 |= DCORSEL_5;                       /* Set DCO = 16MHz */
  CSCTL2 = FLLD_0 + 487;                     /* DCOCLKDIV = 16MHz */
  CSCTL3 = SELREF__REFOCLK;                  /* Set REFO as FLL reference source */

  __delay_cycles(3);
  __bic_SR_register(SCG0);                   /* Enable FLL */
  while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); /* FLL locked */
}

SetupGPIO(){
  /* setup LEDs */
  P1DIR |=  RED_LED;                 /* Set P1.0 to output direction */
  P4DIR |=  GREEN_LED;                 /* Set P4.0 to output direction */
  P1OUT &= ~RED_LED;                 /* Set P1.0 off (Red LED) */
  P4OUT &= ~GREEN_LED;                 /* Set P4.0 off (Green LED) */

  /* setup input buttons */
  P1DIR &= ~START_STOP;             /* Set P1.2 as input */
  P1REN |= START_STOP;              /* Enable pull-up/down resistor */
  P1OUT |= START_STOP;              /* Select pull-up resistor */

  P1DIR &= ~LAP_RESET;             /* Set P2.6 as input */
  P1REN |= LAP_RESET;              /* Enable pull-up/down resistor */
  P1OUT |= LAP_RESET;              /* Select pull-up resistor */
}

SetupButtonInterrupts(){
  P1IE  |= START_STOP;              /* Enable interrupt on P1.2 */
  P1IES |= START_STOP;              /* Trigger on falling edge (button press) */
  P1IFG &= ~START_STOP;             /* Clear any pending interrupt flag */
}

SetupTimerInterrupt(){
  TA0CCR0 =  20000;     /* set compare value 20000 (10ms @ 2MHz) */
  TA0CCTL0 = 0x10;      /* Enable counter interrupts, bit 4=1 */
  TA0CTL |=  TASSEL_2;  /* use SMCLK as source */
  TA0CTL |=  MC_1;      /* count up to CCR0 */
  TA0CTL |=  ID_3;      /* /8 predivider (16MHz -> 2MHz clock) */
}



