void KCC_SASEncoder::setup() {

  attachInterrupt(PIN_ENCODER_DATA, SAS_DATA_RISE, RISING);
  attachInterrupt(PIN_ENCODER_CLOCK, SAS_CLOCK_RISE, RISING);

}

void SAS_DATA_RISE() {
}

void SAS_DATA_FALL() {
}

void SAS_CLOCK_RISE() {
}

void SAS_CLOCK_FALL() {
}

SASMode KCC_SASEncoder::query() {
  return state;
}
