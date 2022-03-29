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

  
  // enableWDTInterrupts(); 
  or_sr(0x18); 
}

void switch_interrupt_handler(){
  char pval = P2IN;

  P2IES |= (pval & switches);	/* if switch up, sense down */
  P2IES &= (pval | ~switches);	/* if switch down, sense up */

  if (~pval & sw1){
    enableWDTInterrupts();
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


// global state vars that control blinking
int blinkLimit = 5;  // duty cycle = 1/blinkLimit
int blinkCount = 0;  // cycles 0...blinkLimit-1
int secondCount = 0; // state var representing repeating time 0…1s

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking 
  blinkCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= greenLed;
  } else		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~greenLed;

  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second
    secondCount = 0;
    blinkLimit ++;	     // reduce duty cycle
    if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7.
      blinkLimit = 0;
  }
} 

