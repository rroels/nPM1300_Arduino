
#include "i2c_device.h"
#include "Wire.h"

I2C_Device::I2C_Device(TwoWire& i2c, uint8_t i2c_address) : i2c(i2c), i2c_address(i2c_address)
{
}

uint8_t I2C_Device::read_bytes(uint16_t address, char* buffer, uint8_t count)
{
    // set register address
    i2c.beginTransmission(i2c_address);
    i2c.write(highByte(address));
    i2c.write(lowByte(address));
    i2c.endTransmission(false);

    // request bytes
    i2c.requestFrom(i2c_address, count);

    // retrieve bytes
    uint8_t write_index = 0;
    while(Wire.available() && write_index < count)
    {
        buffer[write_index] = Wire.read();
        write_index++;
    }

    return write_index;
}

uint8_t I2C_Device::read_register(uint16_t address)
{
    uint8_t result = 0;

    // set register address
    i2c.beginTransmission(i2c_address);
    i2c.write(highByte(address));
    i2c.write(lowByte(address));
    i2c.endTransmission(false);

    // request and read 1 byte
    i2c.requestFrom(i2c_address, (uint8_t) 1);
    result = i2c.read();

    return result;
}

void I2C_Device::write_register(uint16_t reg_address, uint8_t data)
{
    i2c.beginTransmission(i2c_address);
    i2c.write(highByte(reg_address));
    i2c.write(lowByte(reg_address));
    i2c.write(data);
    i2c.endTransmission();
}