/********TYPEDEF********/
typedef int COLOR;
typedef int A_IN; // analog input
typedef int D_IN; // digital input


/********CONSTANTS********/
// output pins
const COLOR RED    = 8;
const COLOR GREEN  = 9;
const COLOR BLUE   = 10;
const COLOR YELLOW = 11;

// input pins (A0-A7 pots, A8-A15 switches)
const A_IN POT_1 = 0;

// constants
const int ON = 255;
const int OFF = 0;

// variables
int state = 0;
int prev_state = 0;
int diag_problems = 0;
int analog_0 = 0;


/********FUNCTION DECLARATIONS********/
// state functions
void change_state(int);
void off_state();
void on_state();
void run_state();
void sleep_state();
void diagnos_state(int);

// LED behavior functions
void fade(COLOR,int);
void pulse(COLOR,int);


/********SETUP********/
void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);

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
    change_state(Serial.parseInt());
    Serial.print("Received: ");
    Serial.println(state, DEC);

    // if switching to diagnosis state
    if (state == 4) {
      Serial.print("Input # of problems to diagnose: ");
      while (Serial.available() <= 0) {        
      }
      diag_problems = Serial.parseInt();
      Serial.println(diag_problems, DEC);
    }
  }
  
  switch (state) {
    case 0:
      off_state();
      break;
    case 1:
      on_state();
      break;
    case 2:
      run_state();
      break;
    case 3:
      sleep_state();
      break;
    case 4:
      diagnos_state(diag_problems);
      state = prev_state; // return to previous state
      break;
  }
}


/********FUNCTION DEFINITIONS********/

void fade(COLOR light, int seconds) {
  int brightness = 255;
  while (brightness) {
    analogWrite(light,brightness);
    delay(seconds*1000/255); // to ensure 6 sec time constant
    brightness--;
  }
}

void pulse(COLOR light, int hz) {
  analogWrite(light,ON);
  delay(1000/hz/2);
  analogWrite(light,OFF);
  delay(1000/hz/2);
}


void change_state(int new_state) {
  prev_state = state;
  state = new_state;
}

void off_state() {
  analogWrite(BLUE,OFF);
  analogWrite(GREEN,OFF);
  analogWrite(RED,OFF);
  analogWrite(YELLOW,OFF);
}

void on_state() {
  pulse(RED,10);
}

void run_state() {
  fade(GREEN,6);

  // duty cycle
  for (int i=0; i<2; i++) {
    pulse(GREEN,2);
  }

  // interrupts
  
}

void sleep_state() {
  for (int i=0; i<4; i++) {
    pulse(BLUE,4);
  }

  fade(BLUE,1);
  change_state(0);
}

void diagnos_state(int problems) {
  for (int i=0; i<problems; i++) {
    pulse(RED,1);
  }
}


