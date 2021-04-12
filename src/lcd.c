#include "os/serial_port.h"
#include "os/shell/shell_command_utils.h"
#include "os/system_time.h"
#include "peripherals/timer.h"
#include "pins.h"
#include "rgb.h"

/* ************************************************************************** */

void lcd_tx_char(char c) {
    uint8_t i;
    char a;

    set_LCD_TX_PIN(1);

    while (!timer2_IF_read()) {
    };
    timer2_IF_clear();

    while (!timer2_IF_read()) {
    };
    timer2_IF_clear();

    set_LCD_TX_PIN(0);
    for (i = 0; i <= 7; i++) {
        a = ((c >> i) & 0x01);
        while (!timer2_IF_read()) {
        };
        timer2_IF_clear();

        set_LCD_TX_PIN(a);
    }
    while (!timer2_IF_read()) {
    };
    timer2_IF_clear();
    set_LCD_TX_PIN(1);

    while (!timer2_IF_read()) {
    };

    timer2_IF_clear();

    while (!timer2_IF_read()) {
    };
    timer2_IF_clear();
}

void lcd_tx_string(const char *string) {
    uint8_t i = 0;
    while (string[i]) {
        lcd_tx_char(string[i++]);
    }
}

/* ************************************************************************** */

#define CONTROL_1 0xfe

#define CLEAR_DISPLAY 0x01
#define CURSOR_RIGHT 0x14
#define CURSOR_LEFT 0x10
#define SCROLL_RIGHT 0x1C
#define SCROLL_LEFT 0x18
#define DISPLAY_ON 0x0C
#define DISPLAY_OFF 0x08
#define CURSOR_UNDERLINE 0x0E
#define CURSOR_BLINK 0x0D
#define CURSOR_SET 0x80

#define CONTROL_2 0x7c

#define BACKLIGHT_OFF 0x80
#define BACKLIGHT_ON 0x9D

#define CONTROL_3 0x12

void lcd_clear(void) {
    lcd_tx_char(CONTROL_1);
    lcd_tx_char(CLEAR_DISPLAY);
}

void lcd_move_cursor(uint8_t position) {
    if (position > 103) {
        position = 103;
    }
    lcd_tx_char(CONTROL_1);
    lcd_tx_char(CURSOR_SET + position);
}

void lcd_set_backlight(uint8_t brightness) {
    if (brightness > 32) {
        brightness = 32;
    }
    lcd_tx_char(CONTROL_2);
    lcd_tx_char(BACKLIGHT_OFF + brightness);
}

/* ************************************************************************** */

// forward declaration
void sh_lcd(int argc, char **argv);

void lcd_init(void) {
    // uart_config_t config = UART_get_config(4);
    // config.baud = _9600;
    // config.txPin = PPS_LCD_TX_PIN;
    // config.rxPin = PPS_LCD_RX_PIN;
    // create_uart_buffers(lcd, config, 128);

    // uart = UART_init(&config);
    set_LCD_TX_PIN(1);
    timer2_clock_source(TMR2_CLK_FOSC4);
    timer2_postscale(TMR_POSTSCALE_10);
    timer2_period_set(168);
    timer2_start();

    shell_register_command(sh_lcd, "lcd");
}

/* ************************************************************************** */

void sh_lcd(int argc, char **argv) {
    switch (argc) {
    case 1:
        println("usage: \tlcd");
        println("\tlcd clear");
        println("\tlcd test");
        println("\tlcd blink");
        println("\tlcd write <text>");
        println("\tlcd backlight <brightness>");
        return;
    case 2:
        if (!strcmp(argv[1], "clear")) {
            lcd_clear();
            return;
        } else if (!strcmp(argv[1], "test")) {
            // uart.tx_string("beep", '\0');
            lcd_tx_char('b');
            lcd_tx_char('e');
            lcd_tx_char('e');
            lcd_tx_char('p');
            return;
        } else if (!strcmp(argv[1], "blink")) {
            lcd_tx_char(CONTROL_1);
            lcd_tx_char(CURSOR_BLINK);
            return;
        }
        break;
    case 3:
        if (!strcmp(argv[1], "backlight")) {
            lcd_set_backlight(atoi(argv[2]));
            return;
        }
        break;
    }
    println("invalid arguments");
}