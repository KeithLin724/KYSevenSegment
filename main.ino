#include "KYSevenSegment.h"

KYSevenSegment seg(13, 12, 6, 5, 4, 11, 10, 7, true);

const int outPin = 9;
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    pinMode(outPin, OUTPUT);
    digitalWrite(outPin, HIGH);
}

void loop() {

    seg.displayHex(B01110111);
    Serial.println("Display Hex: A");

    delay(2000);
    for (uint8_t i = 0; i < 10; i++) {
        seg.displayNumber(i);
        Serial.println("Function displayNumber :" + String(i));
        delay(1000);
    }

    for (uint8_t i = 0; i < 10; i++) {
        seg.displayNumber(i, true);
        Serial.println("Function displayNumber(dp) :" + String(i));
        delay(1000);
    }

    seg.clearDisplay();
    delay(1000);

    seg.onlyControlDP(true);
    delay(1000);

}
