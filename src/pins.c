#include "pins.h"
#include "peripherals/pic_header.h"

/* ************************************************************************** */
/* [[[cog
    from codegen import fmt; import pins
    cog.outl(fmt(pins.pin_definitions()))
]]] */

// GPIO read functions
// none

// Button stuff
// none

// GPIO write functions
void set_GREEN_LED_PIN(bool value) { LATCbits.LATC3 = value; }
void set_RGB_1_LED_PIN(bool value) { LATCbits.LATC4 = value; }
void set_RGB_2_LED_PIN(bool value) { LATCbits.LATC5 = value; }
void set_RGB_3_LED_PIN(bool value) { LATCbits.LATC6 = value; }
void set_YELLOW_LED_PIN(bool value) { LATDbits.LATD0 = value; }
void set_RED_LED_PIN(bool value) { LATDbits.LATD1 = value; }

// GPIO direction functions
// none

// [[[end]]]

/* ************************************************************************** */
/* [[[cog
    from codegen import fmt; import pins
    cog.outl(fmt(pins.pins_init()))
]]] */

void pins_init(void) {
    // DEBUG_RX_PIN
    TRISBbits.TRISB6 = 1;

    // DEBUG_TX_PIN
    TRISBbits.TRISB7 = 0;

    // GREEN_LED_PIN
    TRISCbits.TRISC3 = 0;

    // RGB_1_LED_PIN
    TRISCbits.TRISC4 = 0;

    // RGB_2_LED_PIN
    TRISCbits.TRISC5 = 0;

    // RGB_3_LED_PIN
    TRISCbits.TRISC6 = 0;

    // YELLOW_LED_PIN
    TRISDbits.TRISD0 = 0;

    // RED_LED_PIN
    TRISDbits.TRISD1 = 0;

    // USB_TX_PIN
    TRISFbits.TRISF6 = 0;

    // USB_RX_PIN
    TRISFbits.TRISF7 = 1;
}
// [[[end]]]