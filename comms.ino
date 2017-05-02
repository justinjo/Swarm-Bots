/* comms.ino
 * Implementation of communication protocols.
 */

#include "constants.h"
#include "comms.h"

static const MSG_LEN_1 = 200;
static const MSG_LEN_2 = 300;
static const MSG_LEN_3 = 400;
static const MSG_LEN_4 = 500;

/********* Helper function declarations *********/
static bool get_message(int exp_time);

extern void send_msg_1()
{
  digitalWrite(OSC_EN, HIGH);
  delay(MSG_LEN_1);
  digitalWrite(OSC_EN, LOW);
}

extern void send_msg_2()
{
  digitalWrite(OSC_EN, HIGH);
  delay(MSG_LEN_2);
  digitalWrite(OSC_EN, LOW);
}

extern void send_msg_3()
{
  digitalWrite(OSC_EN, HIGH);
  delay(MSG_LEN_3);
  digitalWrite(OSC_EN, LOW);
}

extern void send_msg_4()
{
  digitalWrite(OSC_EN, HIGH);
  delay(MSG_LEN_4);
  digitalWrite(OSC_EN, LOW);
}

/* Returns only when message 1 is detected */
extern void recieve_msg_1()
{
  get_message(MSG_LEN_1);
}

extern void recieve_msg_2()
{
  get_message(MSG_LEN_2);
}

extern void recieve_msg_3()
{
  get_message(MSG_LEN_3);
}

extern void recieve_msg_4()
{
  get_message(MSG_LEN_4);
}

/********* Helper function definitions *********/
static bool get_message(



