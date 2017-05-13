/* color_sense.h
 * Declaration of color sensing protocols.
 */

#ifndef color_sense_h
#define color_sense_h

/********* Typedef declarations *********/
/* originally planned color differentiation for path detection */
typedef enum Color {
  yellow = 0, red, blue, black
} Color;

/* modified color differentiation (black vs non-black) */
typedef enum Color1 {
  _black = 0, non_black
} Color1;

/********* Exported function declarations *********/
/* returns color read by photosensor */
extern int read_color();
/* specific color reading calibrated to bots 1 and 2, respectively */
extern int read_color1();
extern int read_color2();

#endif
