# dBounce – Non-blocking Debounce Library for Arduino

**dBounce** is a non-blocking, highly noise-resistant debounce library for Arduino-compatible devices.  
It handles very noisy mechanical switches and rotary encoders using a shift-register-based state tracker,  
allowing stable press/release detection without delays or interrupts.

## 🚀 Features

- Non-blocking design using `micros()`-based timing
- Tolerant to extreme switch bounce and glitches
- Suitable for:
  - Pushbuttons
  - Rotary encoders
  - Morse keys
- Detects short and long presses
- Configurable polling interval
- Supports multiple buttons

## 📦 Installation

### Option 1: Install via ZIP

1. [Download the ZIP](https://github.com/YOUR_USERNAME/dBounce/releases)
2. In Arduino IDE:  
   `Sketch > Include Library > Add .ZIP Library...`

### Option 2: Manual

Clone or extract to your `~/Arduino/libraries/dBounce/` directory.

## 📄 Example

```cpp
#include <Debounce.h>

const uint8_t buttonPins[] = {2, 3};
Debounce<sizeof(buttonPins)> debouncer(buttonPins);

void setup() {
  Serial.begin(9600);
}

void loop() {
  debouncer.update();
  if (debouncer.getState(0) == 0) {
    Serial.println("Button 0 pressed");
  }
}
```

## 📚 Documentation

- [Detailed Technical Explanation (Wiki)](https://github.com/radi8/dBounce/wiki)
- `DETAILED_DOC.md` also included in the repo

## 📜 License

MIT © Graeme Jury (ZL2TE)
