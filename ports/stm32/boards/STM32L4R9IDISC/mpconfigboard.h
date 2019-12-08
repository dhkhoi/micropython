#define MICROPY_HW_BOARD_NAME "32L4R9I-DISCO"
#define MICROPY_HW_MCU_NAME "STM32L4R9AI"


#define MICROPY_HW_HAS_SWITCH (1)
#define MICROPY_HW_ENABLE_RNG (1)
#define MICROPY_HW_ENABLE_RTC (1)
#define MICROPY_HW_ENABLE_TIMER (1)
#define MICROPY_HW_ENABLE_USB (1)



// MSI is used and is 4MHz
// Resulting core frequency is 120 MHz:
#define MICROPY_HW_CLK_PLLM (1)
#define MICROPY_HW_CLK_PLLN (60)
#define MICROPY_HW_CLK_PLLP (RCC_PLLP_DIV5)
#define MICROPY_HW_CLK_PLLR (RCC_PLLR_DIV2)
#define MICROPY_HW_CLK_PLLQ (RCC_PLLQ_DIV2)
#define MICROPY_HW_FLASH_LATENCY FLASH_LATENCY_4


//the board has an external 32kHz crystal
#define MICROPY_HW_RTC_USE_LSE (1)


// USART config
#define MICROPY_HW_UART2_TX (pin_A2)
#define MICROPY_HW_UART2_RX (pin_A3)
// USART 2 is connected to the virtual com port on the ST-LINK
#define MICROPY_HW_UART_REPL PYB_UART_2
#define MICROPY_HW_UART_REPL_BAUD 115200


// I2C busses
#define MICROPY_HW_I2C1_SCL (pin_B6)
#define MICROPY_HW_I2C1_SDA (pin_G13)
#define MICROPY_HW_I2C3_SCL (pin_G7)
#define MICROPY_HW_I2C3_SDA (pin_G8)


// SPI busses
// ->to the arduino connector
#define MICROPY_HW_SPI2_NSS (pin_I0)
#define MICROPY_HW_SPI2_SCK (pin_B13)
#define MICROPY_HW_SPI2_MISO (pin_B14)
#define MICROPY_HW_SPI2_MOSI (pin_B15)



//Use Sel from joystick. Joystick is pulled low. Pressing the button makes the input go high
#define MICROPY_HW_USRSW_PIN (pin_C13)
#define MICROPY_HW_USRSW_PULL (GPIO_PULLDOWN)
#define MICROPY_HW_USRSW_EXTI_MODE (GPIO_MODE_IT_RISING)
#define MICROPY_HW_USRSW_PRESSED (1)


// LED (The green LED is controlled over MFX)
#define MICROPY_HW_LED1	(pin_B0)	// green
#define MICROPY_HW_LED_ON(pin) (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)	(mp_hal_pin_low(pin))

//USB config
#define MICROPY_HW_USB_FS (1)
#define MICROPY_HW_USB_OTG_ID_PIN (pin_A10)
