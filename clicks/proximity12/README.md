
---
# Proximity 12 Click

> [Proximity 12 Click](https://www.mikroe.com/?pid_product=MIKROE-3995) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3995&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This function demonstrates the use of Proximity 12 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity12

### Example Key Functions

- `proximity12_cfg_setup` Config Object Initialization function.
```c
void proximity12_cfg_setup ( proximity12_cfg_t *cfg );
```

- `proximity12_init` Initialization function.
```c
err_t proximity12_init ( proximity12_t *ctx, proximity12_cfg_t *cfg );
```

- `proximity12_default_cfg` Click Default Configuration function.
```c
err_t proximity12_default_cfg ( proximity12_t *ctx );
```

- `proximity12_read_proximity` This function reads the raw proximity value measured by the Click board.
```c
err_t proximity12_read_proximity ( proximity12_t *ctx, uint16_t *prox_data );
```

- `proximity12_read_als` This function reads all als data measured by the Click board.
```c
err_t proximity12_read_als ( proximity12_t *ctx, proximity12_als_data_t *als );
```

- `proximity12_set_led_isink` This function sets the LEDs sink scaler and current values.
```c
err_t proximity12_set_led_isink ( proximity12_t *ctx, uint8_t scaler, uint8_t current );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proximity12_cfg_t proximity12_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    proximity12_cfg_setup( &proximity12_cfg );
    PROXIMITY12_MAP_MIKROBUS( proximity12_cfg, MIKROBUS_1 );
    err_t init_flag = proximity12_init( &proximity12, &proximity12_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    init_flag = proximity12_default_cfg ( &proximity12 );
    if ( PROXIMITY12_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Cfg Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity and ALS values and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    uint16_t prox_data = 0;
    proximity12_als_data_t als;
    err_t error_flag = proximity12_read_proximity ( &proximity12, &prox_data );
    error_flag |= proximity12_read_als ( &proximity12, &als );

    if ( PROXIMITY12_OK == error_flag )
    {
        log_printf( &logger, " - Proximity data -\r\n" );
        log_printf( &logger, " Proximity: %u\r\n", prox_data );
        log_printf( &logger, " - ALS data -\r\n" );
        log_printf( &logger, " Clear: %lu - Red: %lu - Green: %lu - Blue: %lu\r\n", als.clear,
                                                                                    als.red,
                                                                                    als.green, 
                                                                                    als.blue );
        
        log_printf( &logger, " Leakage: %lu - Wideband: %lu - IR1: %lu - IR2: %lu\r\n\r\n", als.leakage,
                                                                                            als.wideband,
                                                                                            als.ir1, 
                                                                                            als.ir2 );
    }
    Delay_ms ( 100 );
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
