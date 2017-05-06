/* communication.ino
 * Implementation of pin setup.
 */

#include "pins.h"

/********* Exported function definition *********/
extern void setup_pins()
{
  /* 18 kHz signal pins */
  pinMode(OSC_SETUP_1, OUTPUT);
  pinMode(OSC_SETUP_2, OUTPUT);
  pinMode(OSC_CARRIER, OUTPUT);
  pinMode(OSC_ENABLE, OUTPUT);
  /* communications input pin */
  pinMode(REC_IN, INPUT);t
  /* LED pins */
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  /* motor control output pins */
  pinMode(FRONT_R, OUTPUT);
  pinMode(FRONT_L, OUTPUT);
  pinMode(BACK_R, OUTPUT);
  pinMode(BACK_L, OUTPUT);
  /* color detection pins */
  pinMode(PHOTO_D, INPUT);
  pinMode(BLUE_D, OUTPUT);
  pinMode(RED_D, OUTPUT);
  /* collision detection pins */
  pinMode(FR_BUMP, INPUT);
  pinMode(F_BUMP, INPUT);
  pinMode(FL_BUMP, INPUT);
  pinMode(R_BUMP, INPUT);
  /* magnet detection pin */
  pinMode(HALL, INPUT);
}

