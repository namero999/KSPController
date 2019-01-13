#ifndef KCC_ENC_h
#define KCC_ENC_h

typedef uint8_t SASMode;

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

class KCCEncoder4SAS {

  private:
    SASMode state;
    void setupInterrupts();

  public:
    void setup();
    SASMode query();

};

extern KCCEncoder4SAS _SASMODE;

#endif
