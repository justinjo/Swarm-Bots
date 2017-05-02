/* color_sense.h
 * Declaration of color sensing protocols.
 */

#ifndef color_sense_h
#define color_sense_h

/********* Typedef declarations *********/
typedef enum Color {
  yellow = 0, red, blue, black
} Color;

/********* Exported function declarations *********/
extern int read_color();

#endif
