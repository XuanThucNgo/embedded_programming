#include <stdint.h> // C99 standard integers
#include "miros.h"

OSThread * volatile OS_curr; /*point to the current thread*/
OSThread * volatile OS_next; /*point to the next thread to run*/

void OS_init(void) {
		/*set the PendSV interrup priority to the lowest level*/
		*(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);
}

void OS_sched(void) {
		if(OS_next != OS_curr) {
				*(uint32_t volatile *)0xE000ED04 |= (1U << 28);
		}
}

void OSThread_start(
	 OSThread *me,
	 OSThreadHandler threadHandler,
	 void *stkSto, uint32_t stkSize)
{
	  uint32_t *sp = (uint32_t*)((((uint32_t)stkSto +  stkSize) / 8) * 8);
		uint32_t *stk_limit;
	  *(--sp) = (1U << 24);		//xPSR
		*(--sp) = (uint32_t)&threadHandler; /*PC*/
		*(--sp) =	0x0000000EU;	/*LR*/ 
		*(--sp) =	0x0000000CU;	/*R12*/ 
		*(--sp) =	0x00000003U;	/*R3*/
		*(--sp) =	0x00000002U;	/*R2*/ 
		*(--sp) =	0x00000001U;	/*R1*/ 
		*(--sp) =	0x00000000U;	/*R0*/ 
	  /*adsp, fake registers R4-R11*/
		*(--sp) =	0x0000000BU;	/*R11*/ 
		*(--sp) =	0x0000000AU;	/*R10*/ 
		*(--sp) =	0x00000009U;	/*R9*/ 
		*(--sp) =	0x00000008U;	/*R8*/
		*(--sp) =	0x00000007U;	/*R7*/ 
		*(--sp) =	0x00000006U;	/*R6*/ 
		*(--sp) =	0x00000005U;	/*R5*/ 
		*(--sp) =	0x00000004U;	/*R4*/
	
		/* Save the top of the stack in the thread's attibute */
	
		me -> sp = sp;
		
		/* round up the bottom of the stack to the 8-byte boundary */
		
		stk_limit = (uint32_t*)(((((uint32_t)stkSto - 1U) / 8)+ 1U) * 8);

		/*pre fill the unused part of the stack with 0xDEADBEEF*/
		for(sp = sp - 1U; sp >= stk_limit; --sp) {
			 *sp = 0xDEADBEEFU;
		}	
}

void PendSV_Handler(void){
}


