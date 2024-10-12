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

    npm1300.led_set_mode(nPM1300::LED::LED0, nPM1300::LEDMode::CHARGING);
    npm1300.led_set_mode(nPM1300::LED::LED1, nPM1300::LEDMode::ERROR);
    npm1300.led_set_mode(nPM1300::LED::LED2, nPM1300::LEDMode::HOST);

    npm1300.set_vterm(nPM1300::V4_15);
    npm1300.set_vterm_warm(nPM1300::V4_10);

    npm1300.charger_on();

}

void loop() {
    //npm1300.led_toggle(nPM1300::LED::LED0);
    //npm1300.led_toggle(nPM1300::LED::LED1);
    npm1300.led_toggle(nPM1300::LED::LED2);

    Serial.print("TEMP: ");
    Serial.println(npm1300.measure_temperature());
    Serial.print("VBAT: ");
    Serial.println(npm1300.measure_vbat());
    Serial.print("VSYS: ");
    Serial.println(npm1300.measure_vsys());
    Serial.print("VBUS: ");
    Serial.println(npm1300.measure_vbus());
    Serial.print("VTERM: ");
    Serial.println(npm1300.get_vterm());
    Serial.print("VTERM WARM: ");
    Serial.println(npm1300.get_vterm_warm());
    Serial.print("CHARGER STATUS: ");
    Serial.println(npm1300.get_charge_status(), BIN);
    Serial.print("ERROR REASON: ");
    Serial.println(npm1300.get_error_reason(), BIN);
    Serial.print("ERROR EXTRA: ");
    Serial.println(npm1300.get_error_extra(), BIN);
    Serial.println("");

    delay(1000);
}

#endif
