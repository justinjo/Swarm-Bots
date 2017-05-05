/* routines.ino
 * Implementation of behavior protocols.
 */

#include "routines.h"
#include "pins.h"
#include "led.h"
#include "motor_control.h"

#define DELAY delay(1000)

/********* Helper function declarations *********/
static void led_test();
static void color_test();
static void motor_test();

/********* Exported function definitions *********/
extern void challenge1(int bot_num)
{
  
}

extern void challenge2(int bot_num)
{
  
}

extern void diagnostic()
{
  //led_test();
  color_test();
  //motor_test();
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
  DELAY;
  Serial.println("Blinking each LED");
  led_blink(RED, 3);
  led_blink(BLUE, 3);
  led_blink(YELLOW, 3);
  DELAY;
  Serial.println("End led test\n");
}

static void color_test()
{
  Serial.println("Turning on red LED...");
  led_on(RED_D);
  DELAY;
  Serial.println("Turning on blue LED...");
  led_on(BLUE_D);
  DELAY;
  Serial.println("Turning off LEDs");
  led_off(RED_D);
  led_off(BLUE_D);
  DELAY;
  Serial.println("End color test\n");
}

static void motor_test()
{
  Serial.println("Moving forward");
  forward();
  DELAY; DELAY;
  Serial.println("Stopping");
  halt();
  DELAY;
  Serial.println("Turning around");
  turn_180();
  DELAY;
  Serial.println("Moving backwards");
  backward();
  DELAY;
  halt();
  DELAY;
  Serial.println("Turning tests");
  turn_left();
  DELAY;
  halt();
  DELAY;
  turn_right();
  DELAY; DELAY; DELAY;
  halt();
  DELAY;
  Serial.println("Moving forward");
  forward();
  DELAY;
  halt();
  DELAY;
  Serial.println("End motor test\n");
}

