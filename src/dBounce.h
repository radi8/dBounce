#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <Arduino.h>

//#define DEBUG_BOUNCES

template <size_t NumButtons>
class Debounce {
public:
    Debounce(const uint8_t (&pins)[NumButtons], uint16_t pollIntervalMicros = 1000);

    void update();
    uint8_t getState(uint8_t btnNum) const;

    void setPollInterval(uint16_t interval);
    void setTimer(uint8_t slot);
    uint32_t getTimer(uint8_t slot) const;

private:
    static constexpr uint16_t MASK = 0b1100000000011111;
    static constexpr uint16_t PRESS_PATTERN   = 0b1100000000000000;
    static constexpr uint16_t RELEASE_PATTERN = 0b0000000000011111;

    uint8_t pins_[NumButtons];
    uint16_t state_[NumButtons];   // history shift register
    uint16_t mirror_[NumButtons];  // shadow for previous state
    uint32_t timers_[NumButtons]{};
    uint16_t pollInterval_;
    uint32_t lastPollTime_ = 0;

#ifdef DEBUG_BOUNCES
    void printBinary(uint16_t val, int bits = 16) const;
    void debugDisplay(uint8_t index, bool changed) const;
#endif
};

#include "Debounce.tpp"

#endif // DEBOUNCE_H