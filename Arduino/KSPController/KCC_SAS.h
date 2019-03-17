#pragma once

class KCC_SAS : public KCC_LedSwitch5, KCC_Encoder {

  private:
    static const SASMode OFF        = -1;
    static const SASMode AUTO       =  0;
    static const SASMode MANOUVER   =  1;
    static const SASMode PROGRADE   =  2;
    static const SASMode RETROGRADE =  3;
    static const SASMode NORMAL     =  4;
    static const SASMode ANTINORMAL =  5;
    static const SASMode RADIAL     =  6;
    static const SASMode ANTIRADIAL =  7;
    static const SASMode TARGET     =  8;
    static const SASMode ANTITARGET =  9;
    SASMode lastMode    = AUTO;
    SASMode currentMode = OFF;

  public:
    KCC_SAS(uint8_t ledPin, uint8_t togglePin, uint8_t dataPin, uint8_t clockPin, uint8_t resetPin);
    bool update();
    SASMode get() {
      return currentMode;
    }
    void next();
    void prev();

};

extern KCC_SAS* SAS;
