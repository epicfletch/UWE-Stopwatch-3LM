/*F ----------------------------------------------------------------------------
  NAME :      TimeDateSettingFSM.c

  DESCRIPTION :
              Controls what state the Time/Date/Alarm setting mode is in 



  FUNCTIONS :
              [1] Finite state machine for the clock mode
                INPUTS :    none
                RETURNS :   void
                  a) displays the time as 24hr clock and day of the week 
                  b) displays the date
                  c) displays what time the alarm is set to
                  d) toggles on and off the alarm
*F ---------------------------------------------------------------------------*/


#include "TimeDateSettingFSM.h"

//uint8_t TimeDateState = HOUR_SET;

void timeDateSettingFSM()
{
    //LCDCTL0 |= LCD4MUX | LCDON;                                // Turn on LCD, 4-mux selected
    while(1)
    {
        switch (TimeDateState)
        {
            case HOUR_SET:
                if (startStopFlag)
                {
                    incrementVal(HOUR_SET);
                    startStopFlag = 0;
                }
                else if(lapResetFlag)
                {
                    TimeDateState = MIN_SET;
                    lapResetFlag = 0;
                }
                else
                {
                    flash(HOUR_SET);
                }
                break;
            case MIN_SET:
                if (startStopFlag)
                    {
                        incrementVal(MIN_SET);
                        startStopFlag = 0;
                    }
                    else if(lapResetFlag)
                    {
                        TimeDateState = WEEKDAY_SET;
                        lapResetFlag = 0;
                    }
                    else
                    {
                        flash(MIN_SET);
                    }
                    break;
            case WEEKDAY_SET:
                if (startStopFlag)
                    {
                        incrementVal(HOUR_SET);
                        startStopFlag = 0;
                    }
                    else if(lapResetFlag)
                    {
                        TimeDateState = MONTH_SET;
                        lapResetFlag = 0;
                    }
                    else
                    {
                        flash(WEEKDAY_SET);
                    }
                    break;
            case MONTH_SET:
                if (startStopFlag)
                    {
                        incrementVal(MONTH_SET);
                        startStopFlag = 0;
                    }
                    else if(lapResetFlag)
                    {
                        TimeDateState = DAY_SET;
                        lapResetFlag = 0;
                    }
                    else
                    {
                        flash(MONTH_SET);
                    }
                    break;
            case DAY_SET:
                if (startStopFlag)
                    {
                        incrementVal(DAY_SET);
                        startStopFlag = 0;
                    }
                    else if(lapResetFlag)
                    {
                        TimeDateState = HOUR_SET;
                        lapResetFlag = 0;
                    }
                    else
                    {
                        flash(DAY_SET);
                    }
                    break;
            default:
            TimeDateState = HOUR_SET;
            break;
        }
    }
}

void flash(uint8_t state)
{
    LCDMEM[4] = 0;
   // __delay_cycles(80000);
   // LCDMEM[4] = 1;

}

void incrementVal(uint8_t state)
{
    LCDMEM[4] = 0;
}