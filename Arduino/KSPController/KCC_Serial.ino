void KCC_Serial::setup() {
  Serial.begin(BAUD);
}

void KCC_Serial::handshake() {

  _LCD.print(0, 1, "Waiting For Jeb...");

  while (Serial.read() != SYN)
    delay(500);

  Serial.write(ACK);

  _LCD.clear();

}

byte serialBuffer[sizeof(GameData)];

boolean KCC_Serial::readPacket(GameData* gameData) {

  if (Serial.available() && Serial.readBytesUntil(END, serialBuffer, sizeof(serialBuffer)))  {
    memcpy(gameData, serialBuffer, sizeof(GameData));
    Serial.write(SYN);
    return true;
  }
  
  return false;

}
