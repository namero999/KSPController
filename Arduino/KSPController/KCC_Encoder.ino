KCC_Encoder::KCC_Encoder(uint8_t dataPin, uint8_t clockPin, uint8_t resetPin) {

  this->dataPin  = dataPin;
  this->clockPin = clockPin;
  this->resetPin = resetPin;

  pinMode(dataPin,  INPUT);
  pinMode(clockPin, INPUT);
  pinMode(resetPin, INPUT_PULLUP);

}

void KCC_Encoder::attachInterrupts(void (*dataFall), void (*clockFall)) {
  attachInterrupt(dataPin,  dataFall,  FALLING);
  attachInterrupt(clockPin, clockFall, FALLING);
}
