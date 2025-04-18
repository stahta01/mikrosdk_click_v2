
---
# TempHum 13 Click

> [TempHum 13 Click](https://www.mikroe.com/?pid_product=MIKROE-3635) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3635&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo shows basic TempHum13 Click functionality - temperature
and humidity measurement. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum13

### Example Key Functions

- `temphum13_cfg_setup` Config Object Initialization function. 
```c
void temphum13_cfg_setup ( temphum13_cfg_t *cfg );
``` 
 
- `temphum13_init` Initialization function. 
```c
err_t temphum13_init ( temphum13_t *ctx, temphum13_cfg_t *cfg );
```

- `temphum13_default_cfg` Click Default Configuration function. 
```c
void temphum13_default_cfg ( temphum13_t *ctx );
```

- `temphum13_get_humidity` This function calculates humidity. 
```c
float temphum13_get_humidity ( temphum13_t *ctx );
```

- `temphum13_get_temperature` This function calculates current temperature. 
```c
float temphum13_get_temperature ( temphum13_t *ctx );
```

- `temphum13_change_resolution` This function sets Click measurement resolution. 
```c
uint8_t temphum13_change_resolution ( temphum13_t *ctx, uint8_t measurement_resolution );
```

### Application Init

> Initialize device and driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum13_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum13_cfg_setup( &cfg );
    TEMPHUM13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum13_init( &temphum13, &cfg );
    temphum13_default_cfg( &temphum13 );
}
```

### Application Task

> Measure temperature and humidity values on every 0,5 seconds
and log them to UART Terminal if they are valid.

```c
void application_task ( void )
{
    temperature = temphum13_get_temperature( &temphum13 );
    humidity = temphum13_get_humidity( &temphum13 );
    
    if (temperature != 65536.0)
    {
        log_printf( &logger, "\r\n> Temperature : %.2f C", temperature );
    }

    if (humidity != 65536.0)
    {       
        log_printf( &logger, "\r\n> Humidity    : %.2f%%RH\r\n", humidity );
    } 

    Delay_ms ( 500 );
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
