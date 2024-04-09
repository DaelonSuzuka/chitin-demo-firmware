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

// GPIO write functions
extern void set_GREEN_LED_PIN(bool value);
extern void set_YELLOW_LED_PIN(bool value);
extern void set_RED_LED_PIN(bool value);
extern void set_BARGRAPH_CLOCK(bool value);
extern void set_BARGRAPH_MISO(bool value);
extern void set_BARGRAPH_DATA(bool value);
extern void set_LCD_TX_PIN(bool value);
extern void set_RGB_1_LED_PIN(bool value);
extern void set_RGB_2_LED_PIN(bool value);
extern void set_RGB_3_LED_PIN(bool value);
extern void set_BARGRAPH_STROBE(bool value);

// GPIO direction functions
// none

// PPS Pin initialization macros
#define PPS_DEBUG_RX_PIN PPS_INPUT(B, 6)
#define PPS_DEBUG_TX_PIN PPS_OUTPUT(B, 7)
#define PPS_LCD_RX_PIN PPS_INPUT(D, 3)
#define PPS_USB_TX_PIN PPS_OUTPUT(F, 6)
#define PPS_USB_RX_PIN PPS_INPUT(F, 7)

// ADC Channel Select macros
// none

// [[[end]]]

/* ************************************************************************** */

extern void pins_init(void);

#endif /* _PINS_H_ */