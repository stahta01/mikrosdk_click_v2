
---
# DigiVref Click

> [DigiVref Click](https://www.mikroe.com/?pid_product=MIKROE-3334) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3334&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app changes the reference output voltage. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiVref

### Example Key Functions

- `digivref_cfg_setup` Config Object Initialization function. 
```c
void digivref_cfg_setup ( digivref_cfg_t *cfg );
``` 
 
- `digivref_init` Initialization function. 
```c
err_t digivref_init ( digivref_t *ctx, digivref_cfg_t *cfg );
```

- `digivref_default_cfg` Click Default Configuration function. 
```c
void digivref_default_cfg ( digivref_t *ctx );
```

- `digivref_set_output_voltage` This function sets reference output voltage. 
```c
void digivref_set_output_voltage ( digivref_t *ctx, uint8_t v_ref );
```

### Application Init

> Initialization device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    digivref_cfg_t cfg;

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

    digivref_cfg_setup( &cfg );
    DIGIVREF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digivref_init( &digivref, &cfg );
}
```

### Application Task

> Changes the reference output voltage every 3 seconds.

```c
void application_task ( void )
{
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_4096mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage(  &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_1024mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
