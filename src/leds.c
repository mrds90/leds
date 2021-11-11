#include "leds.h"
//============[PRIVATE CONSTANTS]=====================
#define LED_PORT_INITIAL_VALUE 0x0000
#define LedToMask(led) (1 << (led - 1))

//============[PRIVATE FUNTIONS DECLARATION]=====================


//============[PRIVATE GLOBAL VARIABLES]=====================

static uint16_t *port;

//============[PUBLIC METHODS IMPLEMENATION]=====================

void LEDS_Init(uint16_t *direccion) {
    port = direccion;
    *port = LED_PORT_INITIAL_VALUE;
}

void LEDS_TurnOn(led_t led) {
    *port |= LedToMask(led);
}

void LEDS_TurnOff(led_t led) {
    *port &= ~LedToMask(led);
}

//============[PRIVATE METHODS IMPLEMENATION]=====================
