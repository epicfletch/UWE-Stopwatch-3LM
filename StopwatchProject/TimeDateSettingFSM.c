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

struct timeSet setTime;

void timeDateSettingFSM()
{
    uint8_t TimeDateState = HOUR_SET;
    setTime.hours = 0;
    setTime.minutes = 0;
    setTime.day = 0;
    setTime.weekDay = 0;

    //LCDCTL0 |= LCD4MUX | LCDON;                                // Turn on LCD, 4-mux selected
    while(1)
    {
        switch (TimeDateState)
        {
            case HOUR_SET:
                if (startStopFlag)
                {
                    setTime.hours ++;
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
                        setTime.minutes ++;
                        if (setTime.minutes > 60)
                        {
                            setTime.minutes = 1;
                        }
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
                        setTime.weekDay ++;
                        if (weekday > 7)
                        {
                           setTime.weekDay = 1;
                        }
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
                        setTime.month ++;
                        if (setTime.month > 12)
                        {
                            setTime.month = 1;
                        }
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
                        setTime.day ++;
                        if (setTime.month == (1 || 3 || 5 || 7 || 8 || 10 || 12))
                        {
                            if (setTime.day > 31)
                            {
                                setTime.day = 1;
                            }
                        }
                        if (setTime.month == (4 || 6 || 9 || 11))
                        {
                            if (setTime.day > 30) 
                            {
                                setTime.day = 1;
                            }
                        }
                        if (setTime.month == (2))
                        {
                            if (setTime.day > 28)
                            {
                                setTime.day = 1;
                            }
                        }
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
        
        if(modeFlag == 1){
            modeFlag = 0;
        }
    }
}

void flash(uint8_t state)
{
    LCDMEM[4] = 0;
    __delay_cycles(80000);
    LCDMEM[4] = 1;

}

