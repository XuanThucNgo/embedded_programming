
int counter = 0;
int main(){
  int *p_int; //khai bao con tro
  p_int = &counter;
  while(*p_int < 21){
    ++(*p_int);
  }
  //p_int = (int *)0x20000000U;
    return 0;
}
