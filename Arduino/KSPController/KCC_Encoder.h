#pragma once

class KCC_Encoder {

  private:
    uint8_t dataPin;
    uint8_t clockPin;
    uint8_t resetPin;

  protected:
    KCC_Encoder(uint8_t dataPin, uint8_t clockPin, uint8_t buttonPin);
    void attachInterrupts(void (*dataFall), void (*clockFall));

};
