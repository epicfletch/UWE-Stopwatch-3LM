/*H ----------------------------------------------------------------------------
  FILENAME :  time_slicing_V1.c

  DESCRIPTION :
              Code Example for Time Slicing Demonstration w/ Scheduler

              Copyright J. Mossbrucker 2020

 AUTHOR :     Joerg Mossbrucker


 INCLUDES :
              <msp430.h>        standard I/O defintions for the MSP430

 CHANGES :

*H ---------------------------------------------------------------------------*/


#include "msp430fr4133.h"
#include <msp430.h>

// defines to make it a little easier
// we only need unsigned integers
#define LONG unsigned long
#define WORD unsigned short
#define BYTE unsigned char

#define RED_LED BIT0
#define GREEN_LED BIT0

#define MAX_PROCESSES   3
#define STACK_SIZE      150

volatile int ms = 0;


/*F ----------------------------------------------------------------------------
  NAME :      red_led()

  DESCRIPTION :
              toggles the red LED

*F ---------------------------------------------------------------------------*/
void red_led()
{
    volatile unsigned int i;             // make sure i is not optimized way

    for (;;)
    {
        P1OUT |= RED_LED;                 // Set P1.0 on  (Red LED)
        //__delay_cycles(2000000);  // Delay for 100,000 clock cycles
        while (ms < 1000){}
        ms = 0;

        P1OUT &= ~RED_LED;                 // Set P1.0 off (Red LED)
        // __delay_cycles(2000000);  // Delay for 100,000 clock cycles
        while (ms < 1000){}
        ms = 0;
    }
}


/*F ----------------------------------------------------------------------------
  NAME :      green_led()

  DESCRIPTION :
              toggles the green LED

*F ---------------------------------------------------------------------------*/
void green_led()
{
    volatile unsigned int i;             // make sure i is not optimized away

    for (;;)
    {
      __bic_SR_register(GIE); /* Clear GIE bit, disabling interrupts */
        P4OUT |= GREEN_LED;               // Set P4.0 on  (Green LED)
        __delay_cycles(16000000); 

        P4OUT &= ~GREEN_LED;               // Set P4.0 off (Green LED)
        __delay_cycles(16000000); 
    }
}

/*F ----------------------------------------------------------------------------
  NAME :      both_led()

  DESCRIPTION :
              toggles both LEDs

*F ---------------------------------------------------------------------------*/
void both_led()
{
    volatile unsigned int i;             // make sure i is not optimized away

    for (;;)
    {
        P4OUT |= GREEN_LED;  
        P1OUT |= RED_LED;             
        __delay_cycles(2000000);  // Delay for 100,000 clock cycles

        P4OUT &= ~GREEN_LED;   
        P1OUT &= ~RED_LED;              
        __delay_cycles(2000000);  // Delay for 100,000 clock cycles
    }
}

/* -----------------------------------------------------------------------------
  static memory allocation for the process control blocks PCB
  each PCB consists of
    sp                  the stack pointer
    stack[STACK_SIZE]   the run time stack

  allocate memory for a fixed no. of PCBs
------------------------------------------------------------------------------*/


struct ProcessControlBlock
{
    LONG sp;
    BYTE stack[STACK_SIZE];
};

struct ProcessControlBlock process[MAX_PROCESSES];

/* -----------------------------------------------------------------------------
  first process to run is PCB[0]
------------------------------------------------------------------------------*/
unsigned int current_process = 0;

/* -----------------------------------------------------------------------------
  initialize_process needs temporary access to memory to store information
  these need to be declared global so we can use move instructions
    SREG, SP, PC, saved SP
    pc1,pc2  partial PC as saved on the stack
------------------------------------------------------------------------------*/
LONG status;
LONG stack_pointer;
LONG program_counter;
LONG saved_sp;

WORD pc1;
WORD pc2;


/*F ----------------------------------------------------------------------------
  NAME :      initialize_process()

  DESCRIPTION :
              populates the PCB

  INPUTS :    unsigned int process_index    the no (or index) of the PCB
              void (*funct)()               pointer to process

  RETURNS :   void

  PROCESS :
              [1]   store SREG into status
              [2]   calculate the stack_pointer for PCB to point at end of stack
              [3]   get the starting address of the process
              [4]   combine PC+SR used by the ISR into pc2 and pc1
              [5]   saved_sp <= sp
              [6]   sp <= stack_pointer
              [7]   push pc1
              [8]   push pc2
              [9]   push a 0 13 times
              [10]  stack_pointer <= sp
              [11]  sp <= saved_sp
              [12]  save stack_pointer into the PCB stack pointer

*F ---------------------------------------------------------------------------*/
void initialise_process(unsigned int process_index, void (*funct)())
{
    if (process_index < MAX_PROCESSES)
    {
        asm(
                " movx.a SR,&status\n"
            );

        stack_pointer = (LONG)&process[process_index] + STACK_SIZE - 2;
        program_counter = (LONG)funct;

        // Construct combined PC+SR used by interrupt

        pc1 = (WORD)program_counter;
        pc2 = (WORD)(((program_counter>>4)&0x0F000) | status&0x00FFF);

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

/*F ----------------------------------------------------------------------------
  NAME :      run_process()

  DESCRIPTION :
              runs the process

  INPUTS :    unsigned int process_index    the no (or index) of the PCB

  RETURNS :   void

  PROCESS :
              [1]   if valid process
              [2]     stack_pointer <= stack pointer of the PCB
              [3]     sp <= stack_pointer
              [4]     pop R3 - R15
              [5]     RETI

*F ---------------------------------------------------------------------------*/
void run_process(unsigned int process_index)
{
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

/*F ----------------------------------------------------------------------------
  NAME :      main()

  DESCRIPTION :
              main program

  INPUTS :    none

  RETURNS :   void

  PROCESS :
              [1]   set up pins
              [2]   set up timer interrupt
              [3]   initialize both processes
              [4]   start first process
              [5]   enable interrupts
              [6]   do forever
              [7]     red_led()
              [8]     green_led()

*F ---------------------------------------------------------------------------*/
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    /* sets clock speed to 16MHz*/
    __bis_SR_register(SCG0);        /* Disable FLL */
    CSCTL3 = SELREF__REFOCLK;       /* Set REFO as FLL reference source */

    CSCTL0 = 0x00;                  /* Clear DCO and MOD bits */
    CSCTL1 |= DCORSEL_5;            /* Set DCO = 16MHz */
    CSCTL2 = FLLD_0 + 487;          /* DCOCLKDIV = 16MHz */
    __delay_cycles(3);
    __bic_SR_register(SCG0);        /* Enable FLL */
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // FLL locked */

    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
                                    // to activate previously configured port settings

    P1DIR |=  0x01;                 // Set P1.0 to output direction
    P4DIR |=  0x01;                 // Set P4.0 to output direction
    P1OUT &= ~0x01;                 // Set P1.0 off (Red LED)
    P4OUT &= ~0x01;                 // Set P4.0 off (Green LED)

    //P4OUT |=  0x40;               // Set P4.6 on  (Red LED)


    // Configure Button (P1.2) as Input with Pull-up Resistor
    P1DIR &= ~BIT2;             // Set P1.2 as input
    P1REN |= BIT2;              // Enable pull-up/down resistor
    P1OUT |= BIT2;              // Select pull-up resistor

    // Configure Interrupts for P1.2
    P1IE  |= BIT2;              // Enable interrupt on P1.2
    P1IES |= BIT2;              // Trigger on falling edge (button press)
    P1IFG &= ~BIT2;             // Clear any pending interrupt flag

    /* initialise timer as interrupt (10ms) */
                                    // Timer A0 (1ms interrupt)
    TA0CCR0 =  20000;     /* set compare value 20000 (10ms @ 2MHz) */
    TA0CCTL0 = 0x10;      /* Enable counter interrupts, bit 4=1 */
    TA0CTL |=   TASSEL_2; /* use SMCLK as source */
    TA0CTL |=   MC_1;     /* count up to CCR0 */
    TA0CTL |=   ID_3; /* /8 predivider (16MHz -> 2MHz clock) */

    // Initialisation - Software

    _BIS_SR(GIE);                   // interrupts enabled (we need to do it here so it gets saved to stack)

    initialise_process(0, red_led);
    initialise_process(1, green_led);
    initialise_process(2, both_led);


    run_process(current_process);


    // Background loop

    _BIS_SR(GIE);                   // interrupts enabled

    for (;;)
    {

    }
}


/*F ----------------------------------------------------------------------------
  NAME :      Timer0_A0()

  DESCRIPTION :
              ISR for the timer0_A0 for interrupt

  INPUTS :    none

  RETURNS :   void

  PROCESS :
              [1]   save contexxt on PCB stack
              [2]   stack_pointer <= sp
              [3]   save stack_pointer in PCB sp
              [4]   get next PCB
              [5]   get PCB sp into stack_pointer
              [6]   sp <= stack_pointer
              [7]   get context from stack

*F ---------------------------------------------------------------------------*/
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
  __bic_SR_register(GIE); // Clear GIE bit, disabling interrupts
  __delay_cycles(2000000);  // Delay for 100,000 clock cycles

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
    __bis_SR_register(GIE); // Set General Interrupt Enable (GIE) bit
    P1IFG &= ~BIT2;         // Clear interrupt flag
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)    // Timer0 A0 1ms interrupt service routine
{
  __bic_SR_register(GIE); /* Clear GIE bit, disabling interrupts */
  ms += 10; /* add 10ms to the ms count */
  __bis_SR_register(GIE); /* Set General Interrupt Enable (GIE) bit */
}