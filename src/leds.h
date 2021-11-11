#include <stdint.h>

/**
 * @brief Led names, used as parameters in the functions below.
 *
 */
typedef enum {
    LED1 = 1,   LED2,
    LED3,       LED4,
    LED5,       LED6,
    LED7,       LED8,
    LED9,       LED10,
    LED11,      LED12,
    LED13,      LED14,
    LED15,      LED16,
    LED_QTY,
} led_t;
/**
 * @brief Initialize the leds
 *
 * @return void
 */
void LEDS_Init(uint16_t *port);

/**
 * @brief Test: TurnOn a singular led
 *
 */
void LEDS_TurnOn(led_t led);

/**
 * @brief Test: TurnOff a singular led
 *
 */
void LEDS_TurnOff(led_t led);
/**
 * @brief Test: TurnOn all leds
 *
 */
void LEDS_TurnOnAll(void);
/**
 * @brief Test: TurnOff all leds
 *
 */
void LEDS_TurnOffAll(void);