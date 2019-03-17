KCC_SAS::KCC_SAS(uint8_t ledPin, uint8_t togglePin, uint8_t dataPin, uint8_t clockPin, uint8_t resetPin)
  : KCC_LedSwitch5(ledPin, togglePin)
  , KCC_Encoder(dataPin, clockPin, resetPin) {

//  attachInterrupts(DATA_FALL, CLOCK_FALL);

}

bool SAS_DATA  = HIGH;
bool SAS_CLOCK = HIGH;
int  SAS_PULSE = 0;

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
    SAS->prev();
  attachInterrupt(PIN_SAS_CLOCK, CLOCK_FALL, FALLING);
}

void DATA_RISE() {
  detachInterrupt(PIN_SAS_DATA);
  SAS_DATA = HIGH;
  SAS_PULSE += SAS_CLOCK ? 1 : -1;
  if (SAS_PULSE % 12 == 0)
    SAS->next();
  attachInterrupt(PIN_SAS_DATA, DATA_FALL, FALLING);
}

bool KCC_SAS::update() {

  if (KCC_LedSwitch5::update()) {
    if (isOn()) {
      currentMode = lastMode;
      attachInterrupts(DATA_FALL, CLOCK_FALL);
    } else {
      currentMode = OFF;
      detachInterrupt(PIN_SAS_DATA);
      detachInterrupt(PIN_SAS_CLOCK);
    }
    return true;
  }

  if (isOn() && lastMode != currentMode) {
    lastMode = currentMode;
    return true;
  }

  return false;

}

void KCC_SAS::next() {
  currentMode++;
  if (currentMode > ANTITARGET)
    currentMode = AUTO;
}

void KCC_SAS::prev() {
  currentMode--;
  if (currentMode < AUTO)
    currentMode = ANTITARGET;
}
