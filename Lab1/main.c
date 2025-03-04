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
#define GREEN_LED 0
#define BUTTON1_PIN 2
#define BUTTON2_PIN 6

#include <msp430.h>

void main(void){
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high impedance mode

    // Set up P4.0 (GREEN_LED) as GPIO output
    P4SEL0 &= ~(1 << GREEN_LED);      // Set P4.0 to GPIO
    P4DIR |= (1 << GREEN_LED);        // Set P4.0 as output

    // Set up P1.0 (RED_LED) as GPIO output
    P1SEL0 &= ~(1 << RED_LED);      // Set P1.0 to GPIO
    P1DIR |= (1 << RED_LED);        // Set P1.0 as output

    // Set up P1.2 (Button) as GPIO input
    P1DIR &= ~(1 << BUTTON1_PIN);    // Set P1.2 as input
    P1REN |= (1 << BUTTON1_PIN);     // Enable pull-up/down resistor
    P1OUT |= (1 << BUTTON1_PIN);     // Set pull-up resistor (P1.2 will read as high when button is not pressed)

    // Set up P1.2 (Button) as GPIO input
    P2DIR &= ~(1 << BUTTON2_PIN);    // Set 2.6 as input
    P2REN |= (1 << BUTTON2_PIN);     // Enable pull-up/down resistor
    P2OUT |= (1 << BUTTON2_PIN);     // Set pull-up resistor (P1.2 will read as high when button is not pressed)

    // Variable to track LED state
    unsigned int ledState = 0;     // 0 = LED off, 1 = LED on

    for(;;)
    {
        // Check if the button is pressed (P1.2 is low when pressed)
        if (!(P1IN & (1 << BUTTON1_PIN)))  // If button is pressed (P1.2 = 0)
        {
            // Toggle the LED state
            ledState ^= 1;  // Toggle between 0 and 1

            // Update the LED output based on the ledState
            if (ledState)
            {
                P1OUT |= (1 << RED_LED);  // Turn on LED (P4.0)
            }
            else
            {
                P1OUT &= ~(1 << RED_LED); // Turn off LED (P4.0)
            }

            // Simple delay to debounce the button (can be optimized further)
            volatile unsigned int i = 20000;  // Debounce delay
            while (i != 0) {
                i--;
            }
        }
        else if (!(P2IN & (1 << BUTTON2_PIN)))  // If button is pressed (P1.2 = 0)
        {
            // Toggle the LED state
            ledState ^= 1;  // Toggle between 0 and 1

            // Update the LED output based on the ledState
            if (ledState)
            {
                P4OUT |= (1 << GREEN_LED);  // Turn on LED (P4.0)
            }
            else
            {
                P4OUT &= ~(1 << GREEN_LED); // Turn off LED (P4.0)
            }

            // Simple delay to debounce the button (can be optimized further)
            volatile unsigned int i = 20000;  // Debounce delay
            while (i != 0) {
                i--;
            }
        }
    }
}
