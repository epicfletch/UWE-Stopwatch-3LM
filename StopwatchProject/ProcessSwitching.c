/*F ----------------------------------------------------------------------------
  NAME :      ProcessSwitching.c

  DESCRIPTION :

  FUNCTIONS :
              [1]
              INPUTS :    none
              RETURNS :   void

*F ---------------------------------------------------------------------------*/

#include "ProcessSwitching.h"
struct ProcessControlBlock process[MAX_PROCESSES];

uint32_t status;
uint32_t stack_pointer;
uint32_t program_counter;
uint32_t saved_sp;

uint8_t current_process = 1;

uint16_t pc1;
uint16_t pc2;


void initialiseProcess(unsigned int process_index, void (*funct)()){
    if (process_index < MAX_PROCESSES)
    {
        asm(
                " movx.a SR,&status\n"
            );

        stack_pointer = (uint32_t)&process[process_index] + STACK_SIZE - 2;
        program_counter = (uint32_t)funct;

        // Construct combined PC+SR used by interrupt

        pc1 = (uint16_t)program_counter;
        pc2 = (uint16_t)(((program_counter>>4)&0x0F000) | status&0x00FFF);

        asm(
                " movx.a sp,&saved_sp\n"
                " movx.a &stack_pointer,sp\n"
                " push.w &pc1\n"
                " push.w &pc2\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " push.a #0\n"
                " movx.a sp,&stack_pointer\n"
                " movx.a &saved_sp,sp\n"
            );

        process[process_index].sp = stack_pointer;
    }
}

void runProcess(unsigned int process_index){
  if (process_index < MAX_PROCESSES)
  {
    stack_pointer = process[process_index].sp;

    asm(
            " movx.a &stack_pointer,SP \n"
            " pop.a R3 \n"
            " pop.a R4 \n"
            " pop.a R5 \n"
            " pop.a R6 \n"
            " pop.a R7 \n"
            " pop.a R8 \n"
            " pop.a R9 \n"
            " pop.a R10 \n"
            " pop.a R11 \n"
            " pop.a R12 \n"
            " pop.a R13 \n"
            " pop.a R14 \n"
            " pop.a R15 \n"
            " RETI \n"
    );
  }
}


void processSwitching(){
    asm(
            " push.a R10\n"
            " push.a R9\n"
            " push.a R8\n"
            " push.a R7\n"
            " push.a R6\n"
            " push.a R5\n"
            " push.a R4\n"
            " push.a R3\n"
            " movx.a sp,&stack_pointer\n"
        );

    process[current_process].sp = stack_pointer;

    current_process = (current_process+1) % MAX_PROCESSES;

    stack_pointer = process[current_process].sp;

    asm(
            " movx.a &stack_pointer,SP \n"
            " pop.a R3 \n"
            " pop.a R4 \n"
            " pop.a R5 \n"
            " pop.a R6 \n"
            " pop.a R7 \n"
            " pop.a R8 \n"
            " pop.a R9 \n"
            " pop.a R10 \n"   
    );

    LCDMEMCTL |= LCDCLRM | LCDCLRBM;  /* Clear LCD memory */
}
