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

#include "msp430fr4133.h"
#include <msp430.h>
#include "Defines"

void DisableWatchdog();

void SetupClock();

void SetupGPIO();

void SetupButtonInterrupts();

void SetupTimerInterrupt();

#endif