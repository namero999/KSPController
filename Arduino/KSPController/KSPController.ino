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

}

void loop() {

  if (_SP.readData(&gameData))
    _LCD.update();

  delay(1);

}
