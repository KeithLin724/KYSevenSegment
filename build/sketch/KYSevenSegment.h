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
    void __displayHex_inv(byte value, bool dp, bool dp_only = false) const;
    void __displayHex(byte value, bool dp, bool dp_only = false) const;
    void __initPins() const;

public:
    KYSevenSegment(uint16_t pins[8], bool mode = false);

    KYSevenSegment(int a, int b, int c, int d, int e, int f, int g, int dp, bool mode = false);

    ~KYSevenSegment();

    //set 
    void setInvMode(bool mode);

    void setPins(uint16_t pins[8]);

    // get about the segment mode setting state 
    bool getMode() const;

    // function 

    // display the number 
    void displayNumber(uint16_t value, bool dp = false) const;

    /**
     * @brief
     * display using hex code
     * @param value display hex code
     * @param dp about the dp state
     */
    void displayHex(byte value, bool dp = false) const;

    /**
     * @brief
     * only display the dp
     * @param dp about the dp state
     */
    void only_display_dp(bool dp = false) const;

private: // member 
    uint16_t _pins[8];
    bool _inv_mode;

};


#endif