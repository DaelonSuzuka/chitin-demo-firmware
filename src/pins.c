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

// GPIO write functions
void set_GREEN_LED_PIN(bool value) { LATAbits.LATA5 = value; }
void set_YELLOW_LED_PIN(bool value) { LATAbits.LATA6 = value; }
void set_RED_LED_PIN(bool value) { LATAbits.LATA7 = value; }
void set_BARGRAPH_CLOCK_PIN(bool value) { LATCbits.LATC3 = value; }
void set_BARGRAPH_MISO_PIN(bool value) { LATCbits.LATC4 = value; }
void set_BARGRAPH_DATA_PIN(bool value) { LATCbits.LATC5 = value; }
void set_LCD_TX_PIN(bool value) { LATDbits.LATD2 = value; }
void set_RGB_1_LED_PIN(bool value) { LATDbits.LATD5 = value; }
void set_RGB_2_LED_PIN(bool value) { LATDbits.LATD6 = value; }
void set_RGB_3_LED_PIN(bool value) { LATDbits.LATD7 = value; }
void set_BARGRAPH_STROBE_PIN(bool value) { LATEbits.LATE0 = value; }

// GPIO direction functions
// none

// Button stuff
// array of pointers to button reading functions
button_function_t buttonFunctions[NUMBER_OF_BUTTONS] = {
    read_ONE_BUTTON_PIN, //
    read_TWO_BUTTON_PIN, //
};

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

    // KNOB_ONE_PIN
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 1;

    // KNOB_TWO_PIN
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 1;

    // BARGRAPH_CLOCK_PIN
    TRISCbits.TRISC3 = 0;

    // BARGRAPH_MISO_PIN
    TRISCbits.TRISC4 = 0;

    // BARGRAPH_DATA_PIN
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

    // BARGRAPH_STROBE_PIN
    TRISEbits.TRISE0 = 0;

    // USB_TX_PIN
    TRISFbits.TRISF6 = 0;

    // USB_RX_PIN
    TRISFbits.TRISF7 = 1;

// DEBUG_RX_PIN
#ifdef DEVELOPMENT
    TRISBbits.TRISB6 = 1;
#endif

// DEBUG_TX_PIN
#ifdef DEVELOPMENT
    TRISBbits.TRISB7 = 0;
#endif
}
// [[[end]]]