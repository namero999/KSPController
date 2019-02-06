int pwmOut = 4;

void setup() {
  Serial.begin(57600);
  pinMode(pwmOut, OUTPUT);
  pinMode(46, OUTPUT);
}

int h = 10;

void loop() {
//    rotating();
  fix();
}

void rotating() {
  //  while (!Serial.available()) {}
  //  Serial.read();
  if (h < 0)
    h = 10;
  int val = map(h, 0, 10, 20, 255);
  Serial.println(val);
  analogWrite(pwmOut, val);
  delay(1000);
  h--;
}

void fix() {
  int val = map(h, 0, 10, 10, 255);
  Serial.println(val);
  analogWrite(pwmOut, val);
  delay(1000);
}
