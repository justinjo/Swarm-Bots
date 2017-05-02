/* swarmbot.ino
 * Contains the setup and main loop for the swarmbots.
 */

#include "constants.h"

void setup()
{
  /* 18 kHz signal pins */
  pinMode(OSC_SETUP_1, OUTPUT);
  pinMode(OSC_SETUP_2, OUTPUT);
  pinMode(OSC_CARRIER, OUTPUT);
  pinMode(OSC_ENABLE, OUTPUT);
  /* comms input pins */
  pinMode(REC_IN, INPUT);

  Serial.begin(9600);

  /* 18.523 kHz signal setup, output on pin 5 */
  TCCR3A = _BV(COM3A0) | _BV(COM3B0) | _BV(WGM30) | _BV(WGM31);
  TCCR3B = _BV(WGM32) | _BV(WGM33) |  _BV(CS31);
  OCR3A = 53;

  /* Let's go! */
  Serial.println("Ready to go...");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.print("");
}
