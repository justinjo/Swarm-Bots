/* pins.h
 * Definition of pin assignments
 * 
 * A0 - color detection input
 * A1 - front left bumper input
 * A2 - front bumper input
 * A3 - front right bumper input
 * A4 - rear bumper input
 * 2  - setup for comms
 * 5  - comms carrier
 * 6  - blue color detection LED
 * 7  - red color detection LED
 * 8  - front right motor pin
 * 9  - front left motor pin
 * 10 - back right motor pin
 * 11 - back left motor pin
 * 12 - enable for comms
 * 13 - setup for comms
 * 50 - input for comms
 * 51 - red LED output
 * 52 - blue LED output
 * 53 = yellow LED output
 */

#ifndef pins_h
#define pins_h

/* TYPEDEF */
typedef int Pin;

/* 18 kHz signal pins */
const Pin OSC_SETUP_1 = 2;
const Pin OSC_SETUP_2 = 13;
const Pin OSC_CARRIER = 5;
const Pin OSC_ENABLE  = 12;
const Pin REC_IN      = 50;

/* LED output pins */
const Pin RED    = 51;
const Pin BLUE   = 52;
const Pin YELLOW = 53;

/* Motor control pins */
const Pin FRONT_R = 8;
const Pin FRONT_L = 9;
const Pin BACK_R  = 10;
const Pin BACK_L  = 11;

/* Color detection pins */
const Pin PHOTO_D = A0;
const Pin BLUE_D  = 6;
const Pin RED_D   = 7;

/* Collision detection pins */
const Pin FR_BUMP = A1;
const Pin F_BUMP  = A2;
const Pin FL_BUMP = A3;
const Pin R_BUMP  = A4;

/********* Exported function declarations *********/
extern void setup_pins();

#endif
