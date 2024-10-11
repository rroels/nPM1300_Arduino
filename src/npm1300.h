#ifndef NPM1300_H
#define NPM1300_H

#include <I2C_device.h>
#include "i2c_device.h"

class nPM1300 : public I2C_Device
{
public:

    // constructors
    nPM1300( TwoWire& wire, const uint8_t i2c_address = 0 );

    enum Reg
    {
        // LEDDRV
        LEDDRV0MODESEL  = 0x0A00,
        LEDDRV1MODESEL  = 0x0A01,
        LEDDRV2MODESEL  = 0x0A02,
        LEDDRV0SET      = 0x0A03,
        LEDDRV0CLR      = 0x0A04,
        LEDDRV1SET      = 0x0A05,
        LEDDRV1CLR      = 0x0A06,
        LEDDRV2SET      = 0x0A07,
        LEDDRV2CLR      = 0x0A08
    };

    // -------------------------------

    enum LEDMode {
        ERROR,
        CHARGING,
        HOST,
        NOTUSED
    };

    enum LED {
        LED0,
        LED1,
        LED2
    };

    void led_toggle(LED led);
    void led_set_mode(LED led, LEDMode mode);
    void led_set_state(LED led, bool state);
    void led_on(LED led);
    void led_off(LED led);

private:
    bool led_state[3] = {false};

};

#endif //NPM1300_H
