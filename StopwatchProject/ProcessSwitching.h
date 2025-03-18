/*H ----------------------------------------------------------------------------
  FILENAME :  HardwareSetup.h

  DESCRIPTION :
              Header file for microcontroller hardware setup 

 AUTHOR :     Joerg Mossbrucker
              Josh Fletcher


 INCLUDES :
              <msp430.h>        standard I/O defintions for the MSP430
              "Defines"         all project defines

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef ProcessSwitching_H
#define ProcessSwitching_H

#include "Defines.h"

struct ProcessControlBlock
{
  uint32_t sp;
  uint8_t stack[STACK_SIZE];
};

extern struct ProcessControlBlock process[MAX_PROCESSES];

extern uint32_t status;
extern uint32_t stack_pointer;
extern uint32_t program_counter;
extern uint32_t saved_sp;

extern uint8_t current_process;

extern uint16_t pc1;
extern uint16_t pc2;

void initialiseProcess(unsigned int process_index, void (*funct)());

void runProcess(unsigned int process_index);

void ProcessSwitching();

#endif