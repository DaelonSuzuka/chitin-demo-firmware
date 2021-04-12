#include "ui.h"
#include "leds.h"
#include "os/buttons.h"
#include "os/judi/judi.h"
#include "os/serial_port.h"
#include "os/shell/shell.h"
#include "os/system_time.h"
#include "os/usb_port.h"
#include "pins.h"
#include "rgb.h"

/* ************************************************************************** */

void ui_idle_block(void) {
    // individual leds
    attempt_red_blink();
    attempt_yellow_blink();
    attempt_green_blink();

    // rgb led
    attempt_rgb_update();

    shell_update(getch());

    judi_update(usb_getch());
}

/* ************************************************************************** */


void ui_mainloop(void) {
    while (1) {
        ui_idle_block();
    }
}