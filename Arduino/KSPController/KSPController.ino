#include "Constants.h"
#include "GameData.h"
#include "KCC_LCD.h"
#include "KCC_Serial.h"
#include "KCC_LedSwitch5.h"
#include "KCC_Encoder.h"
#include "KCC_Fuel.h"
#include "KCC_Joysticks.h"
#include "KCC_SAS.h"

Telemetry telemetry;
CommandData commandData;

void setup() {

  initializeComponents();

  SER.handshake();

}

void loop() {

  if (SER.pullTelemetry(&telemetry)) {
    LCD.update();
    // _FUEL.update(&telemetry);
  }

  // CTRL.read();
  // SER.pushCommands(&commandData);

  if (SAS.update())
    Serial.println((short) SAS.get());

  delay(1);

}
