
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

uint8_t current_process = 0;

uint16_t pc1;
uint16_t pc2;

volatile uint8_t g_buffer = 0;         //5 byte-wide buffer to act as mailbox
                                    //volatile so it is not optimised out


void InitialiseProcess(unsigned int process_index, void (*funct)()){
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

void RunProcess(unsigned int process_index){
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


void ProcessSwitching(){
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
}


/*F ----------------------------------------------------------------------------
  NAME        : send()
  DESCRIPTION : waits until mailbox is empty and updates with new message

  INPUTS      : char *g_buffer, char message

  RETURNS     : void
*F ---------------------------------------------------------------------------*/


void send(uint8_t *g_buffer, uint8_t message)  //passes message to update the mailbox
{
   volatile unsigned int i;              //volatile so it is not optimised out

   while(*g_buffer)                      //wait for mailbox to be empty as this indicates previous message has been taken
    {
        i = i + 1;                       //dummy operation so while loop is not optimised out
    }

   *g_buffer = message;                  //send the new message as the mailbox is empty
}


/*F ----------------------------------------------------------------------------
  NAME        : receive()
  DESCRIPTION : waits for a new message and passes to process
                clears mailbox when new message has been read

  INPUTS      : char *g_buffer

  RETURNS     : char message
*F ---------------------------------------------------------------------------*/


uint8_t receive(uint8_t *g_buffer)  //must read and write from/to mailbox
{
    uint8_t message;

    if (*g_buffer != EMPTY)   //if the mailbox contains new message
    {
        message = *g_buffer;  //store the new message in a temp variable

        *g_buffer = EMPTY;    //empty the mailbox to indicate that the message has been received
    }

    return message;           //update process with new message
}

