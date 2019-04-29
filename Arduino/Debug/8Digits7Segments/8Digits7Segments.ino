#include <SPI.h>

#define LED_1_PIN 6
#define LED_1_BIT 3

#define LED_2_PIN 7
#define LED_2_BIT 4

SPISettings settings(100000000, MSBFIRST, SPI_MODE0);

void maxTransfer(uint8_t device, uint8_t address, uint8_t value) {

  SPI.beginTransaction(settings);

  PORTH &= ~(1 << (device == 1 ? LED_1_BIT : LED_2_BIT)); // digitalWrite(LOAD_PIN, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  PORTH |=  (1 << (device == 1 ? LED_1_BIT : LED_2_BIT)); // digitalWrite(LOAD_PIN, HIGH);

  SPI.endTransaction();

}

void setup() {

  delay(1000);

  // Set load pin to output
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);

  SPI.begin();

  // Run test
  // All LED segments should light up
  //  maxTransfer(0x0F, 0x01);
  //  delay(1000);
  //  maxTransfer(0x0F, 0x00);

  // Enable decode mode
  maxTransfer(1, 0x09, 0xFF);
  maxTransfer(2, 0x09, 0xFF);

  // Use lowest intensity
  maxTransfer(1, 0x0A, 0x00);
  maxTransfer(2, 0x0A, 0x00);

  // Scan all digits
  maxTransfer(1, 0x0B, 0x07);
  maxTransfer(2, 0x0B, 0x07);

  // Reset
  for (int i = 1; i <= 8; i++) {
    maxTransfer(1, i, 0x0F);
    maxTransfer(2, i, 0x0F);
  }

  // Turn on chip
  maxTransfer(1, 0x0C, 0x01);
  maxTransfer(2, 0x0C, 0x01);

}

int start = 0;
void loop() {

  doDevice(1);
  doDevice(2);

  delay(100);

}

void doDevice(uint8_t device) {

  long val = start++;

  long absVal = abs(val);
  bool neg = val < 0;

  if (absVal > 999999)
    maxTransfer(device, 0x01, 0x0A);
  else {

    int digits = howMany(absVal);

    int i = 1;
    for (; i <= digits; i++) {
      byte x = absVal % 10;
      maxTransfer(device, i, x);
      absVal /= 10;
    }
    if (neg)
      maxTransfer(device, i, 0x0A);

  }

}

int howMany(long x)  {
  return (x < 10 ? 1 :
          (x < 100 ? 2 :
           (x < 1000 ? 3 :
            (x < 10000 ? 4 :
             (x < 100000 ? 5 :
              (x < 1000000 ? 6 :
               (x < 10000000 ? 7 :
                8 )))))));
}
