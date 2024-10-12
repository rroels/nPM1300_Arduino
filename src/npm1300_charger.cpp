#include <Wire.h>
#include "npm1300.h"

void nPM1300::charger_on() {
    write_register(BCHGDISABLESET, 0b00000010);
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