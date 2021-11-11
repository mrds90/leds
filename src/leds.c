#include "leds.h"
#include "errors.h"
//============[PRIVATE CONSTANTS]=====================
#define LED_PORT_INITIAL_VALUE 0x0000
#define LedToMask(led) (1 << (led - 1))
#define ALL_LEDS_MASK   0xFFFF
#define LED_STATUS(led)      (*port & LedToMask(led)) ? LED_ON : LED_OFF;

//============[PRIVATE FUNTIONS DECLARATION]=====================


//============[PRIVATE GLOBAL VARIABLES]=====================

static uint16_t *port;

//============[PUBLIC METHODS IMPLEMENATION]=====================

void LEDS_Init(uint16_t *direccion) {
    port = direccion;
    *port = LED_PORT_INITIAL_VALUE;
}

void LEDS_TurnOn(led_t led) {
    if (led >= LED1 && led < LED_QTY) {
        *port |= LedToMask(led);
    }
    else {
        MessageRegister(0, __FUNCTION__, __LINE__, "Invalid Led number");
    }
}

void LEDS_TurnOff(led_t led) {
    if (led >= LED1 && led < LED_QTY) {
        *port &= ~LedToMask(led);
    }
    else {
        MessageRegister(0, __FUNCTION__, __LINE__, "Invalid Led number");
    }
}

void LEDS_TurnOnAll(void) {
    *port = ALL_LEDS_MASK;
}

void LEDS_TurnOffAll(void) {
    *port = LED_PORT_INITIAL_VALUE;
}

led_state_t LEDS_GetState(led_t led) {
    led_state_t state;
    if (led >= LED1 && led < LED_QTY) {
        state = LED_STATUS(led);
    }
    else {
        MessageRegister(0, __FUNCTION__, __LINE__, "Invalid Led number");
        state = LED_INVALID;
    }
    return state;
}

//============[PRIVATE METHODS IMPLEMENATION]=====================
