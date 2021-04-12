class Pin:
    # possible tags
    tags = [
        'input',
        'output',
        'tristate',
        'gpio',
        'analog',
        'pullup',
        'button',
    ]

    # shortcuts
    button = ['input', 'gpio', 'button']
    relay = ['output', 'gpio', 'tristate']
    led = ['output', 'gpio']
    uart_tx = ['output', 'pps']
    uart_rx = ['input', 'pps']
    analog_in = ['input', 'analog']


common = {
    # port A
    'A0': None,
    'A1': None,
    'A2': None,
    'A3': None,
    'A4': None,
    'A5': None,
    'A6': None,
    'A7': None,

    # port B
    'B0': None,
    'B1': None,
    'B2': None,
    'B3': None,
    'B4': None,
    'B5': None,
    'B6': ('DEBUG_RX_PIN', Pin.uart_rx),
    'B7': ('DEBUG_TX_PIN', Pin.uart_tx),

    # port C
    'C0': None,
    'C1': None,
    'C2': None,
    'C3': ('GREEN_LED_PIN', Pin.led),
    'C4': ('RGB_1_LED_PIN', Pin.led),
    'C5': ('RGB_2_LED_PIN', Pin.led),
    'C6': ('RGB_3_LED_PIN', Pin.led),
    'C7': None,

    # port D
    'D0': ('YELLOW_LED_PIN', Pin.led),
    'D1': ('RED_LED_PIN', Pin.led),
    'D2': ('LCD_TX_PIN', Pin.led),
    'D3': ('LCD_RX_PIN', Pin.uart_rx),
    'D4': None,
    'D5': None,
    'D6': None,
    'D7': None,

    # port E
    'E0': None,
    'E1': None,
    'E2': None,
    'E3': None,

    # port F
    'F0': None,
    'F1': None,
    'F2': None,
    'F3': None,
    'F4': None,
    'F5': None,
    'F6': ('USB_TX_PIN', Pin.uart_tx),
    'F7': ('USB_RX_PIN', Pin.uart_rx),
}


# Frequency counter, C7, and C8 are on the VPP, ICSPCLK, and ICSPDAT pins and need to be moved
# Debug UART pins are not present in release mode


development = {}


release = {}