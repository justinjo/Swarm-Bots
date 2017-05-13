/* communication.ino
   Implementation of communication protocols.
*/

#include "pins.h"
#include "communication.h"

/********* Constant declarations *********/
static const int MSG_LEN_1 = 200;
static const int MSG_LEN_2 = 300;
static const int MSG_LEN_3 = 400;
static const int MSG_LEN_4 = 600;
static const int ERROR_LST = 0;
static const int ERROR_TRN = 25;

/********* Helper function declarations *********/
static void get_message(int exp_time);
static void get_message_err(int exp_time);
/* control over 18kHz generation */
static void enable_18k();
static void disable_18k();

/********* Exported function definitions *********/
extern void send_msg_1()
{
  enable_18k();
  digitalWrite(OSC_ENABLE, HIGH);
  delay(MSG_LEN_1);
  digitalWrite(OSC_ENABLE, LOW);
}

extern void send_msg_2()
{
  enable_18k();
  digitalWrite(OSC_ENABLE, HIGH);
  delay(MSG_LEN_2);
  digitalWrite(OSC_ENABLE, LOW);
}

extern void send_msg_3()
{
  enable_18k();
  digitalWrite(OSC_ENABLE, HIGH);
  delay(MSG_LEN_3 + ERROR_TRN);
  digitalWrite(OSC_ENABLE, LOW);
}

extern void send_msg_4()
{
  enable_18k();
  digitalWrite(OSC_ENABLE, HIGH);
  delay(MSG_LEN_4);
  digitalWrite(OSC_ENABLE, LOW);
}

/* Returns only when message 1 is detected */
extern void receive_msg_1()
{
  disable_18k();
  get_message(MSG_LEN_1);
}

extern void receive_msg_2()
{
  disable_18k();
  get_message(MSG_LEN_2);
}

extern void receive_msg_3()
{
  disable_18k();
  get_message(MSG_LEN_3);
}

extern void receive_msg_4()
{
  disable_18k();
  get_message(MSG_LEN_4);
}

/* < 45 - message 1
 *  45-55 - message 2
 *  55-65 - message 3
 *  65-75 - message 4
 *  20 + y = 40
 *  30 + y = 50
 */
/********* Helper function definitions *********/
static void get_message(int exp_time)
{
  int pulse_count;
  int upper_bound = exp_time / 10 + 5;
  int lower_bound = exp_time / 10 - 5;
  unsigned long start_time, intermediary;
  bool received = false;
  
  while (!received) {
    pulse_count = 0;
    start_time = millis();
    intermediary = start_time;

    /* wait for detection */
    while (digitalRead(REC_IN) != HIGH) {}
    
    /* record pulse train w/ period 10 ms */
    while (millis() - start_time < exp_time * 3) {
      if (millis() - intermediary > 10) {
        pulse_count += (digitalRead(REC_IN) == HIGH) ? 1 : 0;
        intermediary = millis();
      }
    }
    Serial.print(millis() - start_time, DEC);
    Serial.print(' ');
    Serial.print(pulse_count, DEC);
    Serial.print(' ');
    Serial.println(lower_bound, DEC);
    received = (pulse_count >= lower_bound) && (pulse_count <= upper_bound);
  }
}

static void get_message_err(int exp_time)
{
  int pulse_count;
  int upper_bound = exp_time / 10 + 25;
  int lower_bound = exp_time / 10 + 15;
  unsigned long start_time, intermediary;
  bool received = false;
  
  while (!received) {
    pulse_count = 0;
    start_time = millis();
    intermediary = start_time;

    /* wait for detection */
    while (digitalRead(REC_IN) != HIGH) {}
    
    /* record pulse train w/ period 10 ms */
    while (millis() - start_time < exp_time * 3) {
      if (millis() - intermediary > 10) {
        pulse_count += (digitalRead(REC_IN) == HIGH) ? 1 : 0;
        intermediary = millis();
      }
    }
    Serial.print(millis() - start_time, DEC);
    Serial.print(' ');
    Serial.print(pulse_count, DEC);
    Serial.print(' ');
    Serial.println(lower_bound, DEC);
    received = (pulse_count >= lower_bound) && (pulse_count <= upper_bound);
  }
}

/* 18kHz signal enable */
static void enable_18k()
{
  /* 18.523 kHz signal setup, output on pin 5 */
  TCCR3A = _BV(COM3A0) | _BV(COM3B0) | _BV(WGM30) | _BV(WGM31);
  TCCR3B = _BV(WGM32) | _BV(WGM33) |  _BV(CS31);
  OCR3A  = 53;
}

static void disable_18k()
{
  TCCR3A = 1;
  TCCR3B = 3;
  OCR3A  = 0;
}




