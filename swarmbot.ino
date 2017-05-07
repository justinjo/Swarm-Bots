/* swarmbot.ino
 * Contains the setup and main loop for the swarmbots.
 */

#include "pins.h"
#include "routines.h"
#include "motor_control.h"
#include "communication.h"

void setup()
{
  setup_pins();
  Serial.begin(9600);
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
