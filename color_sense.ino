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
/* returns color read by photosensor */
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

  if (blue_val < 90) {
    color = black;
  } else if (black_val > 10) {
    color = yellow;
  } else if (blue_val < 300) {
    color = blue;
  } else {
    color = red;
  }
  
  return color;
}


/* specific color reading calibrated to bot 1 */
extern int read_color1()
{
  analogWrite(BLUE_D, LOW);
  analogWrite(RED_D, HI);
  int red_val = analogRead(PHOTO_D);
  int color = (red_val < 500) ? _black : non_black;
  return color;
}

/* specific color reading calibrated to bot 2 */
extern int read_color2()
{
  analogWrite(BLUE_D, LOW);
  analogWrite(RED_D, HI);
  int red_val = analogRead(PHOTO_D);
  int color = (red_val > 95) ? non_black : _black;
  return color;
}

/********* Helper function definition *********/
/* controls the colored LEDs near the photodetector */
static void set_color(int blue_lum, int red_lum, int delay_time)
{
  unsigned long start_delay = millis();
  analogWrite(BLUE_D, blue_lum);
  analogWrite(RED_D, red_lum);
  while (millis() - start_delay < delay_time) {}
}

