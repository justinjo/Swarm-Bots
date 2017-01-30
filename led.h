#ifndef led_h
#define led_h

struct LED {
  int pin;
  byte lux; // brightness
  byte maxLux; // for use in toggling
  byte state; // 0 for blink, 1 for fade
  int toggleHz;
  int fadeSec;
  unsigned long startTime;
};

#endif
