# 📘 Debounce Algorithm - Detailed Explanation

This document explains the theory and implementation details of the debounce strategy used in the `Debounce` library, originally developed by Graeme Jury (ZL2TE).

---

## 🧠 Overview

The library uses a **16-bit shift register** per button to track the history of its state (pressed = 0, released = 1). Polling happens at a configurable interval, and each new reading is shifted in:

```cpp
button_History = (button_History << 1) | digitalRead(buttonPin);
```

Stable press or release states are detected using bitwise masking and pattern comparison.

---

## 🧪 Example: Button Release

Assuming a pull-up configuration where pressed = 0 and released = 1.

### Button is held, then released:
```
00 0000000000000000   Quiescent pressed state
01 0000000000000001
02 0000000000000011
03 0000000000000111
04 0000000000001111
05 0000000000011111   <-- MATCH: RELEASE detected here
06 0000000000111111
07 0000000001111111
08 0000000011111111
...
15 0111111111111111
16 1111111111111111   Fully released (stable)
```

### Detection Logic:

```cpp
MASK            = 0b1100000000011111
RELEASE_PATTERN = 0b0000000000011111

if ((history & MASK) == RELEASE_PATTERN) {
    history = 0x5555;  // force cooldown period
}
```

---

## 🧪 Example: Button Press with Bounce

### A bouncy button press causes noise:

```
10 1111111111111110
11 1111111111111100
12 1111111111111001   <- glitch
13 1111111111110011   <- glitch
14 1111111111100110
15 1111111111001101   <- glitch
16 1111111110011010
...
22 1111100110100000   <-- MATCH: PRESS detected here
```

### Masking logic:

```cpp
MASK          = 0b1100000000011111
PRESS_PATTERN = 0b1100000000000000

if ((history & MASK) == PRESS_PATTERN) {
    history = 0xAAAA;  // force cooldown period
}
```

This prevents multiple transitions from being registered during noise.

---

## 🧰 Real Example: Transition Debug Data

From a real button:

```
Raw Input             History State
------------------    ----------------------
0000000000000001      Start of release
...
0000000000011111      Matched RELEASE pattern
...
0101010101010101      Cooldown injected
```

From a Morse key:

```
Stable 0-to-1 stream from clean contacts
Processed in ~2ms with no false triggers
```

---

## 🛠 Implementation Summary

- **Shift register** holds recent state history
- **Mask** isolates significant bits
- **Pattern match** confirms stable transitions
- **Cooldown register** prevents premature re-triggering
- Designed to be **non-blocking**, **noise-resilient**, and **fast**

---

This debounce method is ideal for:
- Noisy mechanical switches
- Rotary encoders
- Morse keys
- Any real-time embedded system where input reliability matters

Developed and tested using real-world noisy hardware.