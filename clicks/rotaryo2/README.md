\mainpage Main Page

---
# Rotary O 2 Click

> Rotary O 2 Click is a compact add-on board that allows you to add a precision input knob to your design. This board features the TLC5925, a low-power 16-channel constant-current LED sink driver from Texas Instruments that, combined with a high-quality rotary encoder from ALPS, the EC12D1564402, allows you to add a precision input knob to your design. It also features an LED ring composed of 16 individual orange LEDs that can visually represent the encoder position and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rotaryo2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rotary-o-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Rotary O 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Rotary O 2 Click driver.

#### Standard key functions :

- `rotaryo2_cfg_setup` Config Object Initialization function.
```c
void rotaryo2_cfg_setup ( rotaryo2_cfg_t *cfg );
```

- `rotaryo2_init` Initialization function.
```c
err_t rotaryo2_init ( rotaryo2_t *ctx, rotaryo2_cfg_t *cfg );
```

- `rotaryo2_default_cfg` Click Default Configuration function.
```c
err_t rotaryo2_default_cfg ( rotaryo2_t *ctx );
```

#### Example key functions :

- `rotaryo2_set_led_pos` This function turns on the LED for the selected LED position.
```c
err_t rotaryo2_set_led_pos ( rotaryo2_t *ctx, uint8_t led_pos );
```

- `rotaryo2_set_led_data` This function, using SPI serial interface, writes a desired 16-bit data.
```c
err_t rotaryo2_set_led_data ( rotaryo2_t *ctx, uint16_t data_in );
```

- `rotaryo2_get_state_switch` This function return rotary encoder switch signal, states of the SW(INT).
```c
uint8_t rotaryo2_get_state_switch ( rotaryo2_t *ctx );
```

## Example Description

> This library contains the API for the Rotary O 2 Click driver 
> to control LEDs states and a rotary encoder position readings.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After the driver init, the app executes a default configuration and turn off all LEDs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryo2_cfg_t rotaryo2_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    rotaryo2_cfg_setup( &rotaryo2_cfg );
    ROTARYO2_MAP_MIKROBUS( rotaryo2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == rotaryo2_init( &rotaryo2, &rotaryo2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYO2_ERROR == rotaryo2_default_cfg ( &rotaryo2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Rotary O 2 Click board™.
> The demo example shows the functionality of a rotary encoder used to control LEDs.

```c
void application_task ( void )
{
    if ( ROTARYO2_OK == rotaryo2_set_led_data( &rotaryo2, led_data ) )
    {
        rotaryo2_switch_detection( );
        rotaryo2_encoder_mechanism( );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryO2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
