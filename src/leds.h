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

typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_INVALID,
} led_state_t;
/**
 * @brief Initialize the leds
 *
 * @return void
 */
void LEDS_Init(uint16_t *port);

/**
 * @brief TurnOn a singular led
 *
 */
void LEDS_TurnOn(led_t led);

/**
 * @brief TurnOff a singular led
 *
 */
void LEDS_TurnOff(led_t led);

/**
 * @brief TurnOn all leds
 *
 */
void LEDS_TurnOnAll(void);

/**
 * @brief TurnOff all leds
 *
 */
void LEDS_TurnOffAll(void);

/**
 * @brief Toggle a singular led
 *
 */
led_state_t LEDS_GetState(led_t led);
