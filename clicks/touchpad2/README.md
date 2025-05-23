
---
# TouchPad 2 Click

> [TouchPad 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4594) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4594&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the TouchPad 2 Click driver.
> The library contains drivers to get touch details,
> the number of touches, X and Y coordinates and touch strength.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchPad2

### Example Key Functions

- `touchpad2_cfg_setup` Config Object Initialization function.
```c
void touchpad2_cfg_setup ( touchpad2_cfg_t *cfg );
```

- `touchpad2_init` Initialization function.
```c
err_t touchpad2_init ( touchpad2_t *ctx, touchpad2_cfg_t *cfg );
```

- `touchpad2_default_cfg` Click Default Configuration function.
```c
void touchpad2_default_cfg ( touchpad2_t *ctx );
```

- `touchpad2_check_version` TouchPad 2 check version function.
```c
err_t touchpad2_check_version ( touchpad2_t *ctx, touchpad2_ver_info_t *ver_info );
```

- `touchpad2_get_touch` TouchPad 2 get touch function.
```c
err_t touchpad2_get_touch ( touchpad2_t *ctx, touchpad2_touch_t *touch_data );
```

### Application Init

> Initializes I2C driver, check communication and reads device version information.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    touchpad2_cfg_t touchpad2_cfg;  /**< Click config object. */

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

    touchpad2_cfg_setup( &touchpad2_cfg );
    TOUCHPAD2_MAP_MIKROBUS( touchpad2_cfg, MIKROBUS_1 );
    err_t init_flag = touchpad2_init( &touchpad2, &touchpad2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    touchpad2_default_cfg ( &touchpad2 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    
    touchpad2_check_version( &touchpad2, &ver_info );
    Delay_ms ( 100 );
    
    if ( ver_info.product_num != TOUCHPAD2_IQS525_PRODUCT_NUMBER ) {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, " Product number : %u \r\n", ver_info.product_num );
    log_printf( &logger, " Project number : %u \r\n", ver_info.projec_num );
    log_printf( &logger, " Version        : %.1f \r\n", ver_info.version );
    log_printf( &logger, " HW ID          : %u \r\n", ver_info.hw_id );
    log_printf( &logger, " HW Revision    : %u \r\n", ver_info.hw_revision );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Waiting for a new touch\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the TouchPad 2 Click board. 
> Read XY data consisting of a status byte, the number of touches,
> X and Y coordinates and touch strength data. 
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
   
    touchpad2_wait_ready( &touchpad2 );
    
    touchpad2_get_touch ( &touchpad2, &touch_data );
    Delay_ms ( 100 );
    
    if ( ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_1 ) || 
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_2 ) ||
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_3 ) ||
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_4 ) ||
         ( touch_data.id_tag == TOUCHPAD2_ID_TAG_TOUCH_5 ) ) {
        log_printf( &logger, "  Number of touches : %d \r\n", ( uint16_t ) touch_data.no_of_fingers );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  Coordinate X = %d \r\n", touch_data.x_pos );
        log_printf( &logger, "  Coordinate Y = %d \r\n", touch_data.y_pos );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  Touch Strength   : %u  \r\n", ( uint16_t ) touch_data.touch_str );
        log_printf( &logger, "------------------------ \r\n" );
        Delay_ms ( 500 );    
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
