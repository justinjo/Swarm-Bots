/* 
 *  currState_machine.ino
 *  Created by Justin Jo
 *  Last Modified: Feb 14, 2017
 */

/********INCLUDES********/
#include "constants.h"
#include "led.h"


/********VARIABLES********/
int currState = 0;
int prevState = 0;
int diagProblems = 0;
int analogPot0 = 0;
int analogPot1 = 0;
unsigned long currMillis;  // timing variable
bool isTransition = false;
bool runFlag0 = false;     // set by interrupts, switch 1
bool runFlag1 = false;     // switch 2

// LEDs
LED red;
LED blue;
LED green;
LED yellow;


/********FUNCTION DECLARATIONS********/
// state functions
void changeState(int newState);
void offState();
void onState();
void runState();
void sleepState();
void diagnosState(int problems);

void resetLEDs();
void setupLED(LED *led, byte lux, byte maxLux, byte state, int hz, int sec, int cnt);
void fade(LED *led);
void pulse(LED *led);


/********SETUP********/
void _setup() {
  // set up LED pins
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  red.pin = RED;
  green.pin = GREEN;
  blue.pin = BLUE;
  yellow.pin = YELLOW;

  pinMode(POT_0, INPUT);
  pinMode(POT_1, INPUT);
  pinMode(SWTCH_0, INPUT);
  pinMode(SWTCH_1, INPUT);

  // set up serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ready to go...");
}


/********LOOP********/
void _loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    changeState(Serial.parseInt());
    Serial.print("Received: ");
    Serial.println(currState, DEC);

    // if switching to diagnosis
    if (currState == 4) {
      analogWrite(red.pin, 255); // use as signal for diagnostic mode
      Serial.print("Input # of problems to diagnose: ");
      while (Serial.available() <= 0) {}
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

  /* reset behavior upon transition to state */
  if (isTransition) {
    setupLED(&red, ~0, ~0, PULSE, 10, 0, 0);
    isTransition = false;
  }

  pulse(&red);
}

/*  runState */
void runState() {
  currMillis = millis();

  if (isTransition) {     /* reset behavior */
    setupLED(&green, ~0, ~0, FADE, 2, 6, 0);
    setupLED(&blue, ~0, ~0, PULSE, 1, 0, 0);
    //setupLED(&yellow, ~0, ~0, OFF, 0, 0, 0);
    isTransition = false;
  }

  analogPot0 = analogRead(POT_0);
  analogPot1 = analogRead(POT_1);

  runFlag0 = analogRead(SWTCH_0) > 512;
  runFlag1 = analogRead(SWTCH_1) > 512;
  
  switch(green.state) {
    case FADE:
      fade(&green);
      if (green.lux == 0) {
        green.state = PULSE;
        green.lux = ~0;
      }
      break;
    case PULSE:
      pulse(&green);
      if (green.toggleCnt > 2) {
        green.state = FADE;
        green.lux = ~0;
        green.toggleCnt = 0;
      }
      break;
  }

  // take care of switches -> will change this to interrupts at some point
  if (runFlag0) {   // switch 1
    blue.toggleHz = 1;
    analogWrite(red.pin, 0);
  } else {
    blue.toggleHz = 10;
    if (runFlag1) {  // switch 2
      analogWrite(red.pin, 255);
    } else {
      analogWrite(red.pin, 0);
    }
  }
  pulse(&blue);

  // potentiometers change the flash pattern and brightness of the yellow LED
  // high potentiometer value -> faster, brighter
  // low potentiometer value -> slower, dimmer
  // flash pattern range: 1 hz to 10 hz [(0 to 9) + 1]
  // brightness range:    0 to 255    [(0 to 255) + 0]
  yellow.toggleHz = analogPot0*9/1023+1;
  yellow.maxLux  = analogPot1*255/1023;
  pulse(&yellow);
}

void sleepState() {
  currMillis = millis();
  
  if (isTransition) {   /* reset behavior */
    setupLED(&blue, ~0, ~0, PULSE, 4, 1, 0);
    isTransition = false;
  }

  switch(blue.state) {
    case PULSE:
      pulse(&blue);
      if (blue.toggleCnt > 3) {
        blue.state = FADE;
      }
      break;
    case FADE:
      fade(&blue);
      if (blue.lux == 0) {
        changeState(0);
      }
      break;
  };
}

void diagnosState(int problems) {
  currMillis = millis();
  
  if (isTransition) {   /* reset behavior */
    setupLED(&red, ~0, ~0, PULSE, 1, 0, 0);
    isTransition = false;
  }

  pulse(&red);

  if (red.toggleCnt >= problems) {
    currState = prevState; // return to previous state
    resetLEDs();
  }
}



void resetLEDs() {
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  analogWrite(YELLOW, 0);
}

void setupLED(LED *led, byte lux, byte maxLux, byte state, int hz, int sec, int cnt) {
  led->lux       = lux;
  led->maxLux    = maxLux;
  led->state     = state;
  led->toggleHz  = hz;
  led->fadeSec   = sec;
  led->toggleCnt = cnt;
  led->startTime = millis();
  analogWrite(led->pin, led->lux);
}

void fade(LED *led) {
  if (currMillis - led->startTime > 1000*led->fadeSec/led->maxLux) {
    led->lux--;
    led->startTime = millis();
    analogWrite(led->pin, led->lux);
  }
}

void pulse(LED *led) {
  /* toggle LED every x ms, where x = 500ms/toggle hz */
  if (currMillis - led->startTime > 500/led->toggleHz) {
    if (led->lux) {
      led->lux = 0;
    } else {
      led->lux = led->maxLux;
      led->toggleCnt++;
    }
    led->startTime = millis();
    analogWrite(led->pin, led->lux);
  }
}
