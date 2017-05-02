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
  int blue, red, yellow, black, color;

  set_color(MED, LOW, LONG_DELAY);
  blue = analogRead(PHOTO_D);
  
  set_color(LOW, HI, MED_DELAY);
  red = analogRead(PHOTO_D);
  
  set_color(MED, HI, MED_DELAY);
  yellow = analogRead(PHOTO_D);
  
  set_color(LOW, LOW, LONG_DELAY);
  black = analogRead(PHOTO_D);

  color = (red > 200) ? red : black;
  color = (red > 650 && black > 5) ? yellow : color;
  color = (red > 70 && blue > 650) ? blue : color;
  
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

