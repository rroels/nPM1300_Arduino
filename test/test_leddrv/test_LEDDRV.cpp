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
 * HELPERS
 */

void check_led_modes(nPM1300::LED led, uint16_t mode_register) {
    npm1300.led_set_mode(led, nPM1300::LEDMode::ERROR);
    reg_value = i2c_read_byte(mode_register);
    TEST_ASSERT_EQUAL_UINT8(0, reg_value);

    npm1300.led_set_mode(led, nPM1300::LEDMode::CHARGING);
    reg_value = i2c_read_byte(mode_register);
    TEST_ASSERT_EQUAL_UINT8(1, reg_value);

    npm1300.led_set_mode(led, nPM1300::LEDMode::HOST);
    reg_value = i2c_read_byte(mode_register);
    TEST_ASSERT_EQUAL_UINT8(2, reg_value);

    npm1300.led_set_mode(led, nPM1300::LEDMode::NOTUSED);
    reg_value = i2c_read_byte(mode_register);
    TEST_ASSERT_EQUAL_UINT8(3, reg_value);
}

// there is no way to check if the LED is actually on, so we have to rely on the software state
void check_led_on_off(nPM1300::LED led, uint16_t mode_register, uint16_t on_register, uint16_t off_register) {
    // put the led in "manual control" mode
    npm1300.led_set_mode(led, nPM1300::LEDMode::HOST);

    // assume starting state of "off"
    npm1300.led_off(led);
    TEST_ASSERT_FALSE(npm1300.led_get_state(led));

    npm1300.led_on(led);
    TEST_ASSERT_TRUE(npm1300.led_get_state(led));

    npm1300.led_off(led);
    TEST_ASSERT_FALSE(npm1300.led_get_state(led));

    npm1300.led_toggle(led);
    TEST_ASSERT_TRUE(npm1300.led_get_state(led));

    npm1300.led_toggle(led);
    TEST_ASSERT_FALSE(npm1300.led_get_state(led));
}

/*
 * TESTS
 */

// after a reset, the led modes should default to:
// led0 -> error mode
// led1 -> charging mode
// led2 -> host mode
void test_led_defaults() {
    npm1300.reset(); // clears led mode
    delay(100);

    reg_value = i2c_read_byte(0x0A00); // LEDDRV0MODESEL
    TEST_ASSERT_EQUAL_UINT8(0, reg_value); // 0 = ERROR
    reg_value = i2c_read_byte(0x0A01); // LEDDRV1MODESEL
    TEST_ASSERT_EQUAL_UINT8(1, reg_value); // 1 = CHARGING
    reg_value = i2c_read_byte(0x0A02); // LEDDRV2MODESEL
    TEST_ASSERT_EQUAL_UINT8(2, reg_value); // 2 = HOST
}

void test_led0_modes() {
    check_led_modes(nPM1300::LED0, 0x0A00); // LEDDRV0MODESEL
}

void test_led1_modes() {
    check_led_modes(nPM1300::LED1, 0x0A01); // LEDDRV1MODESEL
}

void test_led2_modes() {
    check_led_modes(nPM1300::LED2, 0x0A02); // LEDDRV2MODESEL
}

void test_led0_states() {
    check_led_on_off(nPM1300::LED0, 0x0A00, 0x0A03, 0x0A04); // LEDDRV0MODESEL, LEDDRV0SET & LEDDRV0CLR
}

void test_led1_states() {
    check_led_on_off(nPM1300::LED1, 0x0A01, 0x0A05, 0x0A06); // LEDDRV1MODESEL, LEDDRV1SET & LEDDRV1CLR
}

void test_led2_states() {
    check_led_on_off(nPM1300::LED2, 0x0A02, 0x0A07, 0x0A08); // LEDDRV2MODESEL, LEDDRV2SET & LEDDRV2CLR
}

/*
 * MAIN
 */

void setup() {
    Wire.begin();
    npm1300.reset();
    delay(100);

    UNITY_BEGIN();
    RUN_TEST(test_led_defaults);
    RUN_TEST(test_led0_modes);
    RUN_TEST(test_led1_modes);
    RUN_TEST(test_led2_modes);
    RUN_TEST(test_led0_states);
    RUN_TEST(test_led1_states);
    RUN_TEST(test_led2_states);
    UNITY_END();
}

void loop() { delay(1000); }
