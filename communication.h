/* communication.h
 * Declaration of communication protocols.
 */

#ifndef communication_h
#define communication_h

/********* Exported function declarations *********/
/* Transmission functions */
extern void send_msg_1();
extern void send_msg_2();
extern void send_msg_3();
extern void send_msg_4();

/* Receiving functions */
extern void receive_msg_1();
extern void receive_msg_2();
extern void receive_msg_3();
extern void receive_msg_4();

/* 18kHz signal enable */
extern void enable_18k();
extern void disable_18k();

#endif
