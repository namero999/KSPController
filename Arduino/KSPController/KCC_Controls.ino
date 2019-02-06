void KCC_Controls::read() {

  commandData.attX = adjust(analogRead(PIN_JOY_ATTITUDE_X));
  commandData.attY = adjust(analogRead(PIN_JOY_ATTITUDE_Y));

}

int KCC_Controls::adjust(int val) {
  val = map(val, 5, 1020, -SCALE, SCALE);
  return val > DEADZONE || val < -DEADZONE ? val : 0;
}
