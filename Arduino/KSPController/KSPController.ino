#include "Constants.h"
#include "GameData.h"
#include "KCC_Serial.h"
#include "KCC_LedSwitch5.h"
#include "KCC_Encoder.h"
#include "KCC_LCD.h"
#include "KCC_Fuel.h"
#include "KCC_Controls.h"
#include "KCC_SAS.h"

Telemetry telemetry;
CommandData commandData;

KCC_SAS SAS = KCC_SAS(PIN_SAS_LED, PIN_SAS_TOGGLE, PIN_SAS_DATA, PIN_SAS_CLOCK, PIN_SAS_RESET);

void setup() {

  initPins();

  _LCD.setup();

  _SP.setup();
  //  _SP.handshake();

}

void loop() {

  //  if (_SP.pullTelemetry(&telemetry)) {
  //    _LCD.update();
  //    _FUEL.update(&telemetry);
  //  }
  //
  //  _CTRL.read();
  //
  //  _SP.pushCommands(&commandData);

    if (SAS.update())
      Serial.println((short) SAS.get());

  delay(1);

}
