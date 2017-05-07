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
static void detect_color1(int color);
static void hit_wall();
static void follow_path_mag(int color);
static void follow_path_wall(int color);
static void follow_path_end(int color);
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
  challenge1_bot1();
  //follow_path_wall(non_black);
}


/********* Helper function definitions *********/
static void challenge1_bot1()
{
  /* detect yellow patch, light yellow LED, then move to wall */
  detect_color1(non_black);
  led_on(YELLOW);
  hit_wall();

  /* turn off LED and back up until path detected */
  led_off(YELLOW);
  backward();
  delay(200);
  detect_color1(non_black);
  
  /* turn on red LED and follow path until landmine */
  led_on(RED);
  halt();
  turn_right();
  delay(300);
  halt();
  led_off(RED);
  follow_path_mag(non_black);

  /* blink the blue LED twice and message the CCP */
  led_blink(2, BLUE);
  send_msg_1();

  /* wait for CCP to relay message and follow path to the wall */
  receive_msg_1();
  follow_path_wall(non_black);

  /* blink red LED twice, then turn around and signal CCP */
  led_blink(2, RED);
  backward();
  delay(400);
  turn_180();
  halt();
  send_msg_2();

  /* stay still and wait for message from other bot */
  receive_msg_4();

  /* follow the path to its end and find the corner */
  follow_path_end(non_black);
  backward();
  delay(400);
  turn_left();
  delay(400);
  hit_wall();
  while (1) {}
}

static void challenge1_bot2()
{
  receive_msg_2();
  detect_color(yellow);
  led_on(YELLOW);
  hit_wall();
  led_off(YELLOW);
  backward();
  detect_color(red);
  led_on(RED);
  halt();
  turn_right();
  delay(50);
  halt();
  /* path detection on red, search for magnet */
  follow_path_mag(red);
  led_blink(2, BLUE);
  send_msg_3();
  receive_msg_3();
  /* path detection on red until wall */
  follow_path_wall(red);
  led_blink(2, RED);
  backward();
  delay(10);
  turn_180();
  halt();
  send_msg_4();

  follow_path_end(red);
  
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
}

static void detect_color1(int color)
{
  while (read_color1() != color) {}
}

static void hit_wall()
{
  forward();
  while (check_bumpers() == 0) {}
  halt();
}

static void follow_path_mag(int color)
{
  bool right_streak = false;
  forward();
  while (digitalRead(HALL) == HIGH) {
    Serial.println(analogRead(PHOTO_D), DEC);
    if (read_color1() != color) {
      /* when off path, turn accordingly to get back on path */
      if (right_streak) {
        turn_right();
      } else {
        turn_left();
      }
      delay(250);
      backward();
      delay(100);
      forward();
      right_streak = !right_streak;
    }
  }
  halt();
}

static void follow_path_wall(int color)
{
  bool right_streak = true;
  forward();
  while (check_bumpers() == 0) {
    if (read_color1() != color) {
      /* when off path, turn accordingly to get back on path */
      if (right_streak) {
        turn_right();
      } else {
        turn_left();
      }
      delay(250);
      backward();
      delay(100);
      forward();
      right_streak = !right_streak;
    }
  }
  halt();
}

static void follow_path_end(int color)
{
  bool right_streak = false;
  forward();
  while (check_bumpers() == 0) {
    if (read_color1() != color) {
      /* when off path, turn accordingly to get back on path */
      if (right_streak) {
        turn_right();
      } else {
        turn_left();
      }
      delay(250);
      backward();
      delay(100);
      forward();
      right_streak = !right_streak;
    }
  }
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
  led_blink(3, RED);
  led_blink(3, BLUE);
  led_blink(3, YELLOW);
  DELAY_1s;
  led_blink(10, RED, BLUE);
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
  
  Serial.println("Blue LED/Blue Patch");
  analogWrite(RED_D, 255);
  //analogWrite(BLUE_D, 150);
  while (1) {
    Serial.println(analogRead(PHOTO_D));
  }
  
  /*
  int input = read_color1();
  String color;
  color = (input == yellow) ? "Yellow" : "ERROR";
  color = (input == red) ? "Red" : color;
  color = (input == blue) ? "Blue" : color;
  color = (input == black) ? "Black" : color;
  color = (input == non_black) ? "Non black" : color;
  Serial.println(color);
  DELAY_1s;
  */
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

