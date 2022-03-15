Switch
======

The directory switch has a main.c file which inlcudes the main function, the
swithc_interrupt_handler function, and the __interrupt_vec function.

The main function initializes the LEDS that will be used as well as the
switches that can be used in the toy. All switches used are going to be P2.0,
P2.1, P2.2, and P2.3. The LEDS used are P1.0 and P1.6.

The switch_interrupt_handler declares the value of P to know if P1 is used or
P2. In this case we will use P2, so we can manipulate the toy with four
differnet switches.

sw2 turns on both leds, sw3 turns off everything but the redLED, and sw4 turns
everything off but the greenLED

sw1 works differently, let's say that we have turned on both leds pressing
sw2, if we want to turn them off, we must press sw1 + sw2 so that both leds
turn off, the same way works when one led is turned on.

