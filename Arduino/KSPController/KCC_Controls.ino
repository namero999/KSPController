void KCC_Controls::read() {

  commandData.attX = adjust(analogRead(PIN_JOY_ATTITUDE_X));
  commandData.attY = adjust(analogRead(PIN_JOY_ATTITUDE_Y));

}

int KCC_Controls::adjust (int v) {
  v = map(v, 0, 1023, -SCALE, SCALE);
  return v > DEADZONE || v < -DEADZONE ? v : 0;
}
