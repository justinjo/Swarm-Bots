/* motor_control.ino
 * Implementation of motor control functions.
 */
 
/********* Constant declarations *********/
static const int STRAIGHT = 50;
static const int TURN = 75;
static const int ROTATE = 75;
static const int ROTATE_DELAY = 775;
 
/********* Exported function definitions *********/
/* motion functions */
extern void halt()
{
  analogWrite(FRONT_R, LOW);
  analogWrite(FRONT_L, LOW);
  analogWrite(BACK_R, LOW);
  analogWrite(BACK_L, LOW);
}

extern void forward()
{
  analogWrite(BACK_R, LOW);
  analogWrite(BACK_L, LOW);
  analogWrite(FRONT_R, STRAIGHT);
  analogWrite(FRONT_L, STRAIGHT);
}

extern void backward()
{
  analogWrite(FRONT_R, LOW);
  analogWrite(FRONT_L, LOW);
  analogWrite(BACK_R, STRAIGHT);
  analogWrite(BACK_L, STRAIGHT);
}

extern void turn_left()
{
  analogWrite(FRONT_L, TURN);
  analogWrite(BACK_R, TURN);
  analogWrite(BACK_L, LOW);
  analogWrite(FRONT_R, LOW);
}

extern void turn_right()
{
  analogWrite(BACK_L, TURN);
  analogWrite(FRONT_R, TURN);
  analogWrite(FRONT_L, LOW);
  analogWrite(BACK_R, LOW);
}

extern void turn_180()
{
  analogWrite(BACK_L, ROTATE);
  analogWrite(FRONT_R, ROTATE);
  analogWrite(FRONT_L, LOW);
  analogWrite(BACK_R, LOW);
  unsigned long start_delay = millis();
  while(millis() - start_delay < ROTATE_DELAY) {}
  halt();
}
