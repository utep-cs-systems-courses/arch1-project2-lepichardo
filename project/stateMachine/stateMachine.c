#include <msp430.h>
#include "stateMachine.h"
#include "led.h"

char toggle_green(){
  green_on ^= 1;
  return 1;
}

void state_green_advance(){
  red_on = 0;
  char changed = 0;  
  changed = toggle_green();
  led_changed = changed;
  led_update();
}

char toggle_red(){
  red_on ^= 1;
  return 1;
}

void state_red_advance(){
  green_on = 0;
  char changed = 0;  
  changed = toggle_red();
  led_changed = changed;
  led_update();
}
void state_both_advance(){
  char changed = 0;
  changed = toggle_red();
  changed = toggle_green();
  led_changed = changed;
  led_update();
}

void state_stop(){
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;
}
int state = 0;
void __interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 125) {
    if(state == 1){
      state_red_advance();
    }
    else if(state == 2){
      state_green_advance();
    }
    else if(state == 3){
      state_both_advance();
    }
    else{
      state_stop();
    }
    blink_count = 0;
  }
}
