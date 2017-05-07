/* led.h
 * Declaration of led control functions.
 */

#ifndef led_h
#define led_h

/********* Exported function declarations *********/
/* led control functions */
extern void led_on(int pin);
extern void led_off(int pin);
extern void led_blink(int blinks, int pin1, int pin2);

#endif
