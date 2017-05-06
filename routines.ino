/* routines.ino
 * Implementation of behavior protocols.
 */

#include "routines.h"
#include "pins.h"
#include "led.h"
#include "motor_control.h"
#include "color_sense.h"
#include "communication.h"

#define DELAY_1s delay(1000)
#define DELAY_TURN delay(775/2)

/********* Helper function declarations *********/
/* led testing */
static void led_test();
static void color_test();
/* motor testing */
static void motor_test();
/* color detection testing */
static void photo_test();
/* comms testing */
static void send_test();
static void recv_test();

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
  //color_test();
  //motor_test();
  //photo_test();
  //send_test();
  recv_test();
}


/********* Helper function definitions *********/
static void led_test()
{
  Serial.println("Turning on red LED...");
  led_on(RED);
  DELAY_1s;
  Serial.println("Turning on blue LED...");
  led_on(BLUE);
  DELAY_1s;
  Serial.println("Turning on yellow LED...");
  led_on(YELLOW);
  DELAY_1s;
  Serial.println("Turning off LEDs");
  led_off(RED);
  led_off(BLUE);
  led_off(YELLOW);
  DELAY_1s;
  Serial.println("Blinking each LED");
  led_blink(RED, 3);
  led_blink(BLUE, 3);
  led_blink(YELLOW, 3);
  DELAY_1s;
  Serial.println("End led test\n");
}

static void color_test()
{
  Serial.println("Turning on red LED...");
  led_on(RED_D);
  DELAY_1s;
  Serial.println("Turning on blue LED...");
  led_on(BLUE_D);
  DELAY_1s;
  Serial.println("Turning off LEDs");
  led_off(RED_D);
  led_off(BLUE_D);
  DELAY_1s;
  Serial.println("End color test\n");
}

static void motor_test()
{
  Serial.println("Moving forward");
  forward();
  DELAY_1s; DELAY_1s;
  Serial.println("Stopping");
  halt();
  DELAY_1s;
  Serial.println("Turning around");
  turn_180();
  DELAY_1s;
  Serial.println("Moving backwards");
  backward();
  DELAY_1s;
  halt();
  DELAY_1s;
  Serial.println("Turning tests");
  turn_left();
  DELAY_TURN;
  halt();
  DELAY_1s;
  turn_right();
  DELAY_TURN;
  halt();
  turn_right();
  DELAY_TURN;
  halt();
  turn_right();
  DELAY_TURN;
  halt();
  DELAY_1s;
  Serial.println("Moving backward");
  backward();
  DELAY_1s;
  DELAY_1s;
  DELAY_1s;
  halt();
  DELAY_1s;
  Serial.println("End motor test\n");
}

static void photo_test()
{
  int input = read_color();
  String color;
  color = (input == yellow) ? "Yellow" : "ERROR";
  color = (input == red) ? "Red" : color;
  color = (input == blue) ? "Blue" : color;
  color = (input == black) ? "Black" : color;
  Serial.println(color);
  DELAY_1s;
}

static void send_test()
{
  Serial.println("Sending message 1");
  send_msg_1();
  delay(5000);
  Serial.println("Sending message 2");
  send_msg_2();
  delay(5000);
  Serial.println("Sending message 3");
  send_msg_3();
  delay(5000);
  Serial.println("Sending message 4");
  send_msg_4();
  delay(5000);
}

static void recv_test()
{
  Serial.println("Expecting message 1");
  recieve_msg_1();
}

