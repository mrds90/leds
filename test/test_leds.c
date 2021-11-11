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
    MessageRegister_Expect(0, "LEDS_TurnOn", 0, "Invalid Led number");
    MessageRegister_CMockIgnoreArg_line(0);
    LEDS_TurnOn(INVALID_LED);
    TEST_ASSERT_EQUAL(0, fake_port);
}

/**
 * @brief Try to turn the first led on
 *
 */
void test_LEDS_TurnOFF_BadInput(void) {
    MessageRegister_Expect(0, "LEDS_TurnOff", 0, "Invalid Led number");
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
    MessageRegister_Expect(0, "LEDS_TurnOn", 0, "Invalid Led number");
    MessageRegister_CMockIgnoreArg_line(0);
    LEDS_TurnOn(17);
    MessageRegister_Expect(0, "LEDS_TurnOn", 0, "Invalid Led number");
    MessageRegister_CMockIgnoreArg_line(0);
    LEDS_TurnOn(0);
    TEST_ASSERT_EQUAL(0, fake_port);
}

/**
 * @brief Test: Turn on all LEDs
 *
 */
void test_LEDS_TurnON_AllLeds(void) {
    LEDS_TurnOnAll();
    TEST_ASSERT_EQUAL(0xFFFF, fake_port);
}

/**
 * @brief Turn off all LEDs
 *
 */
void test_LEDS_TurnOff_AllLeds(void) {
    LEDS_TurnOnAll();
    LEDS_TurnOffAll();
    TEST_ASSERT_EQUAL(0x0, fake_port);
}

/**
 * @brief Check status of led turned on
 *
 */
void test_LEDS_GetStateOn(void) {
    LEDS_TurnOn(LED3);
    led_state_t state = LEDS_GetState(LED3);
    TEST_ASSERT_EQUAL(LED_ON, state);
}

/**
 * @brief Check status of led turned off
 *
 */
void test_LEDS_GetStateOff(void) {
    LEDS_TurnOnAll();
    LEDS_TurnOff(LED3);
    led_state_t state = LEDS_GetState(LED3);
    TEST_ASSERT_EQUAL(LED_OFF, state);
}

/**
 * @brief Try to get leds state of invalid led
 *
 */
void test_LEDS_GetStateInvalidLed(void) {
    LEDS_TurnOn(LED_3);
    MessageRegister_Expect(0, "LEDS_GetState", 0, "Invalid Led number");
    MessageRegister_CMockIgnoreArg_line(0);
    led_state_t state = LEDS_GetState(INVALID_LED);
    TEST_ASSERT_EQUAL(LED_INVALID, state);
}

/**
 * @brief Try to get leds state just under the limit
 *
 */
void test_LEDS_GetStateInvalidLowLimit(void) {
    LEDS_TurnOn(LED_3);
    MessageRegister_Expect(0, "LEDS_GetState", 0, "Invalid Led number");
    MessageRegister_CMockIgnoreArg_line(0);
    led_state_t state = LEDS_GetState(0);
    TEST_ASSERT_EQUAL(LED_INVALID, state);
}

/**
 * @brief Try to get leds state just over the limit
 *
 */
void test_LEDS_GetStateInvalidHighLimit(void) {
    LEDS_TurnOn(LED_3);
    MessageRegister_Expect(0, "LEDS_GetState", 0, "Invalid Led number");
    MessageRegister_CMockIgnoreArg_line(0);
    led_state_t state = LEDS_GetState(17);
    TEST_ASSERT_EQUAL(LED_INVALID, state);
}
