KCC_LedSwitch5::KCC_LedSwitch5(uint8_t ledPin, uint8_t togglePin) {

  this->ledPin    = ledPin;
  this->togglePin = togglePin;

  pinMode(ledPin,    OUTPUT);
  pinMode(togglePin, INPUT_PULLUP);

  digitalWrite(ledPin, LOW);

}

bool KCC_LedSwitch5::update() {
  bool isDown = digitalRead(togglePin), flip = false;
  if ((wasDown ^ isDown) && !isDown) {
    on = !on;
    digitalWrite(ledPin, on);
    flip = true;
  }
  wasDown = isDown;
  return flip;
}
