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

byte serialBuffer[GD_SIZE];

boolean KCC_Serial::readData(GameData* gameData) {

  static boolean progress = false;
  static uint8_t index = 0;

  while (Serial.available() > 1) {

    if (progress) {
      
      if (index < GD_SIZE) {
        serialBuffer[index++] = Serial.read();
      }
      else {
    
        progress = false;
        index = 0;
        
        if (Serial.read() == DC3 && Serial.read() == DC4) {
          memcpy(gameData, serialBuffer, GD_SIZE);
          Serial.write(ACK);
          return true;
        }
        else {
          Serial.write(NAK);
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

//uint8_t bytes = Serial.readBytes(serialBuffer, GD_SIZE);
//      if (Serial.read() == DC3 && Serial.read() == DC4) {
//        memcpy(gameData, serialBuffer, GD_SIZE);
//        Serial.write(SYN);
//        return true;
//      }
