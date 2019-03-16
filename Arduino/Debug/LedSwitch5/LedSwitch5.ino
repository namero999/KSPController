#define LED_PIN 47
#define BTN_PIN 45

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
}

int led = LOW;
boolean wasDown = false;

void loop() {
  boolean isDown = digitalRead(BTN_PIN);
  if ((wasDown ^ isDown) && !isDown) {
    led = !led;
    digitalWrite(LED_PIN, led);
  }
  wasDown = isDown;
  delay(1);
}
