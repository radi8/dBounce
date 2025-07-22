#include <dBounce.h>

// Define button pins
const uint8_t buttonPins[] = {2, 3, 4};
dBounce<sizeof(buttonPins)> debouncer(buttonPins, 1000); // 1ms polling

void setup() {
  Serial.begin(9600);
  Serial.println("Debounce Library Example");
}

void loop() {
  debouncer.update();

  for (uint8_t i = 0; i < sizeof(buttonPins); ++i) {
    uint8_t state = debouncer.getState(i);

    if (state == 0) {
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" is PRESSED and stable.");
    } else if (state == 1) {
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" is RELEASED and stable.");
    }
  }

  delay(100); // Slow down serial output for readability
}
