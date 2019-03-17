#pragma once

class KCC_Serial {

  private:
    static const unsigned int BAUD = 57600;
    static const byte SYN = 0x16;
    static const byte ACK = 0x06;
    static const byte NAK = 0x15;
    static const byte DC1 = 0x11;
    static const byte DC2 = 0x12;
    static const byte DC3 = 0x13;
    static const byte DC4 = 0x14;
    static const byte START[2];
    static const byte END  [2];
    byte telemetryBuffer[TM_SIZE];

  public:
    KCC_Serial();
    void handshake();
    boolean pullTelemetry(Telemetry*);
    boolean pushCommands(CommandData*);

};

static const byte KCC_Serial::START[2] = { DC1, DC2 };
static const byte KCC_Serial::END  [2] = { DC3, DC4 };

extern KCC_Serial SER;
