/*H ----------------------------------------------------------------------------
  FILENAME :  ButtonInterrupts.h

  DESCRIPTION :
              Header file for button interrupts 

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/

#include "ProcessSwitching.h"

#ifndef ButtonInterrupts_H
#define ButtonInterrupts_H

extern int startStopFlag;
extern int lapResetFlag;

__interrupt void PORT1_ISR(void);

__interrupt void PORT2_ISR(void);

#endif