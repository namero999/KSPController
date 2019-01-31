void KCC_Serial::setup() {
  Serial.begin(BAUD);
}

void KCC_Serial::handshake() {

  _LCD.print(0, 1, F("Waiting For Jeb..."));
  _LCD.print(9, 3, F("...as usual"));

  while (Serial.read() != SYN)
    delay(500);

  Serial.write(ACK);

  _LCD.clear();

}

byte serialBuffer[TM_SIZE];

boolean KCC_Serial::pullTelemetry(Telemetry* telemetry) {

  static boolean progress = false;
  static uint8_t index = 0;

  while (Serial.available() > 1) {

    if (progress) {

      if (index < TM_SIZE) {
        serialBuffer[index++] = Serial.read();
      }
      else {

        progress = false;
        index = 0;

        if (Serial.read() == DC3 && Serial.read() == DC4) {
          memcpy(telemetry, serialBuffer, TM_SIZE);
          // Serial.write(ACK);
          return true;
        }
        else {
          // Serial.write(NAK);
          return false;
        }

      }

    }
    else if (Serial.read() == DC1 && Serial.read() == DC2) {
      progress = true;
    }

  }

  return false;

}

boolean KCC_Serial::pushCommands(CommandData* command) {

  Serial.write(START, 2);
  Serial.write((char*) command, CD_SIZE);
  Serial.write(END, 2);

}
