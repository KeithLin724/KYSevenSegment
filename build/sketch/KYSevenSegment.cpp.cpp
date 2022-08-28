#include <Arduino.h>
#line 2 "d:\\Arduino\\Library\\KYSevenSegment\\main.ino"
void setup();
#line 7 "d:\\Arduino\\Library\\KYSevenSegment\\main.ino"
void loop();
#line 0 "d:\\Arduino\\Library\\KYSevenSegment\\main.ino"
#line 1 "d:\\Arduino\\Library\\KYSevenSegment\\KYSevenSegment.cpp"
#include "KYSevenSegment.h"

void KYSevenSegment::__displayHex_inv(byte value, bool dp, bool dp_only) const {

    if (!dp_only) {
        for (uint8_t i = 0; i < 8; i++) {
            digitalWrite(this->_pins[i], !bitRead(value, i));
        }
    }
    digitalWrite(this->_pins[7], !dp);
}

void KYSevenSegment::__displayHex(byte value, bool dp, bool dp_only) const {

    if (!dp_only) {
        for (uint8_t i = 0; i < 8; i++) {
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

KYSevenSegment::KYSevenSegment(int a, int b, int c, int d, int e, int f, int g, int dp, bool mode = false) {
    this->_pins[0] = a;
    this->_pins[1] = b;
    this->_pins[2] = c;
    this->_pins[3] = d;

    this->_pins[4] = e;
    this->_pins[5] = f;
    this->_pins[6] = g;
    this->_pins[7] = dp;


    this->_inv_mode = mode;

    this->__initPins();
}

KYSevenSegment::KYSevenSegment(uint16_t pins[8], bool mode = false) {
    this->_inv_mode = mode;
    uint16_t index = 8;
    for (uint16_t i = 0; i < index; i++) {
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
void KYSevenSegment::setInvMode(bool mode) {
    this->_inv_mode = mode;

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
void KYSevenSegment::displayNumber(uint16_t value, bool dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(KYSevenSegment::_numberHex[value], dp);
    }
    else {
        this->__displayHex(KYSevenSegment::_numberHex[value], dp);
    }

}
void KYSevenSegment::displayHex(byte value, bool dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(value, dp);
    }
    else {
        this->__displayHex(value, dp);
    }
}

void KYSevenSegment::only_display_dp(bool dp = false) const {
    if (this->_inv_mode) {
        this->__displayHex_inv(0, dp, true);
    }
    else {
        this->__displayHex(0, dp, true);
    }
}


#line 1 "d:\\Arduino\\Library\\KYSevenSegment\\main.ino"

void setup()
{

}

void loop()
{

}

