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
#include "ProcessSwitching.h"
#include "TimeDateSettingFSM.h"
#include "AlarmSetFSM.h"
#include "StopwatchFSM.h"

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

  
  
  InitialiseProcess(0, ClockFSM);
  InitialiseProcess(1, TimeDateSettingFSM);
  InitialiseProcess(2, AlarmSetFSM);
  InitialiseProcess(3, StopwatchFSM);
  RunProcess(current_process); 

  _BIS_SR(GIE);                   /* interrupts enabled */
  for (;;)
  {

  }
}