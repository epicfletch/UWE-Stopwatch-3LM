/*F ----------------------------------------------------------------------------
  NAME :      TimeDateSettingFSM.c

  DESCRIPTION :
              Controls what state the Time/Date/Alarm setting mode is in 



  FUNCTIONS :
              [1] Finite state machine for the time date setting
                INPUTS :    none
                RETURNS :   void
                  a) allows selection of digits to set hour/min/day/month/date
                  b) increments setTime structure elements and assigns to clockTime
                  c) flashes selected digits
*F ---------------------------------------------------------------------------*/


#include "TimeDateSettingFSM.h"
#include "LCD.h"
#include "TimerInterrupt.h"
#include "ProcessSwitching.h"

void TimeDateSettingFSM()
{
    uint8_t messageArray[5] = {0,0,0,0,0};
    uint8_t TimeDateState = HOUR_SET;
    while(1)
    {
        /* state machine for time /date setting*/
        switch (TimeDateState)
        {
            case HOUR_SET:
                if (startStopFlag)
                {
                    /* increments hour value*/
                    setTime.hours ++;
                    if (setTime.hours == 24)
                    {
                        setTime.hours = 0;
                    }
                    startStopFlag = 0;
                }
                else if(lapResetFlag)
                {
                    /*sets the message array at index 0 to the set hours send message to the set the hour time and move state*/
                    messageArray[0] = setTime.hours;
                    send(&g_buffer, messageArray[0]);
                    TimeDateState = MIN_SET;
                    lapResetFlag = 0;
                }
                else
                {
                    /*flashes the hour digits and resets LCD minutes to display minutes if moving back from date setting*/
                    LCDMEM[8] = digit[setTime.minutes/10][0];
                    LCDMEM[9] = digit[setTime.minutes/10][1];
                    LCDMEM[10] = digit[setTime.minutes%10][0];
                    LCDMEM[11] = digit[setTime.minutes%10][1];
                    LCDMEM[4] = 0;
                    LCDMEM[5] = 0;
                    LCDMEM[6] = 0;
                    LCDMEM[7] = 0;
                    __delay_cycles(4000000);
                    LCDMEM[4] = digit[setTime.hours/10][0];
                    LCDMEM[5] = digit[setTime.hours/10][1];
                    LCDMEM[6] = digit[setTime.hours%10][0];
                    LCDMEM[7] = digit[setTime.hours%10][1];
                    LCDMEM[7] |= symbols[0][0];
                    LCDMEM[12] = 0;
                    __delay_cycles(4000000);
                }
                break;
            case MIN_SET:
                if (startStopFlag)
                    {
                        setTime.minutes ++;
                        if (setTime.minutes == 60)
                        {
                            setTime.minutes = 1;
                        }
                        startStopFlag = 0;
                    }
                    else if(lapResetFlag)
                    {
                        clockTime.minutes = setTime.minutes;
                        TimeDateState = WEEKDAY_SET;
                        lapResetFlag = 0;
                    }
                    else
                    {
                        LCDMEM[8] = 0;
                        LCDMEM[9] = 0;
                        LCDMEM[10] = 0;
                        LCDMEM[11] = 0;
                        __delay_cycles(4000000);
                        LCDMEM[8] = digit[setTime.minutes/10][0];
                        LCDMEM[9] = digit[setTime.minutes/10][1];
                        LCDMEM[10] = digit[setTime.minutes%10][0];
                        LCDMEM[11] = digit[setTime.minutes%10][1];
                        __delay_cycles(4000000);
                    }
                    break;
            case WEEKDAY_SET:
                if (startStopFlag)
                    {
                        setTime.weekDay ++;
                        if (setTime.weekDay == 7)
                        {
                           setTime.weekDay = 0;
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
                        LCDMEM[2] = 0;
                        LCDMEM[3] = 0;
                        LCDMEM[18] = 0;
                        LCDMEM[19] = 0;
                        __delay_cycles(4000000);
                        LCDMEM[2] = dayOfWeek[setTime.weekDay][0];
                        LCDMEM[3] = dayOfWeek[setTime.weekDay][1];
                        LCDMEM[18] = dayOfWeek[setTime.weekDay][2];
                        LCDMEM[19] = dayOfWeek[setTime.weekDay][3];
                        __delay_cycles(4000000);
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
                        LCDMEM[4] = digit[setTime.day/10][0];
                        LCDMEM[5] = digit[setTime.day/10][1];
                        LCDMEM[6] = digit[setTime.day%10][0];
                        LCDMEM[7] = digit[setTime.day%10][1];
                        LCDMEM[8] = 0;
                        LCDMEM[9] = 0;
                        LCDMEM[10] = 0;
                        LCDMEM[11] = 0;
                        __delay_cycles(4000000);
                        LCDMEM[8] = digit[setTime.month/10][0];
                        LCDMEM[9] = digit[setTime.month/10][1];
                        LCDMEM[10] = digit[setTime.month%10][0];
                        LCDMEM[11] = digit[setTime.month%10][1];
                        LCDMEM[11] |= symbols[3][0];
                        __delay_cycles(4000000);
                    }
                    break;
            case DAY_SET:
                if (startStopFlag)
                    {
                        setTime.day ++;
                        if ((setTime.month == 1) || (setTime.month == 3) || (setTime.month == 5) || (setTime.month == 7) || (setTime.month == 8) || (setTime.month == 10) || (setTime.month == 12))
                        {
                            if (setTime.day > 31)
                            {
                                setTime.day = 1;
                            }
                        }
                        if ((setTime.month == 4) || (setTime.month == 6) || (setTime.month == 9) || (setTime.month == 11))
                        {
                            if (setTime.day > 30) 
                            {
                                setTime.day = 1;
                            }
                        }
                        if (setTime.month == 2)
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
                        LCDMEM[4] = 0;
                        LCDMEM[5] = 0;
                        LCDMEM[6] = 0;
                        LCDMEM[7] = 0;
                        __delay_cycles(4000000);
                        LCDMEM[4] = digit[setTime.day/10][0];
                        LCDMEM[5] = digit[setTime.day/10][1];
                        LCDMEM[6] = digit[setTime.day%10][0];
                        LCDMEM[7] = digit[setTime.day%10][1];
                        LCDMEM[7] |= symbols[3][0];
                        __delay_cycles(4000000);

                    }
                    break;
            default:
            /* default state is hour set*/
            TimeDateState = HOUR_SET;
            break;
        }
        
    }
}


