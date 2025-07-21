
🧼 Debounce Logic Overview

This library provides a non-blocking, high-reliability debounce algorithm for handling mechanical switches and rotary encoders. It is designed to tolerate very noisy contacts without using delays or interrupts, making it ideal for real-time applications like Morse keyers or rotary encoder input.
🧠 How It Works

    Each button’s state is tracked using a 16-bit shift register updated on a timed polling interval (e.g., every 200 µs).

    Raw reads from the button are shifted in (0 for pressed, 1 for released).

    A bitmask (0xC01F) is applied to the history to detect stable transitions:

        0b1100000000000000 → valid press pattern

        0b0000000000011111 → valid release pattern

🛡️ Noise Suppression

    When a press or release is detected, the register is forcibly overwritten with alternating patterns:

        0xAAAA after a press (forces stability before another event can trigger)

        0x5555 after a release

    This approach ensures glitches and bounce-induced misreads are automatically rejected during the debounce window.

🔄 Rotary Encoder Support

    Encoders are read using transitions on the CLK line.

    The direction is inferred from the DT line’s value during a falling edge on CLK.

    This method ensures accurate detection even with low-cost mechanical encoders.

🚀 Features

    Fully non-blocking (uses micros() timing).

    Supports multiple buttons or encoder channels.

    Built-in press duration timer (for detecting long vs. short presses).

    Resilient to extreme contact bounce (e.g., over 20 ms).

    Easy to extend or customize.
