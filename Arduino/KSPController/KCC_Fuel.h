#pragma once

class KCC_Fuel {

  private:
    uint8_t pwmPin;

  public:
    KCC_Fuel(uint8_t pwmPin);
    void update(Telemetry*);

};
