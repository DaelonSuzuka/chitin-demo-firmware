#include "rgb.h"
#include "os/serial_port.h"
#include "os/shell/shell_command_utils.h"
#include "os/system_time.h"
#include "pins.h"

/* ************************************************************************** */

enum rgb_colors {
    rgb_red,
    rgb_green,
    rgb_blue,
    rgb_cyan,
    rgb_yellow,
    rgb_magenta,
    rgb_white,
    rgb_num_of_colors,
};

enum rgb_modes {
    rgb_off,
    rgb_blink,
    rgb_fade,
};

enum rgb_modes rgb_mode = rgb_off;

/* ************************************************************************** */

void sh_rgb(int argc, char **argv);

void rgb_init(void) {
    //

    shell_register_command(sh_rgb, "rgb");
}

/* -------------------------------------------------------------------------- */

void set_rgb_color(enum rgb_colors color) {
    switch (color) {
    case rgb_red:
        set_RGB_1_LED_PIN(0); // blue
        set_RGB_2_LED_PIN(0); // green
        set_RGB_3_LED_PIN(1); // red
        break;
    case rgb_green:
        set_RGB_1_LED_PIN(0); // blue
        set_RGB_2_LED_PIN(1); // green
        set_RGB_3_LED_PIN(0); // red
        break;
    case rgb_blue:
        set_RGB_1_LED_PIN(1); // blue
        set_RGB_2_LED_PIN(0); // green
        set_RGB_3_LED_PIN(0); // red
        break;
    case rgb_cyan:
        set_RGB_1_LED_PIN(1); // blue
        set_RGB_2_LED_PIN(1); // green
        set_RGB_3_LED_PIN(0); // red
        break;
    case rgb_yellow:
        set_RGB_1_LED_PIN(0); // blue
        set_RGB_2_LED_PIN(1); // green
        set_RGB_3_LED_PIN(1); // red
        break;
    case rgb_magenta:
        set_RGB_1_LED_PIN(1); // blue
        set_RGB_2_LED_PIN(0); // green
        set_RGB_3_LED_PIN(1); // red
        break;
    case rgb_white:
        set_RGB_1_LED_PIN(1); // blue
        set_RGB_2_LED_PIN(1); // green
        set_RGB_3_LED_PIN(1); // red
        break;
    }
}
#define RGB_BLINK_COOLDOWN 1000

void attempt_rgb_blink(void) {
    static system_time_t lastAttempt = 0;
    if (time_since(lastAttempt) < RGB_BLINK_COOLDOWN) {
        return;
    }
    lastAttempt = get_current_time();

    static enum rgb_colors current_color = 0;

    if (rgb_mode != rgb_off) {
        set_rgb_color(current_color);
        current_color++;
        if (current_color == rgb_num_of_colors) {
            current_color = 0; //
        }
    }
}

/* --------------------------------------------------------------------------
 */

#define RGB_FADE_COOLDOWN 10

void attempt_rgb_fade(void) {
    static system_time_t lastAttempt = 0;
    if (time_since(lastAttempt) < RGB_FADE_COOLDOWN) {
        return;
    }
    lastAttempt = get_current_time();

    if (rgb_mode != rgb_off) {
        // println("fade...");
    }
}

/* --------------------------------------------------------------------------
 */

#define RGB_UPDATE_COOLDOWN 5

void attempt_rgb_update(void) {
    static system_time_t lastAttempt = 0;
    if (time_since(lastAttempt) < RGB_UPDATE_COOLDOWN) {
        return;
    }
    lastAttempt = get_current_time();

    switch (rgb_mode) {
    case rgb_off:
        break;
    case rgb_blink:
        attempt_rgb_blink();
        break;
    case rgb_fade:
        attempt_rgb_fade();
        break;
    }
}

/* ************************************************************************** */

void sh_rgb(int argc, char **argv) {
    switch (argc) {
    case 1:
        println("usage: \trgb");
        println("\trgb <mode>");
        return;

    case 2:
        if (!strcmp(argv[1], "off")) {
            rgb_mode = rgb_off;
            set_RGB_1_LED_PIN(0); // blue
            set_RGB_2_LED_PIN(0); // green
            set_RGB_3_LED_PIN(0); // red
            return;
        } else if (!strcmp(argv[1], "blink")) {
            rgb_mode = rgb_blink;
            return;
        } else if (!strcmp(argv[1], "fade")) {
            rgb_mode = rgb_fade;
            return;
        } else {
            break;
        }
    }
    println("invalid arguments");
}