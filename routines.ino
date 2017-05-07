/* routines.ino
 * Implementation of behavior protocols.
 */

#include "routines.h"
#include "pins.h"
#include "led.h"
#include "motor_control.h"
#include "color_sense.h"
#include "communication.h"
#include "collision.h"

#define DELAY_1s delay(1000)
#define DELAY_TURN delay(775/2)

/********* Helper function declarations *********/
/* challenge routines */
static void challenge1_bot1();
static void challenge1_bot2();
static void challenge2_bot1();
static void challenge2_bot2();
static void detect_color(int color);
static void hit_wall();
static void follow_path(int color);
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
extern void challenge(int bot_num, int challenge_num)
{
  if (challenge_num == 1) {
    if (bot_num == 1) {
      challenge1_bot1();
    } else {
      challenge1_bot2();
    }
  } else {
    if (bot_num == 1) {
      challenge2_bot1();
    } else {
      challenge2_bot2();
    }
  }
}

extern void diagnostic()
{
  //led_test();
  //color_test();
  //motor_test();
  //photo_test();
  //send_test();
  //recv_test();
  detect_color(yellow);
  led_on(YELLOW);
  hit_wall();
  led_off(YELLOW);
  backward();
  detect_color(red);
  led_on(RED);
  halt();
}


/********* Helper function definitions *********/
static void challenge1_bot1()
{
  detect_color(yellow);
  led_on(YELLOW);
  hit_wall();
  led_off(YELLOW);
  backward();
  detect_color(red);
  led_on(RED);
  
  /* path detection on red, search for magnet */
  halt();
  /* flash blue led */
  receive_msg_1();

  /* path detection on red until wall */
  halt();
  led_blink(RED, 2);
  backward();
  delay(10);
  turn_180();
  halt();
  send_msg_2();
  receive_msg_4();

  /* path detection on red until yellow */
  
  
}

static void challenge1_bot2()
{
  receive_msg_2();
  detect_color(yellow);
  led_on(YELLOW);
  hit_wall();
  backward();
  detect_color(blue);
  
}

static void challenge2_bot1()
{
  motor_test();
}

static void challenge2_bot2()
{
  motor_test();
}

static void detect_color(int color)
{
  while (read_color() != color) {}
  led_on(YELLOW);
}

static void hit_wall()
{
  forward();
  while (check_bumpers() == 0) {}
  halt();
}

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
  DELAY_1s; DELAY_1s; DELAY_1s;
  halt();
  DELAY_1s;
  Serial.println("End motor test\n");
}

static void photo_test()
{
  /*
  Serial.println("Blue LED/Blue Patch");
  analogWrite(RED_D, 255);
  //analogWrite(BLUE_D, 150);
  while (1) {
    Serial.println(analogRead(PHOTO_D));
  }
  */
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
  receive_msg_1();
}

