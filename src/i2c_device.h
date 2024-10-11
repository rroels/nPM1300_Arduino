
#ifndef I2C_HELPER_H
#define I2C_HELPER_H

#include <Arduino.h>
#include "Wire.h"

class I2C_Device {
public:
    I2C_Device(TwoWire& i2c, uint8_t i2c_address = 0x6B);
    void write_register(uint16_t address, uint8_t data);
    uint8_t read_register(uint16_t address);
private:
    TwoWire& i2c;
    uint8_t i2c_address;
};

#endif //I2C_HELPER_H
