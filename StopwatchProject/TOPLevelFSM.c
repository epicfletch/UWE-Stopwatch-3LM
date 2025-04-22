
#include "TopLevelFSM.h"
void TopLevelFSM()
{
    uint8_t modeState = CLOCK;   // variable for the top level state
    while (1)
    {
        switch (modeState)
        {
            case CLOCK:  
                if(modeFlag == 1){
                    modeState = TIME_CALENDER;
                    modeFlag = 0;
                    processSwitching();                    
                }
                break;
            case TIME_CALENDER:
                runProcess(current_process); 
                if(modeFlag == 1){
                    modeState = ALARM_SET;
                    modeFlag = 0;
                    processSwitching();                    
                }
                break;
            case ALARM_SET:
                runProcess(current_process);
                if(modeFlag == 1){
                    modeState = STOPWATCH;
                    modeFlag = 0;
                    processSwitching();                      
                }
                break;
            case STOPWATCH:
                runProcess(current_process); 
                if(modeFlag == 1){
                    modeState = CLOCK;
                    modeFlag = 0;
                    processSwitching();  
                }
                break;
            default:
                break;
        }
    }
        
}