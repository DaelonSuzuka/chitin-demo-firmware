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
// none

// Button stuff
// none

// GPIO write functions
extern void set_GREEN_LED_PIN(bool value);
extern void set_RGB_1_LED_PIN(bool value);
extern void set_RGB_2_LED_PIN(bool value);
extern void set_RGB_3_LED_PIN(bool value);
extern void set_YELLOW_LED_PIN(bool value);
extern void set_RED_LED_PIN(bool value);

// GPIO direction functions
// none

// PPS Pin initialization macros
#define PPS_DEBUG_RX_PIN PPS_INPUT(B, 6)
#define PPS_DEBUG_TX_PIN PPS_OUTPUT(B, 7)
#define PPS_USB_TX_PIN PPS_OUTPUT(F, 6)
#define PPS_USB_RX_PIN PPS_INPUT(F, 7)

// ADC Channel Select macros
// none

// [[[end]]]

/* ************************************************************************** */

extern void pins_init(void);

#endif /* _PINS_H_ */