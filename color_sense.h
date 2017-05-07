/* color_sense.h
 * Declaration of color sensing protocols.
 */

#ifndef color_sense_h
#define color_sense_h

/********* Typedef declarations *********/
typedef enum Color {
  yellow = 0, red, blue, blac
} Color;

typedef enum Color1 {
  black = 0, non_black
} Color1;

/********* Exported function declarations *********/
extern int read_color();
extern int read_color1();

#endif
