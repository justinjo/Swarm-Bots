#ifndef constants_h
#define constants_h

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
const A_IN POT_0 = A0;
const A_IN POT_1 = A1;
const A_IN SWTCH_0 = A8;
const A_IN SWTCH_1 = A9;

// LED modes
const byte OFF   = 0;
const byte PULSE = 1;
const byte FADE  = 2;

#endif
