/* constants.h
 * Contains pin assignment and general constants
 * 2  - setup for comms
 * 5  - comms carrier
 * 12 - enable for comms
 * 13 - setup for comms
 * 52 - input for comms
 */

#ifndef constants_h
#define constants_h

/* TYPEDEF */
typedef int PIN;

/* 18 kHz signal pins */
const PIN OSC_SETUP_1 = 2;
const PIN OSC_SETUP_2 = 13;
const PIN OSC_CARRIER = 5;
const PIN OSC_ENABLE  = 12;
const PIN REC_IN      = 52;

#endif
