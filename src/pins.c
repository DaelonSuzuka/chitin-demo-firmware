#include "pins.h"
#include "peripherals/pic_header.h"

/* ************************************************************************** */
/* [[[cog
    from codegen import fmt; import pins
    cog.outl(fmt(pins.pin_definitions()))
]]] */

// GPIO read functions
bool read_ONE_BUTTON_PIN(void) { return PORTAbits.RA2; }
bool read_TWO_BUTTON_PIN(void) { return PORTAbits.RA3; }

// Button stuff
// array of pointers to button reading functions
button_function_t buttonFunctions[NUMBER_OF_BUTTONS] = {
    read_ONE_BUTTON_PIN, //
    read_TWO_BUTTON_PIN, //
};

// GPIO write functions
void set_GREEN_LED_PIN(bool value) { LATAbits.LATA5 = value; }
void set_YELLOW_LED_PIN(bool value) { LATAbits.LATA6 = value; }
void set_RED_LED_PIN(bool value) { LATAbits.LATA7 = value; }
void set_BARGRAPH_CLOCK(bool value) { LATCbits.LATC3 = value; }
void set_BARGRAPH_MISO(bool value) { LATCbits.LATC4 = value; }
void set_BARGRAPH_DATA(bool value) { LATCbits.LATC5 = value; }
void set_LCD_TX_PIN(bool value) { LATDbits.LATD2 = value; }
void set_RGB_1_LED_PIN(bool value) { LATDbits.LATD5 = value; }
void set_RGB_2_LED_PIN(bool value) { LATDbits.LATD6 = value; }
void set_RGB_3_LED_PIN(bool value) { LATDbits.LATD7 = value; }
void set_BARGRAPH_STROBE(bool value) { LATEbits.LATE0 = value; }

// GPIO direction functions
// none

// [[[end]]]

/* ************************************************************************** */
/* [[[cog
    from codegen import fmt; import pins
    cog.outl(fmt(pins.pins_init()))
]]] */

void pins_init(void) {
    // ONE_BUTTON_PIN
    TRISAbits.TRISA2 = 1;
    WPUAbits.WPUA2 = 1;

    // TWO_BUTTON_PIN
    TRISAbits.TRISA3 = 1;
    WPUAbits.WPUA3 = 1;

    // GREEN_LED_PIN
    TRISAbits.TRISA5 = 0;

    // YELLOW_LED_PIN
    TRISAbits.TRISA6 = 0;

    // RED_LED_PIN
    TRISAbits.TRISA7 = 0;

    // DEBUG_RX_PIN
    TRISBbits.TRISB6 = 1;

    // DEBUG_TX_PIN
    TRISBbits.TRISB7 = 0;

    // BARGRAPH_CLOCK
    TRISCbits.TRISC3 = 0;

    // BARGRAPH_MISO
    TRISCbits.TRISC4 = 0;

    // BARGRAPH_DATA
    TRISCbits.TRISC5 = 0;

    // LCD_TX_PIN
    TRISDbits.TRISD2 = 0;

    // LCD_RX_PIN
    TRISDbits.TRISD3 = 1;

    // RGB_1_LED_PIN
    TRISDbits.TRISD5 = 0;

    // RGB_2_LED_PIN
    TRISDbits.TRISD6 = 0;

    // RGB_3_LED_PIN
    TRISDbits.TRISD7 = 0;

    // BARGRAPH_STROBE
    TRISEbits.TRISE0 = 0;

    // USB_TX_PIN
    TRISFbits.TRISF6 = 0;

    // USB_RX_PIN
    TRISFbits.TRISF7 = 1;
}
// [[[end]]]