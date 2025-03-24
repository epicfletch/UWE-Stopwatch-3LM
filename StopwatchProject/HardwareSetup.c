/*F ----------------------------------------------------------------------------
  NAME :      HardwareSetup.c

  DESCRIPTION :
              Functions file for microcontroller hardware setup



  FUNCTIONS :
              [1]   Disable watchdog function
                INPUTS :    none
                RETURNS :   void
                  a) disable watchdog
              [2]   Setup clock with 16MHz frequency
                INPUTS :    none
                RETURNS :   void
                a) disable watchdog
                b) disable watchdog
              [3]   Setup LED and Button GPIO pins
                INPUTS :    none
                RETURNS :   void
              [4]   Setup interrupt on button press
                INPUTS :    none
                RETURNS :   void
              [5]   Setup timer interrupt with 10ms frequency
                INPUTS :    none
                RETURNS :   void
              [6]   Setup LCD display
                INPUTS :    none
                RETURNS :   void

*F ---------------------------------------------------------------------------*/

#include "HardwareSetup.h"
#include "msp430fr4133.h"

void DisableWatchdog(){
  WDTCTL = WDTPW | WDTHOLD; /* Disable watchdog timer */
}

void SetupClock(){
  /* sets clock speed to 16MHz*/
  __bis_SR_register(SCG0);                   /* Disable FLL */
  
  CSCTL0 = 0x00;                             /* Clear DCO and MOD bits */
  CSCTL1 |= DCORSEL_5;                       /* Set DCO = 16MHz */
  CSCTL2 = FLLD_0 + 487;                     /* DCOCLKDIV = 16MHz */
  CSCTL3 = SELREF__REFOCLK;                  /* Set REFO as FLL reference source */

  __delay_cycles(3);
  __bic_SR_register(SCG0);                   /* Enable FLL */
  while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); /* FLL locked */
}

void SetupGPIO(){
  PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
                                    // to activate previously configured port settings
  /* setup LEDs */
  P1DIR |=  RED_LED;                 /* Set P1.0 to output direction */
  P4DIR |=  GREEN_LED;               /* Set P4.0 to output direction */
  P1OUT &= ~RED_LED;                 /* Set P1.0 off (Red LED) */
  P4OUT &= ~GREEN_LED;               /* Set P4.0 off (Green LED) */

  /* setup input buttons */
  P1DIR &= ~START_STOP;            /* Set P1.2 as input */
  P1REN |= START_STOP;             /* Enable pull-up/down resistor */
  P1OUT |= START_STOP;             /* Select pull-up resistor */

  P1DIR &= ~MODE;                  /* Set P1.3 as input */
  P1REN |= MODE;                   /* Enable pull-up/down resistor */
  P1OUT |= MODE;                  /* Select pull-UP resistor */
    
  P2DIR &= ~LAP_RESET;             /* Set P2.6 as input */
  P2REN |= LAP_RESET;              /* Enable pull-up/down resistor */
  P2OUT |= LAP_RESET;              /* Select pull-up resistor */


}

void SetupButtonInterrupts(){
  P1IE  |= START_STOP;              /* Enable interrupt on P1.2 */
  P1IES |= START_STOP;              /* Trigger on falling edge (button press) */
  P1IFG &= ~START_STOP;             /* Clear any pending interrupt flag */

  P1IE  |= MODE;                    /* Enable interrupt on P1.3 */
  P1IES |= MODE;                    /* Trigger on falling edge (button press) */
  P1IFG &= ~MODE;                   /* Clear any pending interrupt flag */

  P2IE  |= LAP_RESET;               /* Enable interrupt on P1.2 */
  P2IES |= LAP_RESET;               /* Trigger on falling edge (button press) */
  P2IFG &= ~LAP_RESET;              /* Clear any pending interrupt flag */
}

void SetupTimerInterrupt(){
  TA0CCR0 =  20000;     /* set compare value 20000 (10ms @ 2MHz) */
  TA0CCTL0 = 0x10;      /* Enable counter interrupts, bit 4=1 */
  TA0CTL |=  TASSEL_2;  /* use SMCLK as source */
  TA0CTL |=  MC_1;      /* count up to CCR0 */
  TA0CTL |=  ID_3;      /* /8 predivider (16MHz -> 2MHz clock) */
}


void SetupLCD(){
      // Configure LCD pins
    SYSCFG2 |= LCDPCTL;                                        // R13/R23/R33/LCDCAP0/LCDCAP1 pins selected

    LCDPCTL0 = 0xFFFF;
    LCDPCTL1 = 0x07FF;
    LCDPCTL2 = 0x00F0;                                         // L0~L26 & L36~L39 pins selected

    LCDCTL0 = LCDSSEL_2 | LCDDIV_0;                            // flcd ref freq is VLOCLK divide 1

    //LCD Operation - Mode 2
    LCDVCTL = LCDCPEN |                                        //Enable charge pump
            LCDSELVDD |                                        //Internally connect to Vcc
            VLCD_8 |                                           //internal 3.08v
           (LCDCPFSEL0 | LCDCPFSEL1 | LCDCPFSEL2 | LCDCPFSEL3);//Charge pump frequency selection 256Hz

    LCDMEMCTL |= LCDCLRM | LCDCLRBM;                           // Clear LCD memory

    LCDCSSEL0 = 0x000F;                                        // Configure COMs and SEGs
    LCDCSSEL1 = 0x0000;                                        // L0, L1, L2, L3: COM pins
    LCDCSSEL2 = 0x0000;

    LCDM0 = 0x21;                                              // L0 = COM0, L1 = COM1
    LCDM1 = 0x84;                                              // L2 = COM2, L3 = COM3

    LCDBLKCTL = 0;

    LCDCTL0 |= LCD4MUX | LCDON;                                // Turn on LCD, 4-mux selected
}

