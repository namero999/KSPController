void initPins() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(PIN_LCD_MODE_A, INPUT_PULLUP);
  pinMode(PIN_LCD_MODE_B, INPUT_PULLUP);

  pinMode(PIN_FUEL_SOLID,    OUTPUT);
  pinMode(PIN_FUEL_LIQUID,   OUTPUT);
  pinMode(PIN_FUEL_OXIDIZER, OUTPUT);
  pinMode(PIN_FUEL_MONOPROP, OUTPUT);
  pinMode(PIN_FUEL_ELECTRO,  OUTPUT);

}
