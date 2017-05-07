/* collision.h
 * Declaration of collision detection protocols.
 */

#ifndef collision_h
#define collision_h 

/********* Typedef declarations *********/
typedef enum Bumper {
  fr_bump = 1, f_bump = 2, fl_bump = 4, r_bump = 8
} Bumper;

/********* Exported function declarations *********/
extern byte check_bumpers();

#endif
