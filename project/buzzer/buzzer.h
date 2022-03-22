#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void buzzer_set_period(short cycles);
void settingBuzzer();
void switch_interrupt_handler();

#endif // included
