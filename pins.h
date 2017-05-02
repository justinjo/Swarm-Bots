/* pins.h
 * Definition of pin assignments
 * 2  - setup for comms
 * 5  - comms carrier
 * 8  = front right motor pin
 * 9  - front left motor pin
 * 10 - back right motor pin
 * 11 - back left motor pin
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

/* Motor control pins */
const PIN FRONT_R = 8;
const PIN FRONT_L = 9;
const PIN BACK_R  = 10;
const PIN BACK_L  = 11;

#endif
