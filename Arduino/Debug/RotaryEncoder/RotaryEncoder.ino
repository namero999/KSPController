
int pulses, A_SIG = 0, B_SIG = 1;

void setup() {
  attachInterrupt(0, A_RISE, RISING);
  attachInterrupt(1, B_RISE, RISING);
  pinMode(22, INPUT_PULLUP);
  Serial.begin(115200);
}//setup

uint8_t state = HIGH;

void loop() {
  if (digitalRead(22) != state) {
    state = state == HIGH ? LOW : HIGH;
    if (state == LOW)
      Serial.println("Click");
  }
  delay(5);
}

void A_RISE() {
  detachInterrupt(0);
  A_SIG = 1;

  if (B_SIG == 0)
    pulses++;//moving forward
  if (B_SIG == 1)
    pulses--;//moving reverse
  if (pulses % 4 == 0)
    Serial.println("CCW");
  attachInterrupt(0, A_FALL, FALLING);
}

void A_FALL() {
  detachInterrupt(0);
  A_SIG = 0;

  if (B_SIG == 1)
    pulses++;//moving forward
  if (B_SIG == 0)
    pulses--;//moving reverse
  attachInterrupt(0, A_RISE, RISING);
}

void B_RISE() {
  detachInterrupt(1);
  B_SIG = 1;

  if (A_SIG == 1)
    pulses++;//moving forward
  if (A_SIG == 0)
    pulses--;//moving reverse
  if (pulses % 4 == 0)
    Serial.println("CW");
  attachInterrupt(1, B_FALL, FALLING);
}

void B_FALL() {
  detachInterrupt(1);
  B_SIG = 0;

  if (A_SIG == 0)
    pulses++;//moving forward
  if (A_SIG == 1)
    pulses--;//moving reverse
  attachInterrupt(1, B_RISE, RISING);
}
