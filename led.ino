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

extern void led_blink(int pin, int blinks)
{
  int blink_count = 0;
  unsigned long start_time = millis();
  
  while (blink_count < blinks) {
    led_on(pin);
    while (millis() - start_time < DELAY) {}
    led_off(pin);
    while (millis() - start_time < DELAY * 2) {}
    blink_count++;
    start_time = millis();
  }
}

