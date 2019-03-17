KCC_Serial::KCC_Serial() {
  Serial.begin(BAUD);
}

void KCC_Serial::handshake() {

  LCD.print(0, 1, F("Waiting For Jeb..."));
  LCD.print(9, 3, F("...as usual"));

  while (Serial.read() != SYN)
    delay(500);

  Serial.write(ACK);

  LCD.clear();

}

boolean KCC_Serial::pullTelemetry(Telemetry* telemetry) {

  static uint8_t index = 0;
  static boolean progress = false;

  while (Serial.available() > 1) {

    if (progress) {

      if (index < TM_SIZE) {
        telemetryBuffer[index++] = Serial.read();
      }
      else {

        index = 0;
        progress = false;

        if (Serial.read() == DC3 && Serial.read() == DC4) {
          memcpy(telemetry, telemetryBuffer, TM_SIZE);
          return true;
        }
        else return false;

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
  Serial.write((byte*) command, CD_SIZE);
  Serial.write(END, 2);

}
