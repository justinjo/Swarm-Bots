/* color_sense.ino
 * Implementation of color sensing protocols.
 */

#include "color_sense.h"

/********* Constant declarations *********/
static const int MED = 150;
static const int HI = 255;
static const int MED_DELAY = 50;
static const int LONG_DELAY = 100;

/********* Helper function declaration *********/
static void set_color(int blue_lum, int red_lum, int delay_time);

/********* Exported function definitions *********/
extern int read_color()
{
  int blue_val, red_val, yellow_val, black_val, color;

  set_color(MED, LOW, LONG_DELAY);
  blue_val = analogRead(PHOTO_D);
  
  set_color(LOW, HI, MED_DELAY);
  red_val = analogRead(PHOTO_D);
  
  set_color(MED, HI, MED_DELAY);
  yellow_val = analogRead(PHOTO_D);
  
  set_color(LOW, LOW, LONG_DELAY);
  black_val = analogRead(PHOTO_D);


  if (blue_val < 200) {
    color = red;
  } else if (red_val < 400) {
    color = black;
  } else if (red_val < 600) {
    color = blue;
  } else {
    color = yellow;
  }/*
  if (red_val > 650 && black_val > 5) {
    color = yellow;
  } else if (red_val > 200) {
    color = red;
  } else if (red_val > 70 && blue_val > 650) {
    color = blue;
  } else {
    color = black;
  }
*/
  /*
  Serial.print("Blue: ");
  Serial.println(blue, DEC);
  Serial.print("Red: ");
  Serial.println(red, DEC);
  Serial.print("Yellow: ");
  Serial.println(yellow, DEC);
  Serial.print("Black: ");
  Serial.println(black, DEC);*/
  return color;
}

/********* Helper function definition *********/
static void set_color(int blue_lum, int red_lum, int delay_time)
{
  unsigned long start_delay = millis();
  analogWrite(BLUE_D, blue_lum);
  analogWrite(RED_D, red_lum);
  while (millis() - start_delay < delay_time) {}
}

