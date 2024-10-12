# nPM1300 Arduino Driver

> [!WARNING]
> The information and material (code, designs, files, ...) are provided "AS IS". We make no representation or warranty of any kind, express or implied, regarding the accuracy, adequacy, validity, reliability, availability, or completeness of any information or material. Use this at your own risk.

> [!WARNING]
> At the time of writing this driver is under active development, and is nowhere near ready for real-world usage

## Introduction

This an Arduino driver for Nordic's nPM1300 PMIC.

## Driver Development Status

- [x] Soft Reset (RESET)
- [x] LED Driver (LEDDRV)
- [ ] System monitor 
- [ ] System regulator (SYSREG)
- [ ] Battery Charger (CHARGER)
- [ ] Load switches (LOADSW)
- [ ] LDO (LDO)
- [ ] GPIO (GPIO)
- [ ] Events
- [ ] Interupts

## Development Instructions

### Clean

`pio run -t clean`

### Build

`pio run`

### Upload

`pio run -t upload`

### Run Unit Tests

`pio test`

