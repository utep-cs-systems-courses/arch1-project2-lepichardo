#include <msp430.h>
#include "timerLib.h"
#include "buzzer.h"

// Define switches
#define sw1 1
#define sw2 2
#define sw3 4
#define sw4 8
#define switches 15


int main() {
  configureClocks();

  P2REN |= switches;
  P2IE |= switches;
  P2OUT |= switches;
  P2DIR &= ~switches;
  
  buzzer_init();
  settingBuzzer();

  or_sr(0x18);          // CPU off, GIE on
}

void settingBuzzer(){
  // start buzzing!!!
  switch_interrupt_handler();
}
void switch_interrupt_handler(){

  char pval = P2IN;

  P2IES |= (pval & ~switches);	/* if switch up, sense down */
  P2IES &= (pval | switches);	/* if switch down, sense up */
  
  if (~pval & sw1){
    buzzer_set_period(0000);
  }
  
  if (~pval & sw2){
    buzzer_set_period(1000);
  }
  
  if (~pval & sw3){
    buzzer_set_period(1500);
  }
  
  if (~pval & sw4){
    buzzer_set_period(2000);
  }
  
}
void __interrupt_vec(PORT2_VECTOR) Port_2(){
   if (P2IFG & switches) { 
     P2IFG &= ~switches;
     switch_interrupt_handler(); 
   }
}
