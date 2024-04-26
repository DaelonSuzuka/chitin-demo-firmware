#ifndef _PINS_H_
#define _PINS_H_

#include "peripherals/pps.h"
#include <stdbool.h>

/* ************************************************************************** */
/* [[[cog
    from codegen import fmt; import pins
    cog.outl(fmt(pins.pin_declarations()))
]]] */

// GPIO read functions
extern bool read_ONE_BUTTON_PIN(void);
extern bool read_TWO_BUTTON_PIN(void);

// GPIO write functions
extern void set_GREEN_LED_PIN(bool value);
extern void set_YELLOW_LED_PIN(bool value);
extern void set_RED_LED_PIN(bool value);
extern void set_BARGRAPH_CLOCK_PIN(bool value);
extern void set_BARGRAPH_MISO_PIN(bool value);
extern void set_BARGRAPH_DATA_PIN(bool value);
extern void set_LCD_TX_PIN(bool value);
extern void set_RGB_1_LED_PIN(bool value);
extern void set_RGB_2_LED_PIN(bool value);
extern void set_RGB_3_LED_PIN(bool value);
extern void set_BARGRAPH_STROBE_PIN(bool value);

// GPIO direction functions
// none

// Button stuff
#define NUMBER_OF_BUTTONS 2

// array of pointers to button reading functions
typedef bool (*button_function_t)(void);
extern button_function_t buttonFunctions[NUMBER_OF_BUTTONS];

// enum of button names
enum {
    ONE,
    TWO,
} button_names;

// PPS Pin initialization macros
#define PPS_LCD_RX_PIN PPS_INPUT(D, 3)
#define PPS_USB_TX_PIN PPS_OUTPUT(F, 6)
#define PPS_USB_RX_PIN PPS_INPUT(F, 7)
#ifdef DEVELOPMENT
#define PPS_DEBUG_RX_PIN PPS_INPUT(B, 6)
#endif
#ifdef DEVELOPMENT
#define PPS_DEBUG_TX_PIN PPS_OUTPUT(B, 7)
#endif

// ADC Channel Select macros
#define ADC_KNOB_ONE_PIN 8
#define ADC_KNOB_TWO_PIN 9

// [[[end]]]

/* ************************************************************************** */

extern void pins_init(void);

#endif /* _PINS_H_ */