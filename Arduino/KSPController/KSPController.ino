#include "Constants.h"
#include "GameData.h"
#include "KCC_LCD.h"
#include "KCC_Serial.h"
#include "KCC_SASEncoder.h"

GameData gameData;

void setup() {

  initPins();

  _LCD.setup();

  _SP.setup();
  _SP.handshake();

  _LCD.print(10, 0, sizeof(gameData));
  _LCD.print(10, 1, sizeof(GameData));

}

void loop() {

  if (_SP.readPacket(&gameData))
    _LCD.update();

  delay(1);

}


//char line[10];
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
