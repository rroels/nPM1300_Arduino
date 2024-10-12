#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include <Wire.h>
#include "npm1300.h"

nPM1300 npm1300(Wire, 0x6B);

void setup() {

    Serial.begin(115200);
    Wire.begin();

    npm1300.reset();
    delay(100);

    npm1300.led_set_mode(nPM1300::LED::LED0, nPM1300::LEDMode::HOST);
    npm1300.led_set_mode(nPM1300::LED::LED1, nPM1300::LEDMode::HOST);
    npm1300.led_set_mode(nPM1300::LED::LED2, nPM1300::LEDMode::HOST);
}

void loop() {
    npm1300.led_toggle(nPM1300::LED::LED0);
    npm1300.led_toggle(nPM1300::LED::LED1);
    npm1300.led_toggle(nPM1300::LED::LED2);

    delay(1000);
}

#endif
