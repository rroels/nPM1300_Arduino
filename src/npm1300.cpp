#include <Wire.h>
#include <I2C_device.h>
#include "npm1300.h"

nPM1300::nPM1300( TwoWire& wire, uint8_t i2c_address ) : I2C_Device( wire, i2c_address ) { }

void nPM1300::reset() {
    write_register(TASKSWRESET, 0b00000001);
}

// https://devzone.nordicsemi.com/f/nordic-q-a/107361/npm1300-unique-id-register?ReplyFilter=Answers&ReplySortBy=Answers&ReplySortOrder=Descending
char* nPM1300::get_manufacturing_info() {
    static char data[10] = {0};
    read_bytes(0x0C4C, data, 9);
    return (char*)&data;
}
