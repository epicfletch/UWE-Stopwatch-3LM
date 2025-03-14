/*H ----------------------------------------------------------------------------
  FILENAME :  Define.h

  DESCRIPTION :
              Header file to contain all project defines 

 AUTHOR :     Josh Fletcher


 INCLUDES :   <cstdlib>  c++ standard library
              "msp430fr4133.h"
              <msp430.h>

              

 CHANGES :

*H ---------------------------------------------------------------------------*/

#ifndef Defines_H
#define Defines_H

#include <stdint.h>
#include "msp430fr4133.h"
#include <msp430.h>

#define RED_LED BIT0    /* P1.0 */
#define GREEN_LED BIT0  /* P4.0 */

#define START_STOP BIT2 /* P1.2 */
#define LAP_RESET BIT6  /* P2.6 */
#define MODE 0          /* mode button port to be decided on */

#define MAX_PROCESSES   1
#define STACK_SIZE      100

/* clock states */
#define CLOCK_NORMAL 0
#define CLOCK_DATE 1
#define CLOCK_ALARM_TIME 2
#define CLOCK_ALARM_TOGGLE 3

#endif