
---
# DIGI POT 13 Click

> [DIGI POT 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5683) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5683&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for DIGI POT 13 Click driver.
> The demo application uses a digital potentiometer 
> to change the resistance values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT13

### Example Key Functions

- `digipot13_cfg_setup` Config Object Initialization function.
```c
void digipot13_cfg_setup ( digipot13_cfg_t *cfg );
```

- `digipot13_init` Initialization function.
```c
err_t digipot13_init ( digipot13_t *ctx, digipot13_cfg_t *cfg );
```

- `digipot13_default_cfg` Click Default Configuration function.
```c
err_t digipot13_default_cfg ( digipot13_t *ctx );
```

- `digipot13_set_resistance` DIGI POT 13 set the resistance function.
```c
err_t digipot13_set_resistance ( digipot13_t *ctx, digipot13_cfg_res_t cfg_res, float res_kohm );
```

- `digipot13_set_wiper_pos` DIGI POT 13 set the wiper position function.
```c
err_t digipot13_set_wiper_pos ( digipot13_t *ctx, uint8_t wiper_pos );
```

- `digipot13_write_data` DIGI POT 13 write data function.
```c
err_t digipot13_write_data ( digipot13_t *ctx, uint8_t cmd, uint8_t data_in );
```

### Application Init

> The initialization of I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot13_cfg_t digipot13_cfg;  /**< Click config object. */

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
    digipot13_cfg_setup( &digipot13_cfg );
    DIGIPOT13_MAP_MIKROBUS( digipot13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot13_init( &digipot13, &digipot13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT13_ERROR == digipot13_default_cfg ( &digipot13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the DIGI POT 13 Click board&trade;.
> The demo application iterates through the entire wiper range and 
> sets the resistance in steps of approximately 50 kOhm.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t res_kohm = DIGIPOT13_RES_0_KOHM; res_kohm <= DIGIPOT13_RES_200_KOHM; res_kohm += DIGIPOT13_RES_50_KOHM )
    {
        if ( DIGIPOT13_OK == digipot13_set_resistance( &digipot13, DIGIPOT13_CFG_RES_WH, ( float ) res_kohm ) )
        {
            log_printf( &logger, " Resistance: %.1f kOhm\r\n", ( float ) res_kohm );
            log_printf( &logger, " ----------------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
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
