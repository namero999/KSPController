#ifndef KCC_SERIAL_h
#define KCC_SERIAL_h

class KCCSerial {

  private:
    static const unsigned int BAUD = 38400;

  public:
    static const byte SYN = 0x5E; // ^
    static const byte ACK = 0x7E; // ~
    void setup();
    void handshake();

};

extern KCCSerial _SP;

#endif
