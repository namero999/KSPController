#include "Constants.h"
#include "GameData.h"
#include "KCC_LCD.h"
#include "KCC_Serial.h"
#include "KCC_Fuel.h"
#include "KCC_Controls.h"
#include "KCC_SASEncoder.h"

Telemetry telemetry;
CommandData commandData;

void setup() {

  initPins();

  _LCD.setup();

  _SP.setup();
  //  _SP.handshake();

  _SAS.setup();

}

SASMode lastMode = 0;

void loop() {

  //  if (_SP.pullTelemetry(&telemetry)) {
  //    _LCD.update();
  //    _FUEL.update(&telemetry);
  //  }
  //
  //  _CTRL.read();
  //
  //  _SP.pushCommands(&commandData);

  if (lastMode != _SAS.currentMode) {
    lastMode = _SAS.currentMode;
    Serial.println((short)lastMode);
  }

  delay(1);

}
