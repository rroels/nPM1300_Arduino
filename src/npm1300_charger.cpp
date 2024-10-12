#include <Wire.h>
#include "npm1300.h"

void nPM1300::charger_on() {
    // make it ignore NTC (there is none connected)
    write_register(BCHGDISABLESET, 0b00000010);

    // enable charger
    write_register(BCHGENABLESET, 0b00000001);
}

void nPM1300::charger_off() {
    write_register(BCHGENABLECLR, 0b00000001);
}

uint8_t nPM1300::get_vterm() {
    return read_register(BCHGVTERM);
}

void nPM1300::set_vterm(VTERM vterm) {
    write_register(BCHGVTERM, vterm);
}

uint8_t nPM1300::get_vterm_warm() {
    return read_register(BCHGVTERMR);
}

void nPM1300::set_vterm_warm(VTERM vterm) {
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