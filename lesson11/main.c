#include <stdint.h>

#include "tm4c.h"
#include "delay.h"

#define LED_RED    (1U << 1)
#define LED_BLUE   (1U << 2)
#define LED_GREEN  (1U << 3) 

uint8_t                 u8a, u8b;
uint16_t                u16b, u21d;
uint32_t                u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;

int main(){
  u8a = sizeof(uint8_t);
  u16b = sizeof(uint16_t);
  u32e = sizeof(uint32_t);
  u8a = 0xa1U;
  u16b = 0xc1c2U;
  u32e = 0xe1e2e3e4U;
  
  u8b = u8a;
  u21d = u16b;
  u32f = u32e;
  
  u16b = 40000U;
  u21d = 40000U;
  u32e = (uint32_t)u16b + u21d;
  
  u16b = 100U;
  //s32 = 10 - u16b;
  s32 = 10 - (int16_t)u16b;
  // when mix a signed and unsigned operands both are promoted to "unsigned int" 
//=> the result is "unsigned int". Subsequently, the result is converted to signed 32-bit 
//   because s32 is 32-bit match with 32 bit-ARM => So it fills completely the s32 variable
//   but 16 bit not same 

  
  //if(u32e > -1)   // -1 always promotes the signed to unsigned int => -1 -> 0xFFFFFFFF => fix that
  if((int32_t)u32e > -1)
    u8a = 1U;
  else
    u8a = 0U;
  
  u8a = 0xffU;
  /*
  if (~u8a == 0x00U) {
    u8b = 1U;
  }
  0xffU will be promoted gets promoted to 0x000000ff (8 to 32 bit promotion). 
  therefore ~u8a will be 0xffffff00 which is not 0
  => fix that*/
  if ((uint8_t)~u8a == 0x00U) {
    u8b = 1U;
  }
  
  SYSCTL_RCGCGPIO_R  |= (1U << 5); //Turn on port F  
  SYSCTL_GPIOHBCTL_R |= (1U << 5); //Enable AHB for GPIOF
  GPIO_PORTF_AHB_DIR_R   |= (LED_RED | LED_BLUE | LED_GREEN); //GPIO F Direction
  GPIO_PORTF_AHB_DEN_R   |= (LED_RED | LED_BLUE | LED_GREEN); //GPIO F Digital Enable

  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  while(1) {
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
    delay(500000);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
    
    delay(500000);
  }
  //return 0;
}
