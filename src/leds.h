#ifndef _LEDS_H_
#define _LEDS_H_

#include <stdbool.h>
#include <stdint.h>

/* ************************************************************************** */

extern void leds_init(void);

/* ************************************************************************** */

extern void attempt_red_blink(void);
extern void attempt_yellow_blink(void);
extern void attempt_green_blink(void);

#endif // _LEDS_H_