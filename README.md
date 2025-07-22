# dBounce – Non-blocking Debounce Library for Arduino

- [Detailed Technical Explanation (Wiki)](https://github.com/radi8/dBounce/wiki)
- `DETAILED_DOC.md` also included in the repo

**dBounce** is a non-blocking, highly noise-resistant debounce library for Arduino-compatible devices.  
It handles very noisy mechanical switches and rotary encoders using a shift-register-based state tracker,  
allowing stable press/release detection without delays or interrupts.

## 🚀 Features

- Non-blocking design using `micros()`-based timing
- Handles continuous and extreme bounce without misfires
- Suitable for:
  - Pushbuttons
  - Rotary encoders
  - Morse keys
- Fully non-blocking (no `delay()` or interrupts)
- Supports rotary encoders with direction detection
- Simple polling model with `update()` and `getBtnState()`
- Built-in timing utility for press duration detection
- Detects short and long presses
- Configurable polling interval
- Supports multiple buttons

## 🚀 Installation

1. Download or clone the repository
2. Place the `DebounceLib/` folder inside your Arduino `libraries/` directory
3. Restart the Arduino IDE

To install manually via zip:
- Download from the [Releases](https://github.com/radi8/dBounce/releases)
- In Arduino IDE: `Sketch > Include Library > Add .ZIP Library...`

---

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




