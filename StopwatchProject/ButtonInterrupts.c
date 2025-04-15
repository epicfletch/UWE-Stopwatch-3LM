/*F ----------------------------------------------------------------------------
  NAME :      ButtonInterrupts.c

  DESCRIPTION :
              Handles button interupts

  FUNCTIONS :
              [1] Mode button interrupt handler
              [2] Start/stop button interrupt handler
              [3] lap/reset interrupt handler


*F ---------------------------------------------------------------------------*/

#include "ButtonInterrupts.h"
#include "ClockFSM.h"
#include "Defines.h"

int startStopFlag = 0;
int lapResetFlag = 0;
int modeFlag = 0;


#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void){
  __bic_SR_register(GIE);   /* Clear GIE bit, disabling interrupts */
  __delay_cycles(2500000);  /* delay for 1/8 of a second to handle switch bounce */

  if ((P1IFG & MODE))
  {
    if(!(P1IN & START_STOP)){
      chimeToggleFlag = 1;
    }
    else{
      processSwitching();
    }
  }
  else
  {
    startStopFlag = 1;
  }

  P1IFG = 0;         /* Clear interrupt flag */
  __bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void){
  __bic_SR_register(GIE);   /* Clear GIE bit, disabling interrupts */
  __delay_cycles(2500000);  /* delay for 1/8 of a second to handle switch bounce */

  lapResetFlag  = 1;

  P2IFG = 0;         /* Clear interrupt flag */
  __bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}