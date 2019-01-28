KCC_LCD _LCD;

KCC_LCD::KCC_LCD() : _lcd(0x27, 20, 4)  {}

void KCC_LCD::setup() {

  _lcd.init();
  _lcd.backlight();

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
  boolean a = digitalRead(PIN_DISPLAY_MODE_A);
  boolean b = digitalRead(PIN_DISPLAY_MODE_B);
  return a && b ? ORBITAL : b ? SURFACE : TARGET;
}

void KCC_LCD::update() {

  DisplayMode mode = getMode();

  _LCD.print(0, 0, mode);
  if (mode == TARGET)
    _LCD.print(2, 2, gameData.vessel);
  if (mode == ORBITAL)
    _LCD.print(10, 2, gameData.body);

  _LCD.print(2, 3, gameData.pe);
  _LCD.print(12, 3, gameData.hS);

}