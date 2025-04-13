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
#include "ButtonInterrupts.h"
#include "ClockFSM.h"
#include "TimeDateSettingFSM.h"

void main (void){
  _BIC_SR(GIE);                   /* interrupts disabled */
  /* initialise hardware */
  DisableWatchdog();
  SetupClock();
  SetupGPIO();
  SetupButtonInterrupts();
  SetupTimerInterrupt();
  SetupLCD();

  P1IFG = 0;         /* Clear interrupt flag */
  _BIS_SR(GIE);                   // interrupts enabled (we need to do it here so it gets saved to stack)

  initialiseProcess(0, clockFSM);
  initialiseProcess(1, timeDateSettingFSM);

  runProcess(current_process);

  _BIS_SR(GIE);                   /* interrupts enabled */
  for (;;)
  {

  }
}