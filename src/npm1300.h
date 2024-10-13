#ifndef NPM1300_H
#define NPM1300_H

#include <I2C_device.h>
#include "i2c_device.h"

class nPM1300 : public I2C_Device
{
public:

    // -------------------------------
    // -------- CONSTRUCTOR ----------
    // -------------------------------

    nPM1300( TwoWire& wire, const uint8_t i2c_address = 0 );

    // -------------------------------
    // -------- REGISTERS ------------
    // -------------------------------

    enum Reg
    {
        // RESET
        TASKSWRESET     = 0x0001,

        // LEDDRV
        LEDDRV0MODESEL  = 0x0A00,
        LEDDRV1MODESEL  = 0x0A01,
        LEDDRV2MODESEL  = 0x0A02,
        LEDDRV0SET      = 0x0A03,
        LEDDRV0CLR      = 0x0A04,
        LEDDRV1SET      = 0x0A05,
        LEDDRV1CLR      = 0x0A06,
        LEDDRV2SET      = 0x0A07,
        LEDDRV2CLR      = 0x0A08,

        // MONITOR
        TASKVBATMEASURE     = 0x0500,
        TASKTEMPMEASURE     = 0x0502,
        TASKVSYSMEASURE     = 0x0503,
        TASKIBATMEASURE     = 0x0506,
        TASKVBUS7MEASURE    = 0x0507,
        ADCVBATRESULTMSB    = 0x0511,
        ADCTEMPRESULTMSB    = 0x0513,
        ADCVSYSRESULTMSB    = 0x0514,
        ADCGP0RESULTLSBS    = 0x0515,
        ADCVBAT2RESULTMSB   = 0x0518, // also holds ibat measurement result!
        ADCVBAT3RESULTMSB   = 0x0519, // also holds vbus measurement result!
        ADCGP1RESULTLSBS    = 0x051A,

        // CHARGER
        BCHGENABLESET       = 0x0304,
        BCHGENABLECLR       = 0x0305,
        BCHGDISABLESET      = 0x0306, // also used to disable thermistor use
        BCHGDISABLECLR      = 0x0307,
        BCHGISETMSB         = 0x0308,
        BCHGISETLSB         = 0x0309,
        BCHGVTERM           = 0x030C,
        BCHGVTERMR          = 0x030D,
        BCHGCHARGESTATUS    = 0x0334,
        BCHGERRREASON       = 0x0336,
        BCHGERRSENSOR       = 0x0337,

        // SYSREG
        VBUSSUSPEND         = 0x0203,
        USBCDETECTSTATUS    = 0x0205,
        VBUSINSTATUS        = 0x0207,

    };

    // -------------------------------
    // -------- GENERIC --------------
    // -------------------------------

    void reset();
    char* get_manufacturing_info();

    // -------------------------------
    // -------- LEDDRV ---------------
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
    bool led_get_state(LED led);
    void led_on(LED led);
    void led_off(LED led);

    // -------------------------------
    // -------- MONITOR --------------
    // -------------------------------

    float measure_vbat();
    float measure_vbus();
    float measure_vsys();
    float measure_temperature();

    // -------------------------------
    // -------- CHARGER --------------
    // -------------------------------

    enum VTERM {
        V3_50,
        V3_55,
        V3_60,
        V3_65,
        V4_00,
        V4_05,
        V4_10,
        V4_15,
        V4_20,
        V4_25,
        V4_30,
        V4_35,
        V4_40,
        V4_45,
        DEFAULT_1,
        DEFAULT_2,
    };

    void charger_on();
    void charger_off();
    void ignore_ntc(bool ignore);
    void set_recharge(bool enabled);
    uint8_t get_vterm();
    void set_vterm(VTERM vterm);
    uint8_t get_charge_status();
    uint8_t get_error_reason();
    uint8_t get_error_extra();
    void set_charge_current(uint16_t limit);

    // -------------------------------
    // -------- SYSREG ---------------
    // -------------------------------

    uint8_t get_vbus_status();

private:
    bool led_state[3] = {false};

};

#endif //NPM1300_H
