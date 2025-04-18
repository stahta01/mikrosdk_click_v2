
---
# Opto 5 Click

> [Opto 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4476) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4476&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : dec 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Opto 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto5

### Example Key Functions

- `opto5_cfg_setup` Config Object Initialization function.
```c
void opto5_cfg_setup ( opto5_cfg_t *cfg );
```

- `opto5_init` Initialization function.
```c
err_t opto5_init ( opto5_t *ctx, opto5_cfg_t *cfg );
```

- `opto5_default_cfg` Click Default Configuration function.
```c
void opto5_default_cfg ( opto5_t *ctx );
```

- `opto5_pin_set` Opto 5 pin setting function.
```c
void opto5_pin_set ( opto5_t *ctx );
```

- `opto5_pin_clear` Opto 5 pin clearing function.
```c
void opto5_pin_clear ( opto5_t *ctx );
```

- `opto5_pin_toggle` Opto 5 pin toggling function.
```c
void opto5_pin_toggle ( opto5_t *ctx );
```

### Application Init

> Initialization of UART LOG and GPIO pin drivers.
The output of PWM is set to high so the optocoupler
is not triggered by default.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    opto5_cfg_t opto5_cfg;          /**< Click config object. */

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

    opto5_cfg_setup( &opto5_cfg );
    OPTO5_MAP_MIKROBUS( opto5_cfg, MIKROBUS_1 );
    if ( opto5_init( &opto5, &opto5_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    opto5_default_cfg ( &opto5 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The output pin is toggled every 5 seconds. 

```c
void application_task ( void ) 
{
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Pin toggling...\r\n" );
    opto5_pin_toggle( &opto5 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
