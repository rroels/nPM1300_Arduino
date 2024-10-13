#include <Arduino.h>
#include <unity.h>
#include "npm1300.h"
#include "../helpers/i2c_helper.h"

/*
 * SETUP
 */

nPM1300 npm1300(Wire, 0x6B);
uint8_t reg_value = 0;

void setUp(void) {}

void tearDown(void) {}

/*
 * TESTS
 */

// we know the led modes revert to their default values after a reset
// we use this to verify that the nPM1300 resets when instructed
void test_reset() {
    // led0 should start in "error mode"
    reg_value = i2c_read_byte(0x0A00); // LEDDRV0MODESEL
    TEST_ASSERT_EQUAL_UINT8(0, reg_value); // 0 = ERROR

    // change led0 to charging mode
    npm1300.led_set_mode(nPM1300::LED0, nPM1300::LEDMode::CHARGING);

    // verify charging mode
    reg_value = i2c_read_byte(0x0A00); // LEDDRV0MODESEL
    TEST_ASSERT_EQUAL_UINT8(1, reg_value); // 1 = CHARGING

    npm1300.reset(); // reset
    delay(100);

    // led0 should be in "error mode" after the reset
    reg_value = i2c_read_byte(0x0A00); // LEDDRV0MODESEL
    TEST_ASSERT_EQUAL_UINT8(0, reg_value); // 0 = ERROR
}



/*
 * MAIN
 */

void setup() {
    Wire.begin();
    npm1300.reset();
    delay(100);

    UNITY_BEGIN();
    RUN_TEST(test_reset);
    UNITY_END();
}

void loop() { delay(1000); }
