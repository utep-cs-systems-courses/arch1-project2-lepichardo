#ifndef stateMachine_included
#define stateMachine_included

int state;

char toggle_green();
void state_green_advance();
char toggle_red();
void state_red_advance();
void state_both_advance();
void state_stop();

#endif // included


