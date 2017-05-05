/* collision.ino
 * Implementation of collision detection protocols.
 */

#include "collision.h"

/********* Exported function definitions *********/
/* reads all the bumper pins and returns a byte denoting which bumpers
 * have collided with the wall
 */
extern byte check_bumpers()
{
  byte collision = 0;
  
  collision |= (digitalRead(FR_BUMP)) ? fr_bump : collision;
  collision |= (digitalRead(F_BUMP)) ? f_bump : collision;
  collision |= (digitalRead(FL_BUMP)) ? fl_bump : collision;
  collision |= (digitalRead(R_BUMP)) ? r_bump : collision;

  return collision;
}

