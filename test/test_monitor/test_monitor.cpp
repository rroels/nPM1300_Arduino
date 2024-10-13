#include <Arduino.h>
#include <unity.h>
#include "npm1300.h"
#include "../helpers/i2c_helper.h"

/*
 * SETUP
 */

nPM1300 npm1300(Wire, 0x6B);
float measurement = 0;

void setUp(void) {}

void tearDown(void) {}

/*
 * TESTS
 */

void test_measure_vbat() {
    measurement = npm1300.measure_vbat();
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(1.5, 3.5, measurement, "Should be between 2.0V and 5.0V");
}

void test_measure_vbus() {
    measurement = npm1300.measure_vbus();
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(2.75, 2.75, measurement, "Should be between 0.0V and 5.5V");
}

void test_measure_vsys() {
    measurement = npm1300.measure_vsys();
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(1.5, 3.5, measurement, "Should be between 2.0V and 5.0V");
}

void test_measure_temperature() {
    measurement = npm1300.measure_temperature();
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(20, 30, measurement, "Should be between 20 and 50C");
}

/*
 * MAIN
 */

void setup() {
    Wire.begin();

    npm1300.reset();
    delay(100);

    npm1300.set_vterm(nPM1300::V4_15);
    npm1300.ignore_ntc(true);
    npm1300.set_charge_current(400);
    npm1300.charger_on();

    UNITY_BEGIN();
    RUN_TEST(test_measure_vbat);
    RUN_TEST(test_measure_vbus);
    RUN_TEST(test_measure_vsys);
    RUN_TEST(test_measure_temperature);
    UNITY_END();
}

void loop() { delay(1000); }
