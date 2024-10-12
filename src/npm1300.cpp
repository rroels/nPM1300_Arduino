#include <Wire.h>
#include <I2C_device.h>
#include "npm1300.h"

nPM1300::nPM1300( TwoWire& wire, uint8_t i2c_address ) : I2C_Device( wire, i2c_address ) { }

void nPM1300::reset() {
    write_register(TASKSWRESET, 0b00000001);
}
