
int main() {
    int counter = 0;
    while(counter < 20){
        ++counter;
        if ((counter & 1) != 0) {
          /*do something when the counter is odd*/
        }
        else {
          /*do something when the counter is even*/
        }
          
    } 
    ++counter;
    return 0;
}

0001 0010 == 18                 0001 0101 == 21
0000 0001 == 1                  0000 0001 == 1
---------------                 ----------------
0000 0000 == 0                  0000 0001 == 1
