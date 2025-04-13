/*H ----------------------------------------------------------------------------
  FILENAME :  ButtonInterrupts.h

  DESCRIPTION :
              Header file for button interrupts 

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/



#ifndef ButtonInterrupts_H
#define ButtonInterrupts_H

#include "ProcessSwitching.h"

extern int startStopFlag;
extern int lapResetFlag;
extern int modeFlag;

__interrupt void PORT1_ISR(void);

__interrupt void PORT2_ISR(void);

#endif