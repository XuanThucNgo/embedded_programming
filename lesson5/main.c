#include<tm4c.h>

int main(){
  SYSCTL_RCGCGPIO_R  = 0x20U; //Turn on port F      
  GPIO_PORTF_DIR_R = 0x0EU; //GPIO F Direction
  GPIO_PORTF_DEN_R = 0x0EU; //GPIO F Digital Enable

  while(1) {
    GPIO_PORTF_DATA_R = 0x02U;
    int  counter = 0;
    while (counter < 1000000) {
        ++counter;
    }
    
    GPIO_PORTF_DATA_R = 0x00U;
    counter = 0;
    while (counter < 1000000) {
        ++counter;
    }
  }
  return 0;
}
