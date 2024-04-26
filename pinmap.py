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
    'A2': ('ONE_BUTTON_PIN', Pin.button),
    'A3': ('TWO_BUTTON_PIN', Pin.button),
    'A4': None,
    'A5': ('GREEN_LED_PIN', Pin.led),
    'A6': ('YELLOW_LED_PIN', Pin.led),
    'A7': ('RED_LED_PIN', Pin.led),

    # port B
    'B0': ('KNOB_ONE_PIN', Pin.analog_in),
    'B1': ('KNOB_TWO_PIN', Pin.analog_in),
    'B2': None,
    'B3': None,
    'B4': None,
    'B5': None,

    # port C
    'C0': None,
    'C1': None,
    'C2': None,
    'C3': ('BARGRAPH_CLOCK_PIN', Pin.led),
    'C4': ('BARGRAPH_MISO_PIN', Pin.led),
    'C5': ('BARGRAPH_DATA_PIN', Pin.led),
    'C6': None,
    'C7': None,

    # port D
    'D0': None,
    'D1': None,
    'D2': ('LCD_TX_PIN', Pin.led),
    'D3': ('LCD_RX_PIN', Pin.uart_rx),
    'D4': None,
    'D5': ('RGB_1_LED_PIN', Pin.led),
    'D6': ('RGB_2_LED_PIN', Pin.led),
    'D7': ('RGB_3_LED_PIN', Pin.led),

    # port E
    'E0': ('BARGRAPH_STROBE_PIN', Pin.led),
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


development = {
    'B6': ('DEBUG_RX_PIN', Pin.uart_rx),
    'B7': ('DEBUG_TX_PIN', Pin.uart_tx),
}


release = {}