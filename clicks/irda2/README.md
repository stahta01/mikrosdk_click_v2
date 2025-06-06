
---
# IrDA 2 Click

> [IrDA 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1195) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1195&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an IrDA 2 Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDA2

### Example Key Functions

- `irda2_cfg_setup` Config Object Initialization function.
```c
void irda2_cfg_setup ( irda2_cfg_t *cfg );
```

- `irda2_init` Initialization function.
```c
err_t irda2_init ( irda2_t *ctx, irda2_cfg_t *cfg );
```

- `irda2_default_cfg` Click Default Configuration function.
```c
void irda2_default_cfg ( irda2_t *ctx );
```

- `irda2_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t irda2_generic_write ( irda2_t *ctx, uint8_t *data_in, uint16_t len )
```

- `irda2_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t irda2_generic_read ( irda2_t *ctx, uint8_t *data_out, uint16_t len );
```

- `irda2_reset` This function executes a device reset operation.
```c
void irda2_reset( irda2_t *ctx );
```

### Application Init

> Initalizes device and makes an initial log.

```c
void application_init( void ) 
{
    irda2_cfg_t irda2_cfg;
    log_cfg_t logger_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    log_info( &logger, " Application Init " );
    
    //  Click initialization.
    irda2_cfg_setup( &irda2_cfg );
    IRDA2_MAP_MIKROBUS( irda2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irda2_init( &irda2, &irda2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    irda2_default_cfg( &irda2 );
    irda2_reset( &irda2 );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired text message once per second.

```c
void application_task( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    irda2_generic_write( &irda2, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == irda2_generic_read( &irda2, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
    }
#endif
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
