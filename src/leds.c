#include "leds.h"
//============[PRIVATE CONSTANTS]=====================
#define LED_PORT_INITIAL_VALUE 0x0000

static uint16_t *port;


void LedsInit(uint16_t *direccion) {
    port = direccion;
    *port = LED_PORT_INITIAL_VALUE;
}

void LedTurnOn(uint16_t led) {
    *port = 1 << 2;
}

void LedTurnOff(uint16_t led) {
    *port = LED_PORT_INITIAL_VALUE;
}