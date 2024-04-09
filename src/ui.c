#include "ui.h"
#include "bargraph.h"
#include "leds.h"
#include "os/buttons.h"
#include "os/judi/judi.h"
#include "os/logging.h"
#include "os/serial_port.h"
#include "os/shell/shell.h"
#include "os/system_time.h"
#include "os/usb_port.h"
#include "pins.h"
#include "rgb.h"
static uint8_t LOG_LEVEL = L_SILENT;

/* ************************************************************************** */

void ui_idle_block(void) {
    // individual leds
    attempt_red_blink();
    attempt_yellow_blink();
    attempt_green_blink();

    // rgb led
    attempt_rgb_update();

    attempt_bargraph_update();

    shell_update(getch());

    judi_update(usb_getch());
}

/* ************************************************************************** */

void btn_one_hold(void) {
    LOG_DEBUG({ println("ONE pressed"); });

    system_time_t startTime = get_current_time();

    while (btn_is_down(ONE)) {
        ui_idle_block();
    }

    LOG_INFO({ printf("ONE held for %lu mS\r\n", time_since(startTime)); });
}

void btn_two_hold(void) {
    LOG_DEBUG({ println("TWO pressed"); });

    system_time_t startTime = get_current_time();

    while (btn_is_down(TWO)) {
        ui_idle_block();
    }

    LOG_INFO({ printf("TWO held for %lu mS\r\n", time_since(startTime)); });
}

/* -------------------------------------------------------------------------- */

void ui_mainloop(void) {
    log_register();

    while (1) {
        if (btn_is_down(ONE)) {
            btn_one_hold();
        }
        if (btn_is_down(TWO)) {
            btn_two_hold();
        }

        ui_idle_block();
    }
}