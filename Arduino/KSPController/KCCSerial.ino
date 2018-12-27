void KCCSerial::setup() {
  Serial.begin(BAUD);
}

void KCCSerial::handshake() {

  _LCD.print(0, 1, "Waiting For Jeb...");

  while (Serial.read() != SYN)
    delay(500);

  Serial.write(ACK);

  _lcd.clear();

}
