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
#include "ClockFSM.h"

void main (void){
  _BIC_SR(GIE);                   /* interrupts disabled */
  /* initialise hardware */
  DisableWatchdog();
  SetupClock();
  SetupGPIO();
  SetupButtonInterrupts();
  SetupTimerInterrupt();
  SetupLCD();

<<<<<<< HEAD
  // _BIS_SR(GIE);
  // Testing the merge
  // clockFSM();
=======
>>>>>>> 05e0d428f2549278daf9563845e25032aa7ece15
  P1IFG = 0;         /* Clear interrupt flag */
  _BIS_SR(GIE);                   // interrupts enabled (we need to do it here so it gets saved to stack)

  initialise_process(0, clockFSM);

  run_process(current_process);

  _BIS_SR(GIE);                   /* interrupts enabled */
  for (;;)
  {

  }
}
