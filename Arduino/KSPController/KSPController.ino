#include "Constants.h"
#include "GameData.h"
#include "KCCSerial.h"
#include "KCCLCD.h"
#include "KCCEncoder4SAS.h"

void setup() {

  initPins();

  _LCD.setup();

  _SP.setup();
  _SP.handshake();

}

GameData gameData;
const int gdSize = sizeof(gameData);
byte buf[gdSize];
char line[10];

void loop() {

  if (Serial.available() >= gdSize) {

    Serial.readBytes(buf, gdSize);

    memcpy(&gameData, buf, gdSize);

    dtostrf(gameData.ap, 6, 2, line);
    _LCD.print(0, 0, "Apo: ");
    _LCD.print(5, 0, line);
    //    _lcd.print(KILOMETERS);

    dtostrf(gameData.pe, 6, 2, line);
    _LCD.print(0, 1, "Per: ");
    _LCD.print(5, 1, line);
    //    lcd.print("m");

    dtostrf(gameData.in, 6, 2, line);
    _LCD.print(0, 2, "Inc: ");
    _LCD.print(5, 2, line);
    //    lcd.write(DEG);

    _LCD.print(12, 3, gameData.g);

//    _SASMODE.query();

    Serial.write(_SP.SYN);

  }

  delay(5);

}
