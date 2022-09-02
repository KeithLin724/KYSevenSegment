#include "KYSevenSegment.h"

/**
 * @brief
 * is a library saving the display hex code
 */
const byte KYSevenSegment::_numberHex[] = {
        B0111111, // 0
        B0000110, // 1
        B1011011, // 2
        B1001111, // 3
        B1100110, // 4
        B1101101, // 5
        B1111101, // 6
        B0000111, // 7
        B1111111, // 8
        B1101111, // 9

        B0000000 // Clear Screen
};

void KYSevenSegment::__displayHex_inv(const byte& value, const bool& dp, const bool& dp_only = false) const {

    if (!dp_only) {
        for (uint8_t i(0); i < 8; i++) {
            digitalWrite(this->_pins[i], !bitRead(value, i));
        }
    }
    digitalWrite(this->_pins[7], !dp);
}

void KYSevenSegment::__displayHex(const byte& value, const bool& dp, const bool& dp_only = false) const {

    if (!dp_only) {
        for (uint8_t i(0); i < 8; i++) {
            digitalWrite(this->_pins[i], bitRead(value, i));
        }
    }
    digitalWrite(this->_pins[7], dp);
}

void KYSevenSegment::__initPins() const {
    bool setState = !this->_inv_mode;

    for (const auto& pin : this->_pins) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, setState);
    }

}

KYSevenSegment::KYSevenSegment(int a, int b, int c, int d, int e, int f, int g, int dp, bool inv_mode = false) {
    this->_pins[0] = a;
    this->_pins[1] = b;
    this->_pins[2] = c;
    this->_pins[3] = d;

    this->_pins[4] = e;
    this->_pins[5] = f;
    this->_pins[6] = g;
    this->_pins[7] = dp;


    this->_inv_mode = inv_mode;

    this->__initPins();
}

KYSevenSegment::KYSevenSegment(uint16_t pins[8], bool inv_mode = false) {
    this->_inv_mode = inv_mode;

    for (uint16_t i = 0; i < 8; i++) {
        this->_pins[i] = pins[i];
    }

    this->__initPins();
}

KYSevenSegment::~KYSevenSegment() {
    this->_inv_mode = false;

    for (uint16_t i = 0; i < 8; i++) {
        this->_pins[i] = 0;
    }
}

/**
 * @brief Set the Inv Mode object
 * pins output need to inverse
 *
 * inv_mode = False pin and signal is same
 * inv_mode = True pin and signal is inverse
 * @param inv_mode about the inv_mode switch
 *
 */
void KYSevenSegment::setInvMode(const bool& inv_mode) {
    this->_inv_mode = inv_mode;

}

/**
 * @brief Set the Pins object
 *
 * @param pins about the pins array obj
 */
void KYSevenSegment::setPins(uint16_t pints[8]) {
    for (int i = 0; i < 8; i++) {
        this->_pins[i] = pints[i];
    }

}

/**
 * @brief Get the Mode object
 *
 * get about the segment mode setting state
 * @return true is in inv mode
 * @return false not in inv mode
 */
bool KYSevenSegment::getMode() const {
    return this->_inv_mode;
}

/**
 * @brief
 * Display the number
 * @param id Display the number using class library
 * @param dp About the dp state
 */
void KYSevenSegment::displayNumber(const uint16_t& id, const bool& dp = false) const {
    if (id >= 10) {
        return;
    }

    if (this->_inv_mode) {
        this->__displayHex_inv(KYSevenSegment::_numberHex[id], dp);
    }
    else {
        this->__displayHex(KYSevenSegment::_numberHex[id], dp);
    }

}

/**
 * @brief
 * Display using hex code
 * @param value Display hex code
 * @param dp About the dp state
 */
void KYSevenSegment::displayHex(const byte& value, const bool& dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(value, dp);
    }
    else {
        this->__displayHex(value, dp);
    }
}

/**
 * @brief
 * Only display the dp
 * @param dp About the dp state
 */
void KYSevenSegment::onlyControlDP(const bool& dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(0, dp, true);
    }
    else {
        this->__displayHex(0, dp, true);
    }
}

/**
 * @brief
 *
 * clear display function
 */
void KYSevenSegment::clearDisplay() const {
    if (this->_inv_mode) {
        this->__displayHex_inv(KYSevenSegment::_numberHex[10], 0);
    }
    else {
        this->__displayHex(KYSevenSegment::_numberHex[10], 0);
    }
}
