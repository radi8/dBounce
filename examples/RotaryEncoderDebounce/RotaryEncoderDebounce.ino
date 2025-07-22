/*
  RotaryEncoderDebounce.ino
  Demonstrates debounced input handling for rotary encoders and push buttons
  using the Debounce library.

  Adapted from code by Graeme Jury ZL2TE, 28 Sep 2022
*/

#include <dBounce.h>

const uint8_t buttons[] = {13, 14, 15, 16, 17, 18}; // Enc1_PB, Enc1_DT, Enc1_CLK, Enc2_PB, Enc2_DT, Enc2_CLK
dBounce<sizeof(buttons)> Debouncer(buttons, 200); // 200 µs polling

enum ButtonIndex {
  Enc1_PB, Enc1_DT, Enc1_CLK,
  Enc2_PB, Enc2_DT, Enc2_CLK
};

uint8_t lastStates[sizeof(buttons)] = {1, 1, 1, 1, 1, 1}; // All released initially

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Rotary Encoder Debounce Example");
}

void loop() {
  Debouncer.update();

  // Enc1 Rotation Detection
  if ((Debouncer.getState(Enc1_CLK) <= 2) && lastStates[Enc1_CLK] != 0) {
    lastStates[Enc1_CLK] = 0;
    if (Debouncer.getState(Enc1_DT) <= 2) {
      Serial.println("Enc1: Anti-clockwise");
    } else {
      Serial.println("Enc1: Clockwise");
    }
    Debouncer.setTimer(2);
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (Debouncer.getState(Enc1_CLK) >= 1 && lastStates[Enc1_CLK] != 1) {
    lastStates[Enc1_CLK] = 1;
  }

  // Enc2 Rotation Detection
  if ((Debouncer.getState(Enc2_CLK) <= 2) && lastStates[Enc2_CLK] != 0) {
    lastStates[Enc2_CLK] = 0;
    if (Debouncer.getState(Enc2_DT) <= 2) {
      Serial.println("Enc2: Anti-clockwise");
    } else {
      Serial.println("Enc2: Clockwise");
    }
    Debouncer.setTimer(3);
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (Debouncer.getState(Enc2_CLK) >= 1 && lastStates[Enc2_CLK] != 1) {
    lastStates[Enc2_CLK] = 1;
  }

  // Pushbutton handling for Enc1
  if ((Debouncer.getState(Enc1_PB) <= 2) && lastStates[Enc1_PB] != 0) {
    lastStates[Enc1_PB] = 0;
    Debouncer.setTimer(0);
    Serial.println("Enc1 Button Pressed");
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (Debouncer.getState(Enc1_PB) >= 1 && lastStates[Enc1_PB] != 1) {
    lastStates[Enc1_PB] = 1;
    uint32_t duration = Debouncer.getTimer(0);
    Serial.print("Enc1 Button Released - ");
    Serial.println(duration > 1000000 ? "LONG press" : "SHORT press");
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Pushbutton handling for Enc2
  if ((Debouncer.getState(Enc2_PB) <= 2) && lastStates[Enc2_PB] != 0) {
    lastStates[Enc2_PB] = 0;
    Debouncer.setTimer(1);
    Serial.println("Enc2 Button Pressed");
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (Debouncer.getState(Enc2_PB) >= 1 && lastStates[Enc2_PB] != 1) {
    lastStates[Enc2_PB] = 1;
    uint32_t duration = Debouncer.getTimer(1);
    Serial.print("Enc2 Button Released - ");
    Serial.println(duration > 1000000 ? "LONG press" : "SHORT press");
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(10);
}
