#pragma once

typedef char SASMode;

class KCC_SASEncoder {

  private:
    static const SASMode OFF               = 0;
    static const SASMode AUTO              = 1;
    static const SASMode PROGRADE          = 2;
    static const SASMode RETROGRADE        = 3;
    static const SASMode NORMAL            = 4;
    static const SASMode ANTINORMAL        = 5;
    static const SASMode RADIAL            = 6;
    static const SASMode ANTIRADIAL        = 7;
    static const SASMode TARGET_PROGRADE   = 8;
    static const SASMode TARGET_RETROGRADE = 9;

  public:
    void setup();
    void update();
    void next();
    void prev();
    SASMode currentMode = OFF;

};

extern KCC_SASEncoder _SAS;
