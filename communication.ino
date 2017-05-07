/* communication.ino
   Implementation of communication protocols.
*/

#include "pins.h"
#include "communication.h"

/********* Constant declarations *********/
static const int MSG_LEN_1 = 200;
static const int MSG_LEN_2 = 300;
static const int MSG_LEN_3 = 400;
static const int MSG_LEN_4 = 500;
static const int ERROR_LEN = 150;

/********* Helper function declarations *********/
static void get_message(int exp_time);
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
  delay(MSG_LEN_3);
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
  get_message(MSG_LEN_1 + ERROR_LEN);
}

extern void receive_msg_2()
{
  disable_18k();
  get_message(MSG_LEN_2 + ERROR_LEN);
}

extern void receive_msg_3()
{
  disable_18k();
  get_message(MSG_LEN_3 + ERROR_LEN);
}

extern void receive_msg_4()
{
  disable_18k();
  get_message(MSG_LEN_4 + ERROR_LEN);
}


/********* Helper function definitions *********/
static void get_message(int exp_time)
{
  int pulse_count = 0;
  int upper_bound = exp_time / 10 + 5;
  int lower_bound = exp_time / 10 - 5;
  bool received = false;

  while (!received) {
    /* wait for detection */
    while (digitalRead(REC_IN) != HIGH) {}
    pulse_count += (digitalRead(REC_IN) == HIGH) ? 1 : 0;

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




