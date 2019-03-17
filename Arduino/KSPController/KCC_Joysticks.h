#pragma once

class KCC_Joysticks {

  private:
    static const int SCALE = 100;
    static const int DEADZONE = 5;
    int adjust(int val);
    uint8_t xPin;
    uint8_t yPin;
    uint8_t zPin;

  public:
    KCC_Joysticks(uint8_t xPin, uint8_t yPin, uint8_t zPin);
    void read();

};
