#include <stdint.h>

/**
 * @brief Initialize the leds
 *
 * @return void
 */
void LedsInit(uint16_t *port);

/**
 * @brief Test: TurnOn a singular led
 *
 */
void LedTurnOn(uint16_t led);
/**
 * @brief Test: TurnOff a singular led
 *
 */
void LedTurnOff(uint16_t led);