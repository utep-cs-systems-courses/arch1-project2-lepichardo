#include <msp430.h>
#include "timerLib.h"

// Define LEDS
#define redLed BIT0
#define greenLed BIT6
#define leds (BIT0 | BIT6)

// Define switches
#define sw1 BIT0
#define sw2 BIT1
#define sw3 BIT2
#define sw4 BIT3
#define switches (sw1 | sw2 | sw3 | sw4)


int main(void){

  configureClocks();

  P1DIR |= leds;
  P1OUT &= ~leds;

  P2REN |= switches;
  P2IE |= switches;
  P2OUT |= switches;
  P2DIR &= ~switches;

  or_sr(0x18); 
}

void switch_interrupt_handler(){
  char pval = P2IN;
  
  // sw1 works as ctrl for sw2,sw3,sw4 to turn off what they turn on
  if (pval & sw1){
    P1OUT &= ~leds;
  }
  // turns both leds on
  if (pval & sw2){
    P1OUT ^= leds;
  }
  // turns everything off but the redLED
  if (pval & sw3){
    P1OUT ^= redLed;
  }
  // turns everything off but the greenLED
  if (pval & sw4){
    P1OUT ^= greenLed;
  }
}
void __interrupt_vec(PORT2_VECTOR) Port_2(){
   if (P2IFG & switches) { 
     P2IFG &= ~switches;
     switch_interrupt_handler(); 
   }
}
