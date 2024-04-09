#include "os/logging.h"
#include "os/serial_port.h"
#include "os/shell/shell.h"
#include "os/shell/shell_command_utils.h"
#include "os/shell/shell_keys.h"
#include "os/shell/shell_utils.h"
#include "os/system_time.h"
#include "peripherals/timer.h"
#include "pins.h"
#include <stdint.h>

static uint8_t LOG_LEVEL = L_SILENT;

/* ************************************************************************** */

enum bargraph_modes {
    bargraph_cylon,
    bargraph_set,
};

enum bargraph_modes bargraph_mode = bargraph_set;

/* ************************************************************************** */

static void bargraph_spi_bitbang_tx_word(uint16_t word) {
    set_BARGRAPH_STROBE(1);
    set_BARGRAPH_CLOCK(0);

    for (uint8_t i = 0; i < 16; i++) {
        if (word & (1 << (15 - i))) {
            set_BARGRAPH_DATA(1);
        } else {
            set_BARGRAPH_DATA(0);
        }
        delay_us(10);
        set_BARGRAPH_CLOCK(1);
        delay_us(10);
        set_BARGRAPH_CLOCK(0);
        delay_us(10);
    }
    set_BARGRAPH_STROBE(0);
    delay_us(10);
    set_BARGRAPH_STROBE(1);
    delay_us(10);
}

// forward declaration
void sh_bar(int argc, char **argv);

void bargraph_init(void) {
    log_register();

    set_BARGRAPH_CLOCK(1);
    set_BARGRAPH_DATA(1);
    set_BARGRAPH_STROBE(1);

    bargraph_spi_bitbang_tx_word(0xFFFF);

    shell_register_command(sh_bar, "bar");
}

/* ************************************************************************** */

#define BARGRAPH_UPDATE_COOLDOWN 100

uint16_t cylonValue = 0;
int8_t cylonDirection = 1;

void attempt_bargraph_update(void) {
    static system_time_t lastAttempt = 0;
    if (time_since(lastAttempt) < BARGRAPH_UPDATE_COOLDOWN) {
        return;
    }
    lastAttempt = get_current_time();

    switch (bargraph_mode) {
    case bargraph_set:
        break;
    case bargraph_cylon:
        LOG_DEBUG({ println("updating cylon mode"); });
        if (cylonValue == 0) {
            cylonDirection = 1;
        }
        if (cylonValue == 9) {
            cylonDirection = -1;
        }
        cylonValue += cylonDirection;
        bargraph_spi_bitbang_tx_word(0x1 << cylonValue);
        break;
    }
}

/* ************************************************************************** */

// setup
void sh_bar(int argc, char **argv) {
    switch (argc) {
    case 1:
        println("usage: \tbar");
        println("\tbar <off|cylon|set>");
        println("\tbar set <value>");
        return;

    case 2:
        if (!strcmp(argv[1], "off")) {
            LOG_DEBUG({ println("setting bargraph off"); });
            bargraph_mode = bargraph_set;

            bargraph_spi_bitbang_tx_word(0x0000);
            return;
        } else if (!strcmp(argv[1], "on")) {
            LOG_DEBUG({ println("setting bargraph on"); });
            bargraph_mode = bargraph_set;

            bargraph_spi_bitbang_tx_word(0xFFFF);
            return;
        } else if (!strcmp(argv[1], "cylon")) {
            LOG_DEBUG({ println("setting bargraph to cylon"); });

            bargraph_mode = bargraph_cylon;
            return;
        } else {
            break;
        }
    case 3:
        if (!strcmp(argv[1], "set")) {
            LOG_DEBUG({ println("setting bargraph to value"); });
            uint8_t value = atoi(argv[2]);

            bargraph_mode = bargraph_set;
            
            bargraph_spi_bitbang_tx_word(~(0xFFFF << value));

            return;
        } else {
            break;
        }
    }
    println("invalid arguments");
}