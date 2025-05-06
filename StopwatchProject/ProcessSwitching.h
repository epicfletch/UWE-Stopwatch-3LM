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

#define EMPTY 0

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

extern volatile uint8_t g_buffer;

extern uint16_t pc1;
extern uint16_t pc2;

void InitialiseProcess(unsigned int process_index, void (*funct)());

void RunProcess(unsigned int process_index);

void ProcessSwitching();

/* message passing functions from example code in blackboard*/
void send(uint8_t *buffer, uint8_t message);

uint8_t receive(uint8_t *buffer);

#endif