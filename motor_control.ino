const int EN1 = 2;
const int FWD1 = 3;
const int REV1 = 4;
const int EN2 = 5;
const int REV2 = 6;
const int FWD2 = 7;

int n = 0;
int hi = 255;
int hime = 127;
int med = 63;
int melo = 31;
int lo = 0;

void fwd_l(int h);
void fwd_r(int h);
void rev_l(int h);
void rev_r(int h);
void brk_l();
void brk_r();
void fwd(int h);
void rev(int h);
void lft(int m, int h);
void rgt(int m, int h);
void r_180(int h);
void l_180(int h);

void setup2() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(FWD1, OUTPUT);
  pinMode(REV1, OUTPUT);
  pinMode(REV2, OUTPUT);
  pinMode(FWD2, OUTPUT);
  n = 0;
 
  // set up serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ready to go...");
}

void loop2() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    n = Serial.parseInt();
    Serial.print("Received: ");
    Serial.println(n, DEC);
  }

  switch(n) {
    case 0:
      brk_l();
      brk_r();
      break;
    case 1:
      fwd_l(hi);
      break;
    case 2:
      rev_l(hi);
      break;
    case 3:
      fwd_r(hi);
      break;
    case 4:
      rev_r(hi);
      break;
    case 5:
      brk_l();
      break;
    case 6:
      brk_r();
      break;
    case 10:
      brk_l();
      brk_r();
      break;
    case 11:
      fwd(med);
      break;
    case 12:
      rev(med);
      break;
    case 13:
      lft(med,hi);
      break;
    case 14:
      rgt(med,hi);
      break;
    case 15:
      r_180(med);
      break;
    case 16:
      l_180(med);
      break;
    default:
      break;
  }
}



void fwd_l(int h) {
  analogWrite(EN1, LOW);
  delay(2);
  analogWrite(FWD1, h);
  delay(2);
  analogWrite(REV1, LOW);
  delay(2);
  analogWrite(EN1, hi);
  delay(2);
  n = -1;
}

void rev_l(int h) {
  analogWrite(EN1, LOW);
  delay(2);
  analogWrite(REV1, h);
  delay(2);
  analogWrite(FWD1, LOW);
  delay(2);
  analogWrite(EN1, hi);
  delay(2);
  n = -1;
}

void fwd_r(int h) {
  analogWrite(EN2, LOW);
  delay(2);
  analogWrite(FWD2, h);
  delay(2);
  analogWrite(REV2, LOW);
  delay(2);
  analogWrite(EN2, hi);
  delay(2);
  n = -1;
}

void rev_r(int h) {
  analogWrite(EN2, LOW);
  delay(2);
  analogWrite(REV2, h);
  delay(2);
  analogWrite(FWD2, LOW);
  delay(2);
  analogWrite(EN2, hi);
  delay(2);
  n = -1;
}

void brk_l() {
  analogWrite(EN1, LOW);
  delay(2);
  analogWrite(FWD1, LOW);
  delay(2);
  analogWrite(REV1, LOW);
  delay(2);
  n = -1;
}

void brk_r() {
  analogWrite(EN2, LOW);
  delay(2);
  analogWrite(REV2, LOW);
  delay(2);
  analogWrite(FWD2, LOW);
  delay(2);
  n = -1;
}

void fwd(int h) {
  fwd_l(h);
  fwd_r(h);
}

void rev(int h) {
  rev_l(h);
  rev_r(h);
}

void lft(int m, int h) {
  fwd_l(m);
  fwd_r(h);
}

void rgt(int m, int h) {
  fwd_l(h);
  fwd_r(m);
}

void r_180(int h) {
  fwd_r(h);
  rev_l(h);
  delay(2000);
  brk_l();
  brk_r();
}

void l_180(int h) {
  fwd_l(h);
  rev_r(h);
  delay(2000);
  brk_l();
  brk_r();
}




/*
1) The Arduino must perform the drive control logic. The drive power system must
deliver the power to the motors without adversely impacting or harming the
Arduino Mega board or the drive control logic. This requires a separate power
deliver subsystems for the motor and the electronic logic components. Design the
part of the subsystem for only one motor. Did you take friction and weight into
account? Show you calculations for force and acceleration and power.

2) Solve this phase in stages: learn to control one motor first, then control both
directions for one motor. The motor does not have to be mounted to the bot for
motion control during this phase of the project. Motion control will be
accomplished during the phase 2B.

3) Design your motor control circuit forward direction

4) Design your motor control circuit reverse direction

5) Design your motor control circuit to operate the motor in both directions

6) Estimate the electrical power vs available battery

7) An oscilloscope may be helpful to understand the effects of turning a motor on
and off to the overall system. A function generator may help you understand how
control logic is required to provide speed control to a motor prior to connecting up
any control devices.

8) How does noise impact your drive system? What can you do to minimize the
impact due to noise? Would it be helpful to research how to eliminate noise that
is fed back to the circuit by the motors? How do you go about doing this?
*/
