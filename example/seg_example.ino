/*
Title:example of KYSevenSegment
Written By KYLiN

This is a code of example how to use KYSevenSegment

Date: 3/9/2022
*/

#include <KYSevenSegment.h>

// init KYSevenSegment 
KYSevenSegment seg(13, 12, 6, 5, 4, 11, 10, 7, true);

const int outPin = 9;
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    pinMode(outPin, OUTPUT);
    digitalWrite(outPin, HIGH);
}

void loop() {

    // display Hex 
    seg.displayHex(B01110111);
    Serial.println("Display Hex: A");

    delay(2000);
    // display number with out dp  
    for (uint8_t i = 0; i < 10; i++) {
        seg.displayNumber(i);
        Serial.println("Function displayNumber :" + String(i));
        delay(1000);
    }

    // display number with dp 
    for (uint8_t i = 0; i < 10; i++) {
        seg.displayNumber(i, true);
        Serial.println("Function displayNumber(dp) :" + String(i));
        delay(1000);
    }

    // clear display function 
    seg.clearDisplay();
    delay(1000);

    // control dp function 
    seg.onlyControlDP(true);
    delay(1000);

}
