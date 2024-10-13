#include <Wire.h>
#include "npm1300.h"

uint8_t nPM1300::get_vbus_status() {
    return read_register(VBUSINSTATUS);
}

