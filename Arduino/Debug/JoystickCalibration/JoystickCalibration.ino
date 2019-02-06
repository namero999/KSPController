void setup() {
  pinMode(52, INPUT_PULLUP);
  Serial.begin(57600);
}

int scale = 100;
int deadzone = 5;

void loop() {

  boolean button = !digitalRead(52);
  scale = button ? 10 : 100;
  deadzone = button ? 1 : 5;

  int x = analogRead(A10);
  int y = analogRead(A11);
  int z = analogRead(A12);

  int newX = adjust(x);
  int newY = adjust(y);
  int newZ = adjust(z);

  print(newX, newY, newZ, button);

  delay(500);

}

int adjust (int v) {
//  Serial.println(v);
  v = map(v, 5, 1020, -scale, scale);
  return v > deadzone || v < -deadzone ? v : 0;
}

void print(int x, int y, int z, boolean button) {
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(z);
  Serial.println(button ? " Click" : "");
}
