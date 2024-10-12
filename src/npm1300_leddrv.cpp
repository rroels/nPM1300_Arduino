#include <Wire.h>
#include "npm1300.h"

void nPM1300::led_toggle(LED led) {
    led_state[led] = !led_state[led];
    led_set_state(led, led_state[led]);
}

void nPM1300::led_set_mode(LED led, nPM1300::LEDMode mode) {
    static const uint16_t reg_addresses[3] = {LEDDRV0MODESEL,LEDDRV1MODESEL, LEDDRV2MODESEL};
    write_register(reg_addresses[led], mode);
    led_state[led] = mode;
}

void nPM1300::led_set_state(LED led, bool state) {
    if(state){
        led_on(led);
    }else{
        led_off(led);
    }
}

bool nPM1300::led_get_state(LED led) {
    return led_state[led];
}

void nPM1300::led_on(LED led) {
    static const uint16_t reg_addresses[3] = {LEDDRV0SET,LEDDRV1SET, LEDDRV2SET};
    write_register(reg_addresses[led], 0b00000001);
    led_state[led] = true;
}

void nPM1300::led_off(LED led) {
    static const uint16_t reg_addresses[3] = {LEDDRV0CLR,LEDDRV1CLR, LEDDRV2CLR};
    write_register(reg_addresses[led], 0b00000001);
    led_state[led] = false;
}
