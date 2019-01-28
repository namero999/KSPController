#pragma once

#include "Arduino.h"

class KCC_Serial {

  private:
    static const unsigned int BAUD = 57600;

  public:
    static const byte SYN = 0x5E; // ^
    static const byte ACK = 0x7E; // ~
    static const byte END = 0x17;
    void setup();
    void handshake();
    boolean readPacket(GameData*);

};

extern KCC_Serial _SP;
