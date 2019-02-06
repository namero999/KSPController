KCC_SASEncoder _SAS;

void KCC_SASEncoder::setup() {
  attachInterrupt(PIN_SAS_DATA,  DATA_FALL,  FALLING);
  attachInterrupt(PIN_SAS_CLOCK, CLOCK_FALL, FALLING);
}

int  SAS_PULSE = 0;
bool SAS_DATA  = HIGH;
bool SAS_CLOCK = HIGH;

void CLOCK_FALL() {
  detachInterrupt(PIN_SAS_CLOCK);
  SAS_CLOCK = LOW;
  SAS_PULSE += SAS_DATA ? 1 : -1;
  attachInterrupt(PIN_SAS_CLOCK, CLOCK_RISE, RISING);
}

void DATA_FALL() {
  detachInterrupt(PIN_SAS_DATA);
  SAS_DATA = LOW;
  SAS_PULSE += SAS_CLOCK ? -1 : 1;
  attachInterrupt(PIN_SAS_DATA, DATA_RISE, RISING);
}

void CLOCK_RISE() {
  detachInterrupt(PIN_SAS_CLOCK);
  SAS_CLOCK = HIGH;
  SAS_PULSE += SAS_DATA ? -1 : 1;
  if (SAS_PULSE % 12 == 0)
    _SAS.prev();
  attachInterrupt(PIN_SAS_CLOCK, CLOCK_FALL, FALLING);
}

void DATA_RISE() {
  detachInterrupt(PIN_SAS_DATA);
  SAS_DATA = HIGH;
  SAS_PULSE += SAS_CLOCK ? 1 : -1;
  if (SAS_PULSE % 12 == 0)
    _SAS.next();
  attachInterrupt(PIN_SAS_DATA, DATA_FALL, FALLING);
}

void KCC_SASEncoder::next() {
  currentMode++;
  if (currentMode > 9)
    currentMode = 1;
}

void KCC_SASEncoder::prev() {
  currentMode--;
  if (currentMode < 1)
    currentMode = 9;
}
