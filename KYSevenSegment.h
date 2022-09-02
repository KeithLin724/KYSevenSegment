/*
Title:KYSevenSegment
Written By KYLiN
This is a seven segment lib for Arduino
easy to control seven segment display
Date: 28/8/2022
*/

#ifndef __KY_SEVEN_SEGMENT_H__
#define __KY_SEVEN_SEGMENT_H__

#include <Arduino.h>

class KYSevenSegment {
private:
    static const byte _numberHex[];

private: // function 
    void __displayHex_inv(const byte& value, const bool& dp, const bool& dp_only = false) const;
    void __displayHex(const byte& value, const bool& dp, const bool& dp_only = false) const;
    void __initPins() const;

public:
    KYSevenSegment(uint16_t pins[8], bool inv_mode = false);

    KYSevenSegment(int a, int b, int c, int d, int e, int f, int g, int dp, bool inv_mode = false);

    ~KYSevenSegment();

    //set

    void setInvMode(const bool& inv_mode);

    void setPins(uint16_t pins[8]);

    // get

    bool getMode() const;

    // function 

    void displayNumber(const uint16_t& id, const bool& dp = false) const;

    void displayHex(const byte& value, const bool& dp = false) const;

    void onlyControlDP(const bool& dp = false) const;

    void clearDisplay() const;

private: // member 
    uint16_t _pins[8];
    bool _inv_mode;

};


#endif