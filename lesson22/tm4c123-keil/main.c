#include <stdint.h> // C99 standard integers
#include "bsp.h"

uint32_t stack_blinky1[40];
uint32_t *sp_blinky1 = &stack_blinky1[40];

void main_blinky1() {
    BSP_init();
    while (1) {
        BSP_ledGreenOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledGreenOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}

uint32_t stack_blinky2[40];
uint32_t *sp_blinky2 = &stack_blinky2[40];

void main_blinky2() {
    BSP_init();
    while (1) {
        BSP_ledBlueOn();
        BSP_delay(BSP_TICKS_PER_SEC / 2U);
        BSP_ledBlueOff();
        BSP_delay(BSP_TICKS_PER_SEC / 3U);
    }
}

/* background code: sequential with blocking version */
int main(void) {
    BSP_init();
		/*fabricate Cortex-M ISR stack frame for blinky1*/
		*(--sp_blinky1) = (1U << 24);		//xPSR
		*(--sp_blinky1) = (uint32_t)&(main_blinky1); /*PC*/
		*(--sp_blinky1) =	0x0000000EU;	/*LR*/ 
		*(--sp_blinky1) =	0x0000000CU;	/*R12*/ 
		*(--sp_blinky1) =	0x00000003U;	/*R3*/
		*(--sp_blinky1) =	0x00000002U;	/*R2*/ 
		*(--sp_blinky1) =	0x00000001U;	/*R1*/ 
		*(--sp_blinky1) =	0x00000000U;	/*R0*/ 
	
		/*fabricate Cortex-M ISR stack frame for blinky2*/
		*(--sp_blinky2) = (1U << 24);		//xPSR
		*(--sp_blinky2) = (uint32_t)&(main_blinky2); /*PC*/
		*(--sp_blinky2) =	0x0000000EU;	/*LR*/ 
		*(--sp_blinky2) =	0x0000000CU;	/*R12*/ 
		*(--sp_blinky2) =	0x00000003U;	/*R3*/
		*(--sp_blinky2) =	0x00000002U;	/*R2*/ 
		*(--sp_blinky2) =	0x00000001U;	/*R1*/ 
		*(--sp_blinky2) =	0x00000000U;	/*R0*/ 
	
		while(1) {
		}
		
    //return 0;
}


