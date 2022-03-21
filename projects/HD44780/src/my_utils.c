#include <stdint.h>
#include "definitions.h"
#include "my_utils.h"


// Func Desc:
// Provides a millisecond delay
// uses timer0 with 1 millisecond period tick
// Param1 uint16_t ms : time in mS to delay for.

void customDelayMS(uint16_t ms) {
    uint16_t tickMs;
    for (tickMs = 0; tickMs < ms; tickMs++) {
        TC0_TimerStart();
        while (!TC0_TimerPeriodHasExpired());
        TC0_TimerStop();
    }
}


