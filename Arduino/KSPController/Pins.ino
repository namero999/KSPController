void initPins() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(PIN_ENCODER_CLOCK, INPUT);

  pinMode(PIN_DISPLAY_MODE_A, INPUT_PULLUP);
  pinMode(PIN_DISPLAY_MODE_B, INPUT_PULLUP);

}
