KCC_Joysticks::KCC_Joysticks(uint8_t xPin, uint8_t yPin, uint8_t zPin) {
  this->xPin = xPin;
  this->yPin = yPin;
  this->zPin = zPin;
}

void KCC_Joysticks::read() {

  commandData.attX = adjust(analogRead(xPin));
  commandData.attY = adjust(analogRead(yPin));
  commandData.attZ = adjust(analogRead(zPin));

}

int KCC_Joysticks::adjust(int val) {
  val = map(val, 5, 1020, -SCALE, SCALE);
  return val > DEADZONE || val < -DEADZONE ? val : 0;
}
