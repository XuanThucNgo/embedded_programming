#include <stdint.h>
#include <intrinsics.h>
#include "TM4C123GH6PM.h"
#include "bsp.h"



int main() {

    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    SYSCTL->RCGC2 |= (1U << 5);  /* enable clock for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
    
    SysTick ->LOAD = SYS_CLOCK_HZ/2U - 1U;
    SysTick ->VAL  = 0U;
    SysTick ->CTRL = (1U << 2) | (1U << 1) | (1U);
    
    SysTick_Handler();
    
    __enable_interrupt();
    while (1) {
          __disable_interrupt();
          GPIOF_AHB->DATA |= LED_GREEN;
          __enable_interrupt();
          
          __disable_interrupt();
          GPIOF_AHB->DATA &= ~LED_GREEN;
          __enable_interrupt();
    }
    //return 0;
}
