#include "leds.h"
#include "os/serial_port.h"
#include "os/shell/shell_command_utils.h"
#include "os/system_time.h"
#include "pins.h"

/* ************************************************************************** */

void sh_leds(int argc, char **argv);

void leds_init(void) {
    //

    shell_register_command(sh_leds, "leds");
}

/* ************************************************************************** */

uint16_t red_blink_cooldown = 1000;
bool red_blink_enabled = true;

void attempt_red_blink(void) {
    static system_time_t lastAttempt = 0;
    if (time_since(lastAttempt) < red_blink_cooldown) {
        return;
    }
    lastAttempt = get_current_time();

    if (red_blink_enabled) {
        static bool state = false;
        set_RED_LED_PIN(state);
        state = !state;
    }
}

/* -------------------------------------------------------------------------- */

uint16_t yellow_blink_cooldown = 2000;
bool yellow_blink_enabled = true;

void attempt_yellow_blink(void) {
    static system_time_t lastAttempt = 0;
    if (time_since(lastAttempt) < yellow_blink_cooldown) {
        return;
    }
    lastAttempt = get_current_time();

    if (yellow_blink_enabled) {
        static bool state = false;
        set_YELLOW_LED_PIN(state);
        state = !state;
    }
}

/* -------------------------------------------------------------------------- */

uint16_t green_blink_cooldown = 5000;
bool green_blink_enabled = true;

void attempt_green_blink(void) {
    static system_time_t lastAttempt = 0;
    if (time_since(lastAttempt) < green_blink_cooldown) {
        return;
    }
    lastAttempt = get_current_time();

    if (green_blink_enabled) {
        static bool state = false;
        set_GREEN_LED_PIN(state);
        state = !state;
    }
}

/* ************************************************************************** */

void sh_leds(int argc, char **argv) {
    bool *color_enabled;
    uint16_t *color_cooldown;

    switch (argc) {
    case 1:
        println("usage: \tleds");
        println("\tleds <color> enable");
        println("\tleds <color> disable");
        println("\tleds set <color> <cooldown>");
        println("\tleds read");
        return;
    case 2:
        if (!strcmp(argv[1], "read")) {
            println("led cooldowns:");
            printf("red: %u\r\n", red_blink_cooldown);
            printf("yellow: %u\r\n", yellow_blink_cooldown);
            printf("green: %u\r\n", green_blink_cooldown);
            return;
        } else {
            break;
        }
    case 3:
        if (!strcmp(argv[1], "red")) {
            color_enabled = &red_blink_enabled;
        } else if (!strcmp(argv[1], "yellow")) {
            color_enabled = &yellow_blink_enabled;
        } else if (!strcmp(argv[1], "green")) {
            color_enabled = &green_blink_enabled;
        } else {
            break;
        }

        if (!strcmp(argv[2], "enable")) {
            *color_enabled = true;
        } else if (!strcmp(argv[2], "disable")) {
            *color_enabled = false;
        } else {
            break;
        }
        break;
    case 4:
        if (!strcmp(argv[1], "set")) {
            if (!strcmp(argv[2], "red")) {
                color_cooldown = &red_blink_cooldown;
            } else if (!strcmp(argv[2], "yellow")) {
                color_cooldown = &yellow_blink_cooldown;
            } else if (!strcmp(argv[2], "green")) {
                color_cooldown = &green_blink_cooldown;
            } else {
                break;
            }

            *color_cooldown = atoi(argv[3]);

            return;
        }
        break;
    }
    println("invalid arguments");
}