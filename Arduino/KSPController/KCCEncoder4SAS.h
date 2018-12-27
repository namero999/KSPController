#ifndef KCC_ENC_h
#define KCC_ENC_h

class KCCEncoder4SAS {

  private:
    void initInterrupts();

  public:
    void setup();

};

extern KCCEncoder4SAS _SASMODE;

#endif
