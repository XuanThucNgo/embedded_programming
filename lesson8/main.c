#include<tm4c.h>

#define LED_RED    (1U << 1)
#define LED_BLUE   (1U << 2)
#define LED_GREEN  (1U << 3)

void delay(int iter);        

void delay(int iter){
  int volatile counter;
  counter = 0;
  while (counter < iter) {  //delay loop
        ++counter;
  }
}

int main(){
  
  SYSCTL_RCGCGPIO_R  |= (1U << 5); //Turn on port F  
  SYSCTL_GPIOHBCTL_R |= (1U << 5); //Enable AHB for GPIOF
  GPIO_PORTF_AHB_DIR_R   |= (LED_RED | LED_BLUE | LED_GREEN); //GPIO F Direction
  GPIO_PORTF_AHB_DEN_R   |= (LED_RED | LED_BLUE | LED_GREEN); //GPIO F Digital Enable

  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  while(1) {
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
    
    delay(1000000);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
    
    delay(500000);
  }
  return 0;
}
