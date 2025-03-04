/*H**********************************************************************
	FILENAME : 	Lab1.c

	DESCRIPTION :
				Introduction to the MSP430FR4133 Launchpad
				Blink the Red LED forever

	AUTHOR :		Joerg Mossbrucker          START DATE :    01 Sep 20


  Hardware Setup :
  
        P1 Bit 0 -> Red LED (built-in))

*H*/
#define RED_LED 0


#include <msp430.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high
                                    //impedance mode
                                    // to activate previously configured port settings

    P1SEL0 &= ~(1<<RED_LED);        // Set P1.0 to GPIO
    P1DIR |= (1<<RED_LED);          // Set P1.0 to output direction

    for(;;)
    {
        volatile unsigned int i;    // volatile to prevent optimization

        P1OUT ^= (1<<RED_LED);      // Toggle P1.0 using exclusive-OR

        i = 10000;                  // SW Delay

        do i--;
        while(i != 0);
    }
}

