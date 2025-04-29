/*H ----------------------------------------------------------------------------
  FILENAME :  Chime.h

  DESCRIPTION :
              Header file for clock chime 

 AUTHOR :     Josh Fletcher


 INCLUDES :

 CHANGES :

*H ---------------------------------------------------------------------------*/
#ifndef Chime_H
#define Chime_H

#include "Defines.h"
#include "LCD.h"
#include "TimerInterrupt.h"
#include "ButtonInterrupts.h"

extern int chimeState;

void ChimeToggle();
void Chime();

#endif