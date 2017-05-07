/* led.h
 * Implementation of led control functions.
 */

 #include "led.h"

/********* Constant declarations *********/
static const int DELAY = 500;

 /********* Exported function definitions *********/
extern void led_on(int pin)
{
  digitalWrite(pin, HIGH);
}

extern void led_off(int pin)
{
  digitalWrite(pin, LOW);
}

/* flashes [blinks] number of times. pin2 is an optional argument */
extern void led_blink(int blinks, int pin1, int pin2 = -1)
{
  int blink_count = 0;
  unsigned long start_time = millis();
  
  while (blink_count < blinks) {
    led_on(pin1);
    led_off(pin2);
    while (millis() - start_time < DELAY) {}
    led_off(pin1);
    led_on(pin2);
    while (millis() - start_time < DELAY * 2) {}
    blink_count++;
    start_time = millis();
  }
  led_off(pin2);
}

