
---
# GNSS 11 Click

> [GNSS 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5902) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5902&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART/I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 11 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS11

### Example Key Functions

- `gnss11_cfg_setup` Config Object Initialization function.
```c
void gnss11_cfg_setup ( gnss11_cfg_t *cfg );
```

- `gnss11_init` Initialization function.
```c
err_t gnss11_init ( gnss11_t *ctx, gnss11_cfg_t *cfg );
```

- `gnss11_reset_device` This function resets the device by toggling the RST and ANT_ON pins.
```c
void gnss11_reset_device ( gnss11_t *ctx );
```

- `gnss11_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gnss11_generic_read ( gnss11_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnss11_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnss11_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss11_cfg_t gnss11_cfg;  /**< Click config object. */

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
    gnss11_cfg_setup( &gnss11_cfg );
    GNSS11_MAP_MIKROBUS( gnss11_cfg, MIKROBUS_1 );
    if ( GNSS11_OK != gnss11_init( &gnss11, &gnss11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss11_reset_device ( &gnss11 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    gnss11_process( &gnss11 );
    if ( app_buf_len > ( sizeof ( GNSS11_RSP_GGA ) + GNSS11_GGA_ELEMENT_SIZE ) ) 
    {
        gnss11_parser_application( app_buf );
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
