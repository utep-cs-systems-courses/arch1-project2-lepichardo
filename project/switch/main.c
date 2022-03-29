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
#define switches (BIT0 | BIT1 | BIT2 | BIT3)

int main(void){

  configureClocks();

  P1DIR |= leds;
  P1OUT &= ~leds;

  P2REN |= switches;
  P2IE |= switches;
  P2OUT |= switches;
  P2DIR &= ~switches;

  
  //enableWDTInterrupts(); 
  or_sr(0x18); 
}

void switch_interrupt_handler(){
  char pval = P2IN;

  P2IES |= (pval & switches);	/* if switch up, sense down */
  P2IES &= (pval | ~switches);	/* if switch down, sense up */
  
  if (~pval & sw1){
    P1OUT &= ~greenLed;
    P1OUT |= redLed;
  }
  
  if (~pval & sw2){
    P1OUT &= ~redLed;
    P1OUT |= greenLed;
  }

  if (~pval & sw3){
    P1OUT &= ~leds;
  }
  
}
void __interrupt_vec(PORT2_VECTOR) Port_2(){
   if (P2IFG & switches) { 
     P2IFG &= ~switches;
     switch_interrupt_handler(); 
   }
}
