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
    _LCD.print(0, 0, line);
    //    _lcd.print(KILOMETERS);

    dtostrf(gameData.pe, 6, 2, line);
    _LCD.print(0, 1, line);
    //    lcd.print("m");

    dtostrf(gameData.in, 6, 2, line);
    _LCD.print(0, 2, line);
    //    lcd.write(DEG);

    _LCD.print(12, 3, gameData.g);

    Serial.write(_SP.SYN);

  }

  delay(5);

}

//  if (!started) {
//
//    while (Serial.read() != 255)
//      delay(50);
//
//    digitalWrite(LED_BUILTIN, HIGH);
//    Serial.write(255);
//
//    while (Serial.available() < 20 )
//      delay(50);
//
//    Serial.readBytes(vesselName, 20);
//    _LCD.print(0, 0, vesselName);
//
//    started = true;
//
//  }
