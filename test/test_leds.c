#include "unity.h"
#include "leds.h"

#define LED_3       3
#define LED_BIT(x) (1 << (x - 1))

static uint16_t fake_port;

void setUp(void) {
    LedsInit(&fake_port);
}

/**
 * @brief Test: at Startup, all LEDs are off
 *
 */
void test_LedTurnOffAtStart(void) {
    uint16_t fake_port = 0xFFFF;
    LedsInit(&fake_port);
    TEST_ASSERT_EQUAL(0, fake_port);
}

void test_LedTurnOn(void) {
    LedTurnOn(LED_3);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED_3), fake_port);
}

void test_LedTurnOff(void) {
    LedTurnOn(LED_3);
    LedTurnOff(LED_3);
    TEST_ASSERT_EQUAL(0, fake_port);
}
