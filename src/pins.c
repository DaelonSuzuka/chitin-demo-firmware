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
// none

// GPIO direction functions
// none

// [[[end]]]

/* ************************************************************************** */
/* [[[cog
    from codegen import fmt; import pins
    cog.outl(fmt(pins.pins_init()))
]]] */

void pins_init(void) {
    // DEBUG_TX_PIN
    TRISBbits.TRISB6 = 0;

    // DEBUG_RX_PIN
    TRISBbits.TRISB7 = 1;

    // USB_TX_PIN
    TRISFbits.TRISF6 = 0;

    // USB_RX_PIN
    TRISFbits.TRISF7 = 1;

// DEBUG_TX_PIN
#ifdef DEVELOPMENT
    TRISBbits.TRISB6 = 0;
#else
    TRISBbits.TRISB6 = 0;
#endif

// DEBUG_RX_PIN
#ifdef DEVELOPMENT
    TRISBbits.TRISB7 = 1;
#else
    TRISBbits.TRISB7 = 1;
#endif

// USB_TX_PIN
#ifdef DEVELOPMENT
    TRISFbits.TRISF6 = 0;
#else
    TRISFbits.TRISF6 = 0;
#endif

// USB_RX_PIN
#ifdef DEVELOPMENT
    TRISFbits.TRISF7 = 1;
#else
    TRISFbits.TRISF7 = 1;
#endif
}
// [[[end]]]