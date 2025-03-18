/*F ----------------------------------------------------------------------------
  NAME :      ClockNormal.c

  DESCRIPTION :
              Functions to control the behaviour of the clock in its normal state



  FUNCTIONS :
              [1] 
                INPUTS :    none
                RETURNS :   void
                  a) 
*F ---------------------------------------------------------------------------*/

#include "ClockNormal.h"
#include "intrinsics.h"

void updateDisplay(){
    LCDMEM[4] = digit[hours / 10][0];
    LCDMEM[5] = digit[hours / 10][1];
    LCDMEM[6] = digit[hours % 10][0];
    LCDMEM[7] = digit[hours % 10][1];

    LCDMEM[7] |= symbols[0][0];

    LCDMEM[8] = digit[minutes / 10][0];
    LCDMEM[9] = digit[minutes / 10][1];
    LCDMEM[10] = digit[minutes % 10][0];
    LCDMEM[11] = digit[minutes % 10][1];

    LCDMEM[11] |= symbols[0][0];

    LCDMEM[2] = digit[seconds / 10][0];
    LCDMEM[3] = digit[seconds / 10][1];
    LCDMEM[18] = digit[seconds % 10][0];
    LCDMEM[19] = digit[seconds % 10][1];
    __delay_cycles(8000000);
}

void clearLCD(){
  LCDMEMCTL |= LCDCLRM | LCDCLRBM;  /* Clear LCD memory */
} 