KCC_LCD _LCD;

KCC_LCD::KCC_LCD() : _lcd(0x27, 20, 4)  {}

void KCC_LCD::setup() {

  _lcd.init();
  _lcd.backlight();

  // splash();

  _lcd.clear();

}

void KCC_LCD::clear() {
  _lcd.clear();
}

template <typename T> void KCC_LCD::print(uint8_t x, uint8_t y, T w) {
  _lcd.setCursor(x, y);
  _lcd.print(w);
}

DisplayMode KCC_LCD::getMode() {
  boolean a = digitalRead(PIN_LCD_MODE_A);
  boolean b = digitalRead(PIN_LCD_MODE_B);
  return a && b ? ORBITAL : b ? SURFACE : TARGET;
}

char line[8];

void KCC_LCD::update() {

  DisplayMode mode = getMode();
  boolean change = currentMode != mode;

  if (change) {
    _lcd.clear();
    currentMode = mode;
    _LCD.print(13, 0, mode == ORBITAL ? F("ORBITAL") : mode == SURFACE ? F("SURFACE") : F(" TARGET"));
  }

  if (currentMode == ORBITAL) {

    if (change) {
      _LCD.print(0, 0, telemetry.vessel);
      _LCD.print(0, 1, "AP: ");
      _LCD.print(0, 2, "PE: ");
      _LCD.print(0, 3, "IN: ");
    }

    //    dtostrf(gameData.ap, 7, 2, line);
    _LCD.print(4, 1, telemetry.ap);

    //    dtostrf(gameData.pe, 7, 2, line);
    _LCD.print(4, 2, telemetry.pe);

    //    dtostrf(gameData.in, 7, 2, line);
    _LCD.print(4, 3, telemetry.in);

  }

  else if (currentMode == SURFACE) {

    if (change) {
      _LCD.print(0, 0, telemetry.body);
      _LCD.print(0, 1, "AL: ");
      _LCD.print(0, 2, "VS: ");
      _LCD.print(0, 3, "HS: ");
    }

    //    dtostrf(gameData.alt, 7, 2, line);
    _LCD.print(4, 1, telemetry.alt);

    //    dtostrf(gameData.vS, 7, 2, line);
    _LCD.print(4, 2, telemetry.vS);

    //    dtostrf(gameData.hS, 7, 2, line);
    _LCD.print(4, 3, telemetry.hS);

  }

  else if (currentMode == TARGET) {

    if (change)
      _LCD.print(0, 0, TARGET);

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
