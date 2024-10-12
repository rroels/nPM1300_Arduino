
#include <Arduino.h>
#include <Wire.h>

// can be overridden externally if needed
uint8_t i2c_helper_address = 0x6B;
TwoWire& i2c_helper_wire = Wire;

uint8_t i2c_read_byte(uint16_t reg_address)
{
    uint8_t result = 0;

    // set register address
    i2c_helper_wire.beginTransmission(i2c_helper_address);
    i2c_helper_wire.write(highByte(reg_address));
    i2c_helper_wire.write(lowByte(reg_address));
    i2c_helper_wire.endTransmission(false);

    // request and read 1 byte
    i2c_helper_wire.requestFrom(i2c_helper_address, (uint8_t) 1);
    result = i2c_helper_wire.read();

    return result;
}

void i2c_write_byte(uint16_t reg_address, uint8_t data)
{
    i2c_helper_wire.beginTransmission(i2c_helper_address);
    i2c_helper_wire.write(highByte(reg_address));
    i2c_helper_wire.write(lowByte(reg_address));
    i2c_helper_wire.write(data);
    i2c_helper_wire.endTransmission();
}



