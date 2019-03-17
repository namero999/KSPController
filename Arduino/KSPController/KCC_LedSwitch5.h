#pragma once

class KCC_LedSwitch5 {

  private:
    uint8_t ledPin;
    uint8_t togglePin;
    bool on = false;
    bool wasDown = false;

  protected:
    KCC_LedSwitch5(uint8_t ledPin, uint8_t togglePin);
    bool update();
    bool isOn() {
      return on;
    }

};
