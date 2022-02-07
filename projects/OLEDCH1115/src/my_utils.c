#include <stdint.h>
#include "definitions.h"  
#include "my_utils.h"


// Provides a millisecond delay 
// uses timer0 with 1 millisecond period tick
void delay_ms(uint16_t ms)
{
    uint16_t tickMs;
    for (tickMs=0; tickMs<ms; tickMs++)
    {
       TC0_TimerStart(); 
       while(!TC0_TimerPeriodHasExpired());
       TC0_TimerStop(); 
    }
}


