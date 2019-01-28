#pragma once

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

typedef uint8_t DisplayMode;

class KCC_LCD {

  private:
    static const DisplayMode ORBITAL = 1;
    static const DisplayMode SURFACE = 2;
    static const DisplayMode TARGET = 3;
    DisplayMode getMode();
    LiquidCrystal_I2C _lcd;

  public:
    KCC_LCD();
    void setup();
    void update();
    void clear();
    template <typename T> void print(uint8_t, uint8_t, T);

};

extern KCC_LCD _LCD;
