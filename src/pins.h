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
// none

// GPIO direction functions
// none

// PPS Pin initialization macros
#define PPS_DEBUG_TX_PIN PPS_OUTPUT(B, 6)
#define PPS_DEBUG_RX_PIN PPS_INPUT(B, 7)
#define PPS_USB_TX_PIN PPS_OUTPUT(F, 6)
#define PPS_USB_RX_PIN PPS_INPUT(F, 7)
#ifdef DEVELOPMENT
#define PPS_DEBUG_TX_PIN PPS_OUTPUT(B, 6)
#else
#define PPS_DEBUG_TX_PIN PPS_OUTPUT(B, 6)
#endif
#ifdef DEVELOPMENT
#define PPS_DEBUG_RX_PIN PPS_INPUT(B, 7)
#else
#define PPS_DEBUG_RX_PIN PPS_INPUT(B, 7)
#endif
#ifdef DEVELOPMENT
#define PPS_USB_TX_PIN PPS_OUTPUT(F, 6)
#else
#define PPS_USB_TX_PIN PPS_OUTPUT(F, 6)
#endif
#ifdef DEVELOPMENT
#define PPS_USB_RX_PIN PPS_INPUT(F, 7)
#else
#define PPS_USB_RX_PIN PPS_INPUT(F, 7)
#endif

// ADC Channel Select macros
// none

// [[[end]]]

/* ************************************************************************** */

extern void pins_init(void);

#endif /* _PINS_H_ */