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
bool isTransition = false;

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

void resetLEDs();


/********SETUP********/
void setup() {
  // set up LED pins
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  red.pin = RED;
  green.pin = GREEN;
  blue.pin = BLUE;
  yellow.pin = YELLOW;

  // set up serial communication
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
      analogWrite(red.pin, 255); // use as signal for diagnostic mode
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
      break;
  }
}


/********FUNCTION DEFINITIONS********/

/*  changeState
 *  Changes the current state */
void changeState(int newState) {
  isTransition = (newState != currState);
  prevState = currState;
  currState = newState;
  resetLEDs();
}

/* offState
 * All LEDs off */
void offState() {
  resetLEDs();
}

/*  onState
 *  Pulse @ 10 Hz  */
void onState() {
  currMillis = millis();

  /* reset time upon transition to state */
  if (isTransition) {
    red.startTime = currMillis;
    red.maxLux = ~0;
    red.lux = red.maxLux;
    red.state = BLINK;
    red.toggleHz = 10;
    isTransition = false;
  }

  analogWrite(red.pin, red.lux);

  /* toggle LED every x ms, where x = 500ms/toggle hz */
  if (currMillis - red.startTime > 500/red.toggleHz) {
    if (red.lux) {
      red.lux = 0;
    }
    else {
      red.lux = red.maxLux;
    }
    red.startTime = millis();
  }
}

/*  runState */
void runState() {
  currMillis = millis();

  /* reset time upon transition to state */
  if (isTransition) {
    startMillis = currMillis;
    green.startTime = currMillis;
    blue.startTime = currMillis;
    yellow.startTime = currMillis;

    green.state = FADE;
    green.fadeSec = 6;
    green.toggleHz = 2;
    green.toggleCnt = 0;
    green.maxLux = ~0;
    green.lux = maxLux;
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
  currMillis = millis();
  
  if (isTransition) {
    blue.startTime = currMillis;
    blue.maxLux = ~0;
    blue.lux = blue.maxLux;
    blue.state = BLINK;
    blue.fadeSec = 1;
    blue.toggleHz = 4;
    blue.toggleCnt = 0;
    isTransition = false;
  }
  
  analogWrite(blue.pin, blue.lux);

  switch(blue.state) {
    case BLINK:
      if (currMillis - blue.startTime > 500/blue.toggleHz) {
        if (blue.lux) {
          blue.lux = 0;
        }
        else {
          blue.lux = blue.maxLux;
          blue.toggleCnt++;
        }
        blue.startTime = millis();
      }
      if (blue.toggleCnt > 3) {
        blue.state = FADE;
      }
      break;
    case FADE:
      if (currMillis - blue.startTime > 1000/255*blue.fadeSec) {
        blue.lux--;
        if (blue.lux == 0) {
          changeState(0);
        }
        blue.startTime = millis();
      }
      break;
  };
  

}

void diagnosState(int problems) {
  currMillis = millis();
  
  if (isTransition) {
    red.startTime = currMillis;
    red.maxLux = ~0;
    red.lux = red.maxLux;
    red.state = BLINK;
    red.toggleHz = 1;
    red.toggleCnt = 0;
    isTransition = false;
  }

  analogWrite(red.pin, red.lux);

  if (currMillis - red.startTime > 500/red.toggleHz) {
    if (red.lux) {
      red.lux = 0;
    }
    else {
      red.lux = red.maxLux;
      red.toggleCnt++;
    }
    red.startTime = millis();
  }
  
  if (red.toggleCnt >= problems) {
    currState = prevState; // return to previous currState
  }
}


void resetLEDs() {
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  analogWrite(YELLOW, 0);
}


