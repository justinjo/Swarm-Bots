/* routines.ino
 * Implementation of behavior protocols.
 */

#include "routines.h"
#include "pins.h"
#include "led.h"

#define DELAY delay(500)

/********* Helper function declarations *********/
static void led_test();
static void color_test();

/********* Exported function definitions *********/
extern void challenge1(int bot_num)
{
  
}

extern void challenge2(int bot_num)
{
  
}

extern void diagnostic()
{
  led_test();
  color_test();
}


/********* Helper function definitions *********/
static void led_test()
{
  Serial.println("Turning on red LED...");
  led_on(RED);
  DELAY;
  Serial.println("Turning on blue LED...");
  led_on(BLUE);
  DELAY;
  Serial.println("Turning on yellow LED...");
  led_on(YELLOW);
  DELAY;
  Serial.println("Turning off LEDs");
  led_off(RED);
  led_off(BLUE);
  led_off(YELLOW);
  Serial.println("Blinking each LED three times");
  led_blink(RED, 3);
  DELAY;
  led_blink(BLUE, 3);
  DELAY;
  led_blink(YELLOW, 3);
  DELAY;
  Serial.println();
}

static void color_test()
{
  Serial.println("Turning on red LED...");
  led_on(RED);
  DELAY;
  Serial.println("Turning on blue LED...");
  led_on(BLUE);
  DELAY;
  Serial.println("Turning on yellow LED...");
  led_on(YELLOW);
  DELAY;
  Serial.println("Turning off LEDs");
  led_off(RED);
  led_off(BLUE);
  led_off(YELLOW);
  Serial.println("Blinking each LED three times");
  led_blink(RED, 3);
  DELAY;
  led_blink(BLUE, 3);
  DELAY;
  led_blink(YELLOW, 3);
  DELAY;
  Serial.println();
}
