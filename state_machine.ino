/* 
 *  currState_machine.ino
 *  Created by Justin Jo
 *  Last Modified: Jan 27, 2017
 */

/********INCLUDES********/
#include "constants.h"
#include "led.h"


/********VARIABLES********/
int currState = 0;
int prevState = 0;
int diagProblems = 0;
int analog0 = 0;

// timing variable
unsigned long startMillis;
unsigned long currMillis;

// LEDs
LED red;
LED blue;
LED green;
LED yellow;


/********FUNCTION DECLARATIONS********/
// state functions
void changeState(int);
void offState();
void onState();
void runState();
void sleepState();
void diagnosState(int);


/********SETUP********/
void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  red.pin = RED;
  green.pin = GREEN;
  blue.pin = BLUE;
  yellow.pin = YELLOW;

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ready to go...");
}


/********LOOP********/
void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    changeState(Serial.parseInt());
    Serial.print("Received: ");
    Serial.println(currState, DEC);

    // if switching to diagnosis currState
    if (currState == 4) {
      Serial.print("Input # of problems to diagnose: ");
      while (Serial.available() <= 0) {
      }
      diagProblems = Serial.parseInt();
      Serial.println(diagProblems, DEC);
    }
  }
  
  switch (currState) {
    case 0:
      offState();
      break;
    case 1:
      onState();
      break;
    case 2:
      runState();
      break;
    case 3:
      sleepState();
      break;
    case 4:
      diagnosState(diagProblems);
      currState = prevState; // return to previous currState
      break;
  }
}


/********FUNCTION DEFINITIONS********/

/*  changeState
 *  Changes the current state */
void changeState(int newState) {
  prevState = currState;
  currState = newState;
}

/* offState
 * All LEDs off */
void offState() {
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  analogWrite(YELLOW, 0);
}

/*  onState
 *  Pulse @ 10 Hz  */
void onState() {
  currMillis = millis();

  /* reset time upon transition to state */
  if (currState != prevState) {
    red.startTime = currMillis;
    red.brightness = ~0;
  }
  
  analogWrite(red.pin, red.brightness);

  /* toggle LED every 50 ms */
  if (currMillis - red.startTime > 50) {
    red.brightness = ~red.brightness;
    red.startTime = millis();
  }
}

/*  runState */
void runState() {
  currMillis = millis();

  /* reset time upon transition to state */
  if (currState != prevState) {
    startMillis = currMillis;
    red.startTime = currMillis;
    blue.startTime = currMillis;
    yellow.startTime = currMillis;
  }
  
  /*fade(GREEN,6);
  
  int brightness = 255;
  while (brightness) {
    analogWrite(light,brightness);
    delay(seconds*1000/255); // to ensure 6 sec time constant
    brightness--;
  }
  
  // duty cycle
  for (int i=0; i<2; i++) {
    //pulse(GREEN,2);
  }

  // interrupts
  */
}

void sleepState() {
  for (int i=0; i<4; i++) {
    //pulse(BLUE,4);
  }

  //fade(BLUE,1);
  changeState(0);
}

void diagnosState(int problems) {
  for (int i=0; i<problems; i++) {
    //pulse(RED,1);
  }
}


