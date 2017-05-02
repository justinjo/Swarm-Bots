/* swarmbot.ino
 * Contains the setup and main loop for the swarmbots.
 */

#include "pins.h"
#include "color_sense.h"
#include "communication.h"
#include "motor_control.h"

void setup()
{
  /* 18 kHz signal pins */
  pinMode(OSC_SETUP_1, OUTPUT);
  pinMode(OSC_SETUP_2, OUTPUT);
  pinMode(OSC_CARRIER, OUTPUT);
  pinMode(OSC_ENABLE, OUTPUT);
  /* communications input pin */
  pinMode(REC_IN, INPUT);
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
  Serial.println("Enter challenge number:");
  while (Serial.available() == 0) {}
  int challenge = Serial.parseInt();
  Serial.print("Challenge number ");
  Serial.println(challenge, DEC);
  
  Serial.println("Enter bot number:");
  while (Serial.available() == 0) {}
  int bot_num = Serial.parseInt();
  Serial.print("Bot number ");
  Serial.println(bot_num, DEC);
  
}
