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

int startStopFlag = 0;
int lapResetFlag = 0;
int modeFlag = 0;

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void){
  __bic_SR_register(GIE);   /* Clear GIE bit, disabling interrupts */
  __delay_cycles(2000000);  /* delay for 1/8 of a second to handle switch bounce */

   if ((P1IFG & MODE)) // checking if it was mode button that was pressed on interrupt vector 1
  {
      asm(
          " push.a R10\n"
          " push.a R9\n"
          " push.a R8\n"
          " push.a R7\n"
          " push.a R6\n"
          " push.a R5\n"
          " push.a R4\n"
          " push.a R3\n"
          " movx.a sp,&stack_pointer\n"
      );

  process[current_process].sp = stack_pointer;

  current_process = (current_process+1) % MAX_PROCESSES;

  stack_pointer = process[current_process].sp;

  asm(
          " movx.a &stack_pointer,SP \n"
          " pop.a R3 \n"
          " pop.a R4 \n"
          " pop.a R5 \n"
          " pop.a R6 \n"
          " pop.a R7 \n"
          " pop.a R8 \n"
          " pop.a R9 \n"
          " pop.a R10 \n"
  );
  }
  else
  {
    startStopFlag = 1;
  }
  P1IFG = 0;         /* Clear interrupt flag */
  _bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void){
  __bic_SR_register(GIE);   /* Clear GIE bit, disabling interrupts */
  __delay_cycles(2000000);  /* delay for 1/8 of a second to handle switch bounce */

  lapResetFlag  = 1;

  P2IFG = 0;         /* Clear interrupt flag */
  __bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}