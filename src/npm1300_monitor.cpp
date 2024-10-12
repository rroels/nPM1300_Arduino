#include <Wire.h>
#include "npm1300.h"

float nPM1300::measure_vbat() {
    write_register(TASKVBATMEASURE, 0b00000001);

    uint8_t vbat_msb = read_register(ADCVBATRESULTMSB);
    uint8_t vbat_lsb = read_register(ADCGP0RESULTLSBS);
    vbat_lsb = (vbat_lsb & 0b00000011);
    uint16_t total = (vbat_msb << 2) | vbat_lsb;

    // (V_BATADC/1023) * VFS_VBAT
    // VFS_VBAT	= 5.0 (fixed value, see datasheet)
    return (total / 1023.0) * 5.0;
}

float nPM1300::measure_vbus() {
    write_register(TASKVBUS7MEASURE, 0b00000001);

    // ADCVBAT3RESULTMSB is not a typo, it is shared for vbat and vbus results
    uint8_t vbat_msb = read_register(ADCVBAT3RESULTMSB);
    uint8_t vbat_lsb = read_register(ADCGP1RESULTLSBS);
    vbat_lsb = (vbat_lsb & 0b00000011);
    uint16_t total = (vbat_msb << 2) | vbat_lsb;

    // (V_BUSADC/1023) * VFS_VBUS
    // VFS_VBUS	= 7.5 (fixed value, see datasheet)
    return (total / 1023.0) * 7.5;
}

float nPM1300::measure_vsys() {
    write_register(TASKVSYSMEASURE, 0b00000001);

    uint8_t vsys_msb = read_register(ADCVSYSRESULTMSB);
    uint8_t vsys_lsb = read_register(ADCGP0RESULTLSBS);
    vsys_lsb = (vsys_lsb & 0b11000000) >> 6;
    uint16_t total = (vsys_msb << 2) | vsys_lsb;

    // (V_SYSADC/1023) * VFS_VSYS
    // VFS_VSYS	= 6.375 (fixed value, see datasheet)
    return (total / 1023.0) * 6.375;
}

float nPM1300::measure_temperature() {
    write_register(	TASKTEMPMEASURE, 0b00000001);

    uint8_t temp_msb = read_register(ADCTEMPRESULTMSB);
    uint8_t temp_lsb = read_register(ADCGP0RESULTLSBS);
    temp_lsb = (temp_lsb & 0b00110000) >> 4;
    uint16_t total = (temp_msb << 2) | temp_lsb;

    // 394.67 - 0.7926 * k_dietemp
    return 394.67 - (0.7926 * total);
}