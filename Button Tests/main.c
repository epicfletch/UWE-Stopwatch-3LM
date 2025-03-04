#include <msp430.h>

#define LED_PIN     BIT0    // P1.0 - LED
#define BUTTON_PIN  BIT2    // P1.2 - Button


// Port 1 ISR
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    __disable_interrupt();       // Enable global interrupts
    P1OUT ^= LED_PIN;           // Toggle LED state
    //P1IFG &= ~BUTTON_PIN;       // Clear interrupt flag
    __enable_interrupt();       // Enable global interrupts
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    // Configure LED pin as output
    P1DIR |= LED_PIN;           // Set P1.0 as output
    P1OUT &= ~LED_PIN;          // Ensure LED is off initially

    // Configure Button pin as input with pull-up resistor
    P1DIR &= ~BUTTON_PIN;       // Set P1.2 as input
    P1REN |= BUTTON_PIN;        // Enable pull-up/down resistor
    P1OUT |= BUTTON_PIN;        // Select pull-up resistor

    // Enable interrupt on button press
    P1IE  |= BUTTON_PIN;        // Enable interrupt for P1.2
    P1IES |= BUTTON_PIN;        // Interrupt on high-to-low transition
    P1IFG &= ~BUTTON_PIN;       // Clear interrupt flag

    __enable_interrupt();       // Enable global interrupts
    volatile int i;
    while (1)
    {
       i++;
    }
}

