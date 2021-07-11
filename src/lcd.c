#include "os/serial_port.h"
#include "os/shell/shell.h"
#include "os/shell/shell_command_utils.h"
#include "os/shell/shell_keys.h"
#include "os/shell/shell_utils.h"
#include "os/system_time.h"
#include "peripherals/timer.h"
#include "pins.h"
#include "rgb.h"

/* ************************************************************************** */

#define LCD_ROWS 4
#define LCD_COLS 20

struct {
    uint8_t cursor_x;
    uint8_t cursor_y;
    char grid[LCD_ROWS][LCD_COLS];
} lcd_state;

/* ************************************************************************** */

// EMPTY_UART_INTERFACE(uart);

// void lcd_tx_char(char c) {
//     uart.tx_char(c); //
// }

// void lcd_tx_string(const char *string) {
//     uart.tx_string(string, '\0'); //
// }

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

    memset(lcd_state.grid, ' ', 80);

    set_LCD_TX_PIN(1);
    timer2_clock_source(TMR2_CLK_FOSC4);
    timer2_postscale(TMR_POSTSCALE_10);
    timer2_period_set(168);
    timer2_start();

    lcd_clear();

    shell_register_command(sh_lcd, "lcd");
}

/* ************************************************************************** */

void draw_lcd(void) {
    term_reset_screen();
    term_cursor_set(0, 0);

    lcd_state.cursor_x = 0;
    lcd_state.cursor_y = 0;

    println("");
    println("|  LCD Render Preview  |");
    println("| -------------------- |");

    for (uint8_t row = 0; row < LCD_ROWS; row++) {
        print("| ");
        for (uint8_t col = 0; col < LCD_COLS; col++) {
            printf("%c", lcd_state.grid[row][col]);
        }
        println(" |");
    }

    println("| -------------------- |");
    println("");

    println("Anything you type in the above grid");
    println("should appear on the LCD.");

    println("");
    println("Press \033[1;32mBACKSPACE\033[0;37;40m to clear the LCD");
    println("Press \033[1;31mESCAPE\033[0;37;40m or \033[1;31mCTRL+C\033[0;37;40m to exit");

    term_cursor_set(3, 4);
}

void lcd_cursor_up(void) {
    if (lcd_state.cursor_y) {
        term_cursor_up(1);
        lcd_state.cursor_y--;
        lcd_move_cursor((lcd_state.cursor_y * LCD_COLS) + lcd_state.cursor_x);
    }
}

void lcd_cursor_down(void) {
    if (lcd_state.cursor_y < LCD_ROWS - 1) {
        term_cursor_down(1);
        lcd_state.cursor_y++;
        lcd_move_cursor((lcd_state.cursor_y * LCD_COLS) + lcd_state.cursor_x);
    }
}

void lcd_cursor_left(void) {
    if (lcd_state.cursor_x) {
        term_cursor_left(1);
        lcd_state.cursor_x--;
        lcd_move_cursor((lcd_state.cursor_y * LCD_COLS) + lcd_state.cursor_x);
    }
}

void lcd_cursor_right(void) {
    if (lcd_state.cursor_x < LCD_COLS) {
        term_cursor_right(1);
        lcd_state.cursor_x++;
        lcd_move_cursor((lcd_state.cursor_y * LCD_COLS) + lcd_state.cursor_x);
    }
}

void lcd_insert_char(char currentChar) {
    if (lcd_state.cursor_x < LCD_COLS) {
        lcd_tx_char(currentChar);
        printf("%c", currentChar);
        lcd_state.grid[lcd_state.cursor_y][lcd_state.cursor_x] = currentChar;
        lcd_state.cursor_x++;
    }
}

/* -------------------------------------------------------------------------- */

int8_t sh_lcd_keys(key_t key) {
    switch (key.key) {
    default:
        return 0;
    case BACKSPACE:
        lcd_state.cursor_x = 0;
        lcd_state.cursor_y = 0;
        memset(lcd_state.grid, ' ', 80);
        draw_lcd();
        lcd_clear();
        return 0;
    case DELETE:
        return 0;
    case UP:
        lcd_cursor_up();
        return 0;
    case DOWN:
        lcd_cursor_down();
        return 0;
    case LEFT:
        lcd_cursor_left();
        return 0;
    case RIGHT:
        lcd_cursor_right();
        return 0;
    case ENTER:
        return 0;
    case ESCAPE:
        return -1;
    }
}

/* ************************************************************************** */

// loop - executed on every key press
// must have a return to indicate desire to terminate program
// if the correct state to do that comes about during the last keypress
int8_t sh_lcd_callback(char currentChar) {
    if (iscntrl(currentChar)) {
        return sh_lcd_keys(identify_key(currentChar));
    }

    if (isprint(currentChar)) {
        lcd_insert_char(currentChar);
    }

    return 0;
}

// setup
void sh_lcd(int argc, char **argv) {
    draw_lcd();

    shell_register_callback(sh_lcd_callback);
}