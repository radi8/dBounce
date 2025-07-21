#ifndef DEBOUNCE_TPP
#define DEBOUNCE_TPP

template <size_t NumButtons>
Debounce<NumButtons>::Debounce(const uint8_t (&pins)[NumButtons], uint16_t pollIntervalMicros)
    : pollInterval_(pollIntervalMicros) {
    for (size_t i = 0; i < NumButtons; ++i) {
        pins_[i] = pins[i];
        pinMode(pins_[i], INPUT_PULLUP);
        bool pressed = digitalRead(pins_[i]) == LOW;
        state_[i] = mirror_[i] = pressed ? 0x0000 : 0xFFFF;
    }
}

template <size_t NumButtons>
void Debounce<NumButtons>::setPollInterval(uint16_t interval) {
    pollInterval_ = interval;
}

template <size_t NumButtons>
void Debounce<NumButtons>::setTimer(uint8_t slot) {
    if (slot < NumButtons)
        timers_[slot] = micros();
}

template <size_t NumButtons>
uint32_t Debounce<NumButtons>::getTimer(uint8_t slot) const {
    return (slot < NumButtons) ? micros() - timers_[slot] : 0;
}

template <size_t NumButtons>
void Debounce<NumButtons>::update() {
    if ((micros() - lastPollTime_) < pollInterval_)
        return;
    lastPollTime_ = micros();

    for (size_t i = 0; i < NumButtons; ++i) {
        uint8_t reading = digitalRead(pins_[i]);
        uint16_t old = state_[i];
        state_[i] = (state_[i] << 1) | reading;

        if (state_[i] != mirror_[i]) {
            if ((state_[i] & MASK) == PRESS_PATTERN) {
                state_[i] = 0xAAAA;
                mirror_[i] = 0x0000;
            } else if ((state_[i] & MASK) == RELEASE_PATTERN) {
                state_[i] = 0x5555;
                mirror_[i] = 0xFFFF;
            }

#ifdef DEBUG_BOUNCES
            debugDisplay(i, true);
#endif
        }
    }
}

template <size_t NumButtons>
uint8_t Debounce<NumButtons>::getState(uint8_t btnNum) const {
    if (btnNum >= NumButtons) return 0xFF;

    if ((state_[btnNum] == 0x0000 || state_[btnNum] == 0xFFFF) && state_[btnNum] == mirror_[btnNum]) {
        return (state_[btnNum] == 0x0000) ? 0 : 1;
    } else {
        return (mirror_[btnNum] == 0x0000) ? 3 : 2;
    }
}

#ifdef DEBUG_BOUNCES
template <size_t NumButtons>
void Debounce<NumButtons>::printBinary(uint16_t val, int bits) const {
    for (int i = bits - 1; i >= 0; --i) {
        Serial.print((val & (1 << i)) ? '1' : '0');
        if (i % 4 == 0 && i > 0) Serial.print('_');
    }
}

template <size_t NumButtons>
void Debounce<NumButtons>::debugDisplay(uint8_t index, bool changed) const {
    Serial.print(F("Btn#"));
    Serial.print(index);
    Serial.print(F(" State: "));
    printBinary(state_[index]);
    Serial.print(F(" | Mirror: "));
    printBinary(mirror_[index]);
    if (changed) Serial.println(F(" <- change"));
    else Serial.println();
}
#endif

#endif // DEBOUNCE_TPP