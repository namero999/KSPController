#ifndef KCC_LCD_h
#define KCC_LCD_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class KCCLCD {

  public:
    void setup();
    template <class T> void print(uint8_t, uint8_t, T);

};

extern KCCLCD _LCD;

#endif
