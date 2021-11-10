#include "leds.h"
//============[PRIVATE CONSTANTS]=====================
#define LED_PORT_INITIAL_VALUE 0x0000
#define SET_LED(x) (1 << (x - 1))

static uint16_t *port;


void LedsInit(uint16_t *direccion) {
    port = direccion;
    *port = LED_PORT_INITIAL_VALUE;
}

void LedTurnOn(led_t led) {
    *port |= SET_LED(led);
}

void LedTurnOff(led_t led) {
    *port &= ~SET_LED(led);
}
