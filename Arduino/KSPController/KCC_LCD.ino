KCC_LCD::KCC_LCD(uint8_t modeSwitchPin1, uint8_t modeSwitchPin2) : _lcd(0x27, 20, 4)  {

  this->modeSwitchPin1 = modeSwitchPin1;
  this->modeSwitchPin2 = modeSwitchPin2;

  pinMode(modeSwitchPin1, INPUT_PULLUP);
  pinMode(modeSwitchPin2, INPUT_PULLUP);

  _lcd.init();
  _lcd.backlight();

  //  splash();

  _lcd.clear();

}

DisplayMode KCC_LCD::readModeSwitch() {
  bool sw1 = digitalRead(modeSwitchPin1);
  bool sw2 = digitalRead(modeSwitchPin2);
  return sw1 && sw2 ? ORBITAL : sw2 ? SURFACE : TARGET;
}

// char line[8];

void KCC_LCD::update() {

  DisplayMode mode = readModeSwitch();
  bool change = currentMode != mode;

  if (change) {
    _lcd.clear();
    currentMode = mode;
    LCD->print(13, 0, mode == ORBITAL ? F("ORBITAL") : mode == SURFACE ? F("SURFACE") : F(" TARGET"));
  }

  if (currentMode == ORBITAL) {

    if (change) {
      LCD->print(0, 0, telemetry.vessel);
      LCD->print(0, 1, "AP: ");
      LCD->print(0, 2, "PE: ");
      LCD->print(0, 3, "IN: ");
    }

    // dtostrf(gameData.ap, 7, 2, line);
    LCD->print(4, 1, telemetry.ap);

    // dtostrf(gameData.pe, 7, 2, line);
    LCD->print(4, 2, telemetry.pe);

    // dtostrf(gameData.in, 7, 2, line);
    LCD->print(4, 3, telemetry.in);

  }

  else if (currentMode == SURFACE) {

    if (change) {
      LCD->print(0, 0, telemetry.body);
      LCD->print(0, 1, "AL: ");
      LCD->print(0, 2, "VS: ");
      LCD->print(0, 3, "HS: ");
    }

    // dtostrf(gameData.alt, 7, 2, line);
    LCD->print(4, 1, telemetry.alt);

    // dtostrf(gameData.vS, 7, 2, line);
    LCD->print(4, 2, telemetry.vS);

    // dtostrf(gameData.hS, 7, 2, line);
    LCD->print(4, 3, telemetry.hS);

  }

  else if (currentMode == TARGET) {

    if (change)
      LCD->print(0, 0, TARGET);

  }

}

void KCC_LCD::splash() {

  byte half[8]  = { 0x1F, 0x1F, 0x1F, 0x1F, 0x0, 0x0, 0x0, 0x0 };
  _lcd.createChar(1, half);

  byte lines[4][20] = {
    { 0x20, 0x20,   0xFF, 0x20, 0xFF,   0x20, 0x20, 0x20,   0xFF, 0xFF, 0xFF, 0xFF,   0x20, 0x20, 0x20,   0xFF, 0xFF, 0xFF,   0x20, 0x20 },
    { 0x20, 0x20,   0xFF, 0xFF, 0x20,   0x20, 0x20, 0x20,   0x01, 0x01, 0x01, 0xFF,   0x20, 0x20, 0x20,   0xFF, 0xFF, 0xFF,   0x20, 0x20 }, // Line 2 and 3 are flipped (?)
    { 0x20, 0x20,   0xFF, 0x20, 0xFF,   0x20, 0x20, 0x20,   0xFF, 0x20, 0x20, 0x20,   0x20, 0x20, 0x20,   0xFF, 0x20, 0xFF,   0x20, 0x20 },
    { 0x20, 0x20,   0xFF, 0x20, 0xFF,   0x20, 0x20, 0x20,   0xFF, 0xFF, 0xFF, 0xFF,   0x20, 0x20, 0x20,   0xFF, 0x20, 0x20,   0x20, 0x20 }
  };

  _lcd.home();

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 20; j++)
      _lcd.write(lines[i][j]);

  delay(1000);

}

void KCC_LCD::clear() {
  _lcd.clear();
}

template <typename T> void KCC_LCD::print(uint8_t x, uint8_t y, T w) {
  _lcd.setCursor(x, y);
  _lcd.print(w);
}
