#pragma once

typedef uint8_t SASMode;

class KCC_SASEncoder {

  private:
    static const SASMode OFF;
    static const SASMode AUTO;
    static const SASMode PROGRADE;
    static const SASMode RETROGRADE;
    static const SASMode NORMAL;
    static const SASMode ANTINORMAL;
    static const SASMode RADIAL;
    static const SASMode ANTIRADIAL;
    static const SASMode TARGET_PROGRADE;
    static const SASMode TARGET_RETROGRADE;
    SASMode state;

  public:
    void setup();
    SASMode query();

};

extern KCC_SASEncoder _SAS;
