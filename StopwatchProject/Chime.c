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

void chimeToggle(){
    if(chimeState == 0){
        chimeState = 1;
        LCDMEM[9] |= symbols[2][0];
    }
    else{
        chimeState = 0;
        LCDMEM[9] &= ~symbols[2][0];;
    }
}
void chime(){
    /* toggle LED */
}