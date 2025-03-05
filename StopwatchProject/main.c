/*H ----------------------------------------------------------------------------
  FILENAME :  main.c

  DESCRIPTION :
              Main function for UWE stopwatch project

 AUTHOR :     Josh Fletcher


 INCLUDES :
              "HardwareSetup" 

 CHANGES :

*H ---------------------------------------------------------------------------*/
int testing;

#include "HardwareSetup.h"
#include "ProcessSwitching.h"
#include "Clock.h"

void main (void){
  /* initialise hardware */
  DisableWatchdog();
  SetupClock();
  SetupGPIO();
  SetupButtonInterrupts();
  SetupTimerInterrupt();
}
