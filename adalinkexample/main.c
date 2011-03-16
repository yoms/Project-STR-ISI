#include <stdio.h>
extern int Flip_Flop1();
extern void adainit (void);  
extern void adafinal (void); 
int main() {   
  adainit();
  printf("coucou!");
  Flip_Flop1();   
  adafinal();
  return 0;
}
