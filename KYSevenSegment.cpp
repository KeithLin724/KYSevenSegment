#include "KYSevenSegment.h"

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

//set 
void KYSevenSegment::setInvMode(const bool& inv_mode) {
    this->_inv_mode = inv_mode;

}
void KYSevenSegment::setPins(uint16_t pints[8]) {
    for (int i = 0; i < 8; i++) {
        this->_pins[i] = pints[i];
    }

}
// get
bool KYSevenSegment::getMode() const {
    return this->_inv_mode;
}
// function
void KYSevenSegment::displayNumber(const uint16_t& value, const bool& dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(KYSevenSegment::_numberHex[value], dp);
    }
    else {
        this->__displayHex(KYSevenSegment::_numberHex[value], dp);
    }

}
void KYSevenSegment::displayHex(const byte& value, const bool& dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(value, dp);
    }
    else {
        this->__displayHex(value, dp);
    }
}

void KYSevenSegment::only_display_dp(const bool& dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(0, dp, true);
    }
    else {
        this->__displayHex(0, dp, true);
    }
}

