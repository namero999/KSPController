#pragma once

#include "Arduino.h"

class KCC_Serial {

  private:
    static const unsigned int BAUD = 57600;

  public:
    static const byte SYN = 0x16;
    static const byte ACK = 0x06;
    static const byte NAK = 0x15;
    static const byte DC1 = 0x11;
    static const byte DC2 = 0x12;
    static const byte DC3 = 0x13;
    static const byte DC4 = 0x14;
    void setup();
    void handshake();
    boolean readData(GameData*);

};

extern KCC_Serial _SP;
