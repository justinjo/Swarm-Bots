#ifndef led_h
#define led_h

struct LED {
  int pin;
  byte brightness;
  unsigned long startTime;
};

#endif
