/* swarmbot.ino
 * Contains the setup and main loop for the swarmbots.
 */

#include "pins.h"
#include "routines.h"
#include "motor_control.h"

void setup()
{
  setup_pins();

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
  /*
  Serial.println("Enter challenge number:");
  while (Serial.available() == 0) {}
  int challenge_num = Serial.parseInt();
  Serial.print("Challenge number ");
  Serial.println(challenge_num, DEC);
  
  Serial.println("Enter bot number:");
  while (Serial.available() == 0) {}
  int bot_num = Serial.parseInt();
  Serial.print("Bot number ");
  Serial.println(bot_num, DEC);

  challenge(bot_num, challenge_num);
  */
  
  diagnostic();
}
