// /*F ----------------------------------------------------------------------------
//   NAME :      Chime.c

//   DESCRIPTION :
//               Functions to control the behaviour of the chime

//   FUNCTIONS :
//               [1] 
//                 INPUTS :    none
//                 RETURNS :   void
//                   a) 
// *F ---------------------------------------------------------------------------*/

#include "Chime.h"

int chimeState = 0;

void ChimeToggle(){
    if(chimeState == 0){
        chimeState = 1;
        LCDMEM[9] |= symbols[2][0];
    }
    else{
        chimeState = 0;
        LCDMEM[9] &= ~symbols[2][0];;
    }
}
void Chime(){
    int k = 0;
    for(k = 0; k < 5; k++){
        P4OUT |= GREEN_LED;               // Set P4.0 on  (Green LED)
        __delay_cycles(8000000); 
        P4OUT &= ~GREEN_LED;               // Set P4.0 off (Green LED)
        __delay_cycles(8000000); 
    }
}