/*H ----------------------------------------------------------------------------
  FILENAME :  HardwareSetup.h

  DESCRIPTION :
              Header file for microcontroller hardware setup 

 AUTHOR :     Josh Fletcher


 INCLUDES :
              <msp430.h>        standard I/O defintions for the MSP430
              "Defines"         all project defines

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef HardwareSetup_H
#define HardwareSetup_H

#include "Defines.h"

void DisableWatchdog();

void SetupClock();

void SetupGPIO();

void SetupButtonInterrupts();

void SetupTimerInterrupt();

void SetupLCD();

#endif