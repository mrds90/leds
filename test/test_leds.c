#include "unity.h"
#include "leds.h"

#define LED_3       3
#define LED_5       5
#define LED_BIT(x) (1 << (x - 1))

static uint16_t fake_port;

void setUp(void) {
    LEDS_Init(&fake_port);
}

/**
 * @brief Test: at Startup, all LEDs are off
 *
 */
void test_LEDS_TurnOffAtStart(void) {
    uint16_t fake_port = 0xFFFF;
    LEDS_Init(&fake_port);
    TEST_ASSERT_EQUAL(0, fake_port);
}

/**
 * @brief Test: Turn on LED 3
 *
 */
void test_LEDS_TurnOn(void) {
    LEDS_TurnOn(LED3);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED_3), fake_port);
}

/**
 * @brief Test: Turn off LED 3
 *
 */
void test_LEDS_TurnOff(void) {
    LEDS_TurnOn(LED3);
    LEDS_TurnOff(LED3);
    TEST_ASSERT_EQUAL(0, fake_port);
}

/**
 * @brief Test: Turn on LED 3 and 5 then turn it off the led 3
 *
 */
void test_LEDS_TurnOnAndOffSeveralLeds(void) {
    LEDS_TurnOn(LED3);
    LEDS_TurnOn(LED5);
    LEDS_TurnOff(LED3);
    TEST_ASSERT_EQUAL((LED_BIT(LED_5)), fake_port);
}
