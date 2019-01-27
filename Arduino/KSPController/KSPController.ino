#include "Constants.h"
#include "GameData.h"
#include "KCCSerial.h"
#include "KCCLCD.h"
#include "KCCEncoder4SAS.h"

GameData gameData;
const int gdSize = sizeof(gameData);

byte buf[100];
char line[10];

void setup() {

  initPins();

  _LCD.setup();

  _SP.setup();
  _SP.handshake();

  _LCD.print(10, 0, gdSize);

}

int i = 0;
void loop() {

  if (_SP.readPacket(buf)) {

    _LCD.print(0, 0, ++i);
    _LCD.print(0, 1, gdSize);

    memcpy(&gameData, buf, gdSize);

    if (i < 2) {
      _LCD.print(2, 2, gameData.vessel);
      _LCD.print(10, 2, gameData.body);
    }

    _LCD.print(2, 3, gameData.pe);
    _LCD.print(12, 3, gameData.hS);

    Serial.write(_SP.SYN);

  }

  delay(2);

}







//if (Serial.available() >= gdSize) {
//
//    Serial.readBytes(buf, gdSize);
//
//    memcpy(&gameData, buf, gdSize);
//
//    dtostrf(gameData.ap, 6, 2, line);
//    _LCD.print(0, 0, "Apo: ");
//    _LCD.print(5, 0, line);
//    //    _lcd.print(KILOMETERS);
//
//    dtostrf(gameData.pe, 6, 2, line);
//    _LCD.print(0, 1, "Per: ");
//    _LCD.print(5, 1, line);
//    //    lcd.print("m");
//
//    dtostrf(gameData.in, 6, 2, line);
//    _LCD.print(0, 2, "Inc: ");
//    _LCD.print(5, 2, line);
//    //    lcd.write(DEG);
//
//    //    _LCD.print(12, 3, gameData.g);
//
//    //    _SASMODE.query();
//
//    Serial.write(_SP.SYN);
//
//  }
