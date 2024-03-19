#include<tm4c.h>

#define LED_RED    (1U << 1)
#define LED_BLUE   (1U << 2)
#define LED_GREEN  (1U << 3)
int main(){
  
  SYSCTL_RCGCGPIO_R  |= (1U << 5); //Turn on port F      
  GPIO_PORTF_DIR_R   |= (LED_RED | LED_BLUE | LED_GREEN); //GPIO F Direction
  GPIO_PORTF_DEN_R   |= (LED_RED | LED_BLUE | LED_GREEN); //GPIO F Digital Enable

  GPIO_PORTF_DATA_R |= LED_BLUE;
  while(1) {
    GPIO_PORTF_DATA_R |= LED_RED;
    int volatile counter = 0;
    while (counter < 1000000) {
        ++counter;
    }
    
    GPIO_PORTF_DATA_R &= ~LED_RED;
    counter = 0;
    while (counter < 1000000) {
        ++counter;
    }
  }
  return 0;
}
