
---
# H BRIDGE 2 Click

> [H-Bridge 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3000) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3000&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application controls the speed and direction of motor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge2

### Example Key Functions

- `hbridge2_cfg_setup` Config Object Initialization function. 
```c
void hbridge2_cfg_setup ( hbridge2_cfg_t *cfg );
``` 
 
- `hbridge2_init` Initialization function. 
```c
err_t hbridge2_init ( hbridge2_t *ctx, hbridge2_cfg_t *cfg );
```

- `hbridge2_set_output` Output Set function. 
```c
uint8_t hbridge2_set_output ( hbridge2_t *ctx, uint8_t out_state );
```
 
- `hbridge2_enable` Enable function. 
```c
void hbridge2_enable ( hbridge2_t *ctx, uint8_t state );
```

- `hbridge2_set_gout` GOUT Set function. 
```c
void hbridge2_set_gout ( hbridge2_t *ctx, uint8_t state );
```

### Application Init

> Initializes GPIO driver and puts the device to enable state, and the GPIO pin to logic high state.


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    hbridge2_cfg_setup( &cfg );
    HBRIDGE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge2_init( &hbridge2, &cfg );

    hbridge2_enable( &hbridge2, HBRIDGE2_ENABLE );
    hbridge2_set_gout( &hbridge2, HBRIDGE2_GOUT_HIGH );
    log_printf( &logger, "H-Bridge 2 is intialized\r\n" );
    Delay_ms ( 200 );
}
```

### Application Task

> Demonstrates the control of output pins by put output pins to different states. The outputs be changed after every 3 seconds.

```c
void application_task ( void )
{
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_H_OUT2_L );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_L_OUT2_H );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_Z_OUT2_Z );
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
