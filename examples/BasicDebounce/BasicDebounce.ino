#include <dBounce.h>

const uint8_t buttonPins[] = {2, 3, 4};
dBounce<sizeof(buttonPins)> debouncer(buttonPins, 1000); // 1ms polling

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("Debounce Library Example...");

}

void loop() {
  static uint8_t lastState[2] = {255, 255};

  debouncer.update();

  for (uint8_t i = 0; i < sizeof(buttonPins); ++i) {
    uint8_t state = debouncer.getState(i);

    if (state != lastState[i]) {
      lastState[i] = state;

      if (state == 0) {
        Serial.print("Button ");
        Serial.print(i);
        Serial.println(" is PRESSED and stable.");
      }
      else if (state == 1) {
        Serial.print("Button ");
        Serial.print(i);
        Serial.println(" is RELEASED and stable.");
      }
    }
  }
}

