#include "unity.h"
#include "leds.h"
#include "mock_errors.h"

#define LED_1       1
#define LED_3       3
#define LED_5       5
#define LED_16      16
#define LED_BIT(x) (1 << (x - 1))
#define INVALID_LED -1

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

/**
 * @brief Test bad inputs
 *
 */
void test_LEDS_TurnOn_BadInput(void) {
    MessageRegister_Expect(0, "LEDS_TurnOn", 0, "Numero de led invalido");
    MessageRegister_CMockIgnoreArg_line(0);
    LEDS_TurnOn(INVALID_LED);
    TEST_ASSERT_EQUAL(0, fake_port);
}
/**
 * @brief Try to turn the first led on
 * 
 */
void test_LEDS_TurnOFF_BadInput(void) {
    MessageRegister_Expect(0, "LEDS_TurnOff", 0, "Numero de led invalido");
    MessageRegister_CMockIgnoreArg_line(0);
    LEDS_TurnOff(INVALID_LED);
}
/**
 * @brief Try to turn the last led on
 * 
 */
void test_LEDS_TurnOnLowLimit(void) {
    LEDS_TurnOn(LED1);
    TEST_ASSERT_EQUAL(LED_BIT(LED_1), fake_port);
}

void test_LEDS_TurnOnHighLimit(void) {
    LEDS_TurnOn(LED16);
    TEST_ASSERT_EQUAL(LED_BIT(LED_16), fake_port);
}
/**
 * @brief Try to turn one led just over the limit and under the limit
 * 
 */
void test_LEDS_TurnOn_OutOfRangeAtLimit(void) {
    MessageRegister_Expect(0, "LEDS_TurnOn", 0, "Numero de led invalido");
    MessageRegister_CMockIgnoreArg_line(0);
    LEDS_TurnOn(17);
    MessageRegister_Expect(0, "LEDS_TurnOn", 0, "Numero de led invalido");
    MessageRegister_CMockIgnoreArg_line(0);
    LEDS_TurnOn(0);
    TEST_ASSERT_EQUAL(0, fake_port);
}

