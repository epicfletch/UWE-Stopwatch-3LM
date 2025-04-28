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
<<<<<<< HEAD
#include "ProcessSwitching.h"
#include "TimeDateSettingFSM.h"
#include "TOPLevelFSM.h"
#include "AlarmSetFSM.h"
=======
#include "StopwatchFSM.h"
>>>>>>> 4b1903dc933d8dd1d6f2eaa7959d490bd8c47b87

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

<<<<<<< HEAD
  
  
  initialiseProcess(0, clockFSM);
  initialiseProcess(1, timeDateSettingFSM);
  initialiseProcess(2, alarmSetFSM);
  runProcess(current_process); 
  //runProcess(current_process);
=======
  initialiseProcess(0, stopwatchFSM);

  runProcess(current_process);
>>>>>>> 4b1903dc933d8dd1d6f2eaa7959d490bd8c47b87

  _BIS_SR(GIE);                   /* interrupts enabled */
  for (;;)
  {

  }
}