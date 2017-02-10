const int S4 = 8;
const int S1 = 9;
const int S2 = 10;
const int S3 = 11;

int n = 0;
int hi = 255;
int lo = 0;

void forward();
void reverse();
void brake();

void setup() {
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
  
  // set up serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ready to go...");
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    n = Serial.parseInt();
    Serial.print("Received: ");
    Serial.println(n, DEC);
  }

  switch(n) {
    case 0:
      brake();
      break;
    case 1:
      forward();
      break;
    case 2:
      reverse();
      break;
  }
}



void forward() {
  analogWrite(S4, hi);
  delay(5);
  analogWrite(S1, hi);
  delay(5);
}

void reverse() {
  analogWrite(S2, hi);
  delay(5);
  analogWrite(S3, hi);
  delay(5);
}

void brake() {
  analogWrite(S3, lo);
  delay(5);
  analogWrite(S1, lo);
  delay(5);
  analogWrite(S2, lo);
  delay(5);
  analogWrite(S4, lo);
  delay(5);

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
