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
#define MODE BIT3      /* P1.3 */
#define LAP_RESET BIT6  /* P2.6 */


#define MAX_PROCESSES   2
#define STACK_SIZE      100

/* clock states */
#define CLOCK_NORMAL 0
#define CLOCK_DATE 1
#define CLOCK_ALARM_TIME 2
#define CLOCK_ALARM_TOGGLE 3
#define CLOCK_ALARM 4
#define CLOCK_CHIME_TOGGLE 5


/* Time Date Set States */
#define HOUR_SET 0
#define MIN_SET 1
#define WEEKDAY_SET 2
#define MONTH_SET 3
#define DAY_SET 4
#define INCREMENT 5


/* Top Level States */
#define CLOCK 0
#define TIME_CALENDER 1
#define ALARM_SET 2
#define STOPWATCH 3

#endif
