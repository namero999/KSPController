#pragma once

#include <LiquidCrystal_I2C.h>

typedef uint8_t DisplayMode;

class KCC_LCD {

  private:
    static const DisplayMode OFF     = 0;
    static const DisplayMode ORBITAL = 1;
    static const DisplayMode SURFACE = 2;
    static const DisplayMode TARGET  = 3;
    uint8_t modeSwitchPin1;
    uint8_t modeSwitchPin2;
    DisplayMode currentMode = OFF;
    DisplayMode readModeSwitch();
    void splash();
    LiquidCrystal_I2C _lcd;

  public:
    KCC_LCD(uint8_t modeSwitchPin1, uint8_t modeSwitchPin2);
    void clear();
    void update();
    template <typename T> void print(uint8_t, uint8_t, T);

};

extern KCC_LCD* LCD;
