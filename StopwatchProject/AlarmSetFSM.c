#include "AlarmSetFSM.h"
void alarmSetFSM()
{
    uint8_t alarmState = 0;   // variable for the alarm state
    while(1){
        switch (alarmState)
        {
            case HOUR_SET:
                if (startStopFlag)
                {
                    setAlarm.hours ++;
                    if (setAlarm.hours == 24)
                    {
                        setAlarm.hours = 0;
                    }
                    startStopFlag = 0;
                }
                else if(lapResetFlag)
                {
                    alarmTime.hours = setAlarm.hours;
                    alarmState = MIN_SET;
                    lapResetFlag = 0;
                }
                else
                {
                    LCDMEM[8] = digit[setAlarm.minutes/10][0];
                    LCDMEM[9] = digit[setAlarm.minutes/10][1];
                    LCDMEM[10] = digit[setAlarm.minutes%10][0];
                    LCDMEM[11] = digit[setAlarm.minutes%10][1];
                    LCDMEM[4] = 0;
                    LCDMEM[5] = 0;
                    LCDMEM[6] = 0;
                    LCDMEM[7] = 0;
                    LCDMEM[12] = 0;
                    __delay_cycles(4000000);
                    LCDMEM[4] = digit[setAlarm.hours/10][0];
                    LCDMEM[5] = digit[setAlarm.hours/10][1];
                    LCDMEM[6] = digit[setAlarm.hours%10][0];
                    LCDMEM[7] = digit[setAlarm.hours%10][1];
                    LCDMEM[7] |= symbols[0][0];
                    LCDMEM[12] = symbols[1][0];
                    __delay_cycles(4000000);
                }
                break;
            case MIN_SET:
                if (startStopFlag)
                    {
                        setAlarm.minutes ++;
                        if (setAlarm.minutes == 60)
                        {
                            setAlarm.minutes = 1;
                        }
                        startStopFlag = 0;
                    }
                    else if(lapResetFlag)
                    {
                        alarmTime.minutes = setAlarm.minutes;
                        alarmState = HOUR_SET;
                        lapResetFlag = 0;
                    }
                    else
                    {
                        LCDMEM[8] = 0;
                        LCDMEM[9] = 0;
                        LCDMEM[10] = 0;
                        LCDMEM[11] = 0;
                        __delay_cycles(4000000);
                        LCDMEM[8] = digit[setAlarm.minutes/10][0];
                        LCDMEM[9] = digit[setAlarm.minutes/10][1];
                        LCDMEM[10] = digit[setAlarm.minutes%10][0];
                        LCDMEM[11] = digit[setAlarm.minutes%10][1];
                        LCDMEM[12] = symbols[1][0];
                        __delay_cycles(4000000);
                    }
                    break;
            default:
            alarmState = HOUR_SET;
            break;
        }
    }   
}
