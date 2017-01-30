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
const A_IN POT_1 = A0;
const A_IN SWTCH_1 = A8;
const A_IN SWTCH_2 = A9;

#endif
