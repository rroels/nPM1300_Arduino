#include <Wire.h>
#include "npm1300.h"

void nPM1300::charger_on() {
    // make it ignore NTC (there is none connected)
    write_register(BCHGDISABLESET, 0b00000010);

    // enable charger
    write_register(BCHGENABLESET, 0b00000001);
}

void nPM1300::ignore_ntc(bool ignore) {
    if (ignore) {
        // charging will ignore the NTC thermistor resistor measure
        write_register(BCHGDISABLESET, 0b00000010);
    } else {
        // charging will use the NTC thermistor resistor measure
        write_register(BCHGDISABLECLR, 0b00000010);
    }
}

void nPM1300::set_recharge(bool enabled) {
    if (enabled) {
        // enable Recharging of battery once charged
        write_register(BCHGDISABLECLR, 0b00000001);
    } else {
        // disable Recharging of battery once charged
        write_register(BCHGDISABLESET, 0b00000001);
    }
}


void nPM1300::charger_off() {
    write_register(BCHGENABLECLR, 0b00000001);
}

uint8_t nPM1300::get_vterm() {
    return read_register(BCHGVTERM);
}

void nPM1300::set_vterm(VTERM vterm) {
    // set voltage at which to stop charging
    write_register(BCHGVTERM, vterm);
    // set voltage at which to stop charging when the die temp is "warm"
    write_register(BCHGVTERMR, vterm);
}

uint8_t nPM1300::get_charge_status() {
    return read_register(BCHGCHARGESTATUS);
}

uint8_t nPM1300::get_error_reason() {
    return read_register(BCHGERRREASON);
}

uint8_t nPM1300::get_error_extra() {
    return read_register(BCHGERRSENSOR);
}

void nPM1300::set_charge_current(uint16_t limit) {
    // make sure value is between 32 and 800
    if(limit < 32) { limit = 32; }
    if(limit > 800) { limit = 800; }

    uint8_t msb = limit/4;
    uint8_t lsb = 1;
    if ((limit/2) % 2) {
        lsb = 0;
    }

    write_register(BCHGISETMSB, msb);
    write_register(BCHGISETLSB, lsb);
}
