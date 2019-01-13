#include "KCCEncoder4SAS.h"

void KCCEncoder4SAS::setup() {

  setupInterrupts();

}

void KCCEncoder4SAS::setupInterrupts() {
  attachInterrupt(ENCODER_DATA_PIN, DATA_RISE, RISING);
  attachInterrupt(ENCODER_CLICK_PIN, CLOCK_RISE, RISING);
}

SASMode KCCEncoder4SAS::query() {
  return this->state;
}

void DATA_RISE() {
}

void DATA_FALL() {
}

void CLOCK_RISE() {
}

void CLOCK_FALL() {
}
