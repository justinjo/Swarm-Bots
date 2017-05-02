/* pins.h
 * Contains pin assignment
 * 2  - setup for comms
 * 5  - comms carrier
 * 12 - enable for comms
 * 13 - setup for comms
 * 22 - input for comms
 * 51 - red LED output
 * 52 - blue LED output
 * 53 = yellow LED output
 */

#ifndef pins_h
#define pins_h

/* TYPEDEF */
typedef int PIN;

/* 18 kHz signal pins */
const PIN OSC_SETUP_1 = 2;
const PIN OSC_SETUP_2 = 13;
const PIN OSC_CARRIER = 5;
const PIN OSC_ENABLE  = 12;
const PIN REC_IN      = 22;

/* LED output pins */
const PIN RED    = 51;
const PIN BLUE   = 52;
const PIN YELLOW = 53;

#endif
