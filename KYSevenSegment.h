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
    static constexpr byte _numberHex[]{
        B0111111, // 0
        B0000110, // 1
        B1011011, // 2
        B1001111, // 3
        B1100110, // 4
        B1101101, // 5
        B1111101, // 6
        B0000111, // 7
        B1111111, // 8
        B1101111  // 9
    };

private: // function 
    void __displayHex_inv(const byte& value, const bool& dp, const bool& dp_only = false) const;
    void __displayHex(const byte& value, const bool& dp, const bool& dp_only = false) const;
    void __initPins() const;

public:
    KYSevenSegment(uint16_t pins[8], bool inv_mode = false);

    KYSevenSegment(int a, int b, int c, int d, int e, int f, int g, int dp, bool inv_mode = false);

    ~KYSevenSegment();

    //set

    /**
     * @brief Set the Inv Mode object
     * pins output need to inverse
     *
     * inv_mode = False pin and signal is same
     * inv_mode = True pin and signal is inverse
     * @param inv_mode about the inv_mode switch
     *
     */
    void setInvMode(const bool& inv_mode);


    /**
     * @brief Set the Pins object
     *
     * @param pins about the pins array obj
     */
    void setPins(uint16_t pins[8]);

    /**
     * @brief Get the Mode object
     *
     * get about the segment mode setting state
     * @return true is in inv mode
     * @return false not in inv mode
     */
    bool getMode() const;

    // function 

    /**
     * @brief
     * Display the number
     * @param value Display the number using class library
     * @param dp About the dp state
     */

    void displayNumber(const uint16_t& value, const bool& dp = false) const;

    /**
     * @brief
     * Display using hex code
     * @param value Display hex code
     * @param dp About the dp state
     */
    void displayHex(const byte& value, const bool& dp = false) const;

    /**
     * @brief
     * Only display the dp
     * @param dp About the dp state
     */
    void only_display_dp(const bool& dp = false) const;

private: // member 
    uint16_t _pins[8];
    bool _inv_mode;

};


#endif