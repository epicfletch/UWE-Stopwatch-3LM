/*H ----------------------------------------------------------------------------
  FILENAME :  main.c

  DESCRIPTION :
              Main function for UWE stopwatch project

 AUTHOR :     Josh Fletcher


 INCLUDES :
              "HardwareSetup" 

 CHANGES :

*H ---------------------------------------------------------------------------*/
#include "HardwareSetup.h"
#include "ProcessSwitching.h"
#include "ClockFSM.h"

void main (void){
  _BIC_SR(GIE);                   /* interrupts disabled */
  /* initialise hardware */
  DisableWatchdog();
  SetupClock();
  SetupGPIO();
  //SetupButtonInterrupts();
  SetupTimerInterrupt();
  SetupLCD();

  // _BIS_SR(GIE);
  // Testing the merge
  // clockFSM();
  P1IFG = 0;         /* Clear interrupt flag */
  _BIS_SR(GIE);                   // interrupts enabled (we need to do it here so it gets saved to stack)

  initialise_process(0, clockFSM);

  run_process(current_process);

  _BIS_SR(GIE);                   /* interrupts enabled */
  for (;;)
  {

  }
}
