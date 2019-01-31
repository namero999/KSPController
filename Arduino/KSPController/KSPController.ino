#include "Constants.h"
#include "GameData.h"
#include "KCC_LCD.h"
#include "KCC_Serial.h"
#include "KCC_SASEncoder.h"

Telemetry telemetry;
CommandData commandData;

void setup() {

  initPins();

  _LCD.setup();

  _SP.setup();
  _SP.handshake();

  commandData.attX = 10;
  commandData.attY = 11;
  commandData.attZ = 12;

}

void loop() {

  if (_SP.pullTelemetry(&telemetry))
    _LCD.update();

  _SP.pushCommands(&commandData);

  delay(1);

}
