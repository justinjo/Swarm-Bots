/* swarmbot.ino
 * Contains the setup and main loop for the swarmbots.
 */

#include "pins.h"
#include "routines.h"

void setup()
{
  setup_pins();
  Serial.begin(9600);
  Serial.println("Ready to go...");
}

void loop()
{
  diagnostic();
}
