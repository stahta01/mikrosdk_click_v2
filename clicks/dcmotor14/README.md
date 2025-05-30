
---
# DC Motor 14 Click

> [DC Motor 14 Click](https://www.mikroe.com/?pid_product=MIKROE-3982) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3982&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 14 Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dcmotor14

### Example Key Functions

- `dcmotor14_cfg_setup` Config Object Initialization function. 
```c
void dcmotor14_cfg_setup ( dcmotor14_cfg_t *cfg );
``` 
 
- `dcmotor14_init` Initialization function. 
```c
err_t dcmotor14_init ( dcmotor14_t *ctx, dcmotor14_cfg_t *cfg );
```

- `dcmotor14_forward` This functio is used to drive the motor forward. 
```c
void dcmotor14_forward ( dcmotor14_t *ctx );
```
 
- `` This functio is used to drive the motor in reverse. 
```c
dcmotor14_reverse  ( dcmotor14_t *ctx );
```

- `` This functio is used to brake the motor. 
```c
dcmotor14_brake  ( dcmotor14_t *ctx );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor14_cfg_t cfg;

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

    dcmotor14_cfg_setup( &cfg );
    DCMOTOR14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor14_init( &dcmotor14, &cfg );
}
```

### Application Task

> Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
> and after that drives it in the reverse direction for 5 seconds, and finally, 
> disconnects the motor for 2 seconds. Each step will be logged on the USB UART where
> you can track the program flow.

```c
void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    dcmotor14_forward( &dcmotor14 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Pull brake! \r\n" );
    dcmotor14_brake( &dcmotor14 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor turns in reverse! \r\n" );
    dcmotor14_reverse( &dcmotor14 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor is disconnected (High-Z)!  \r\n" );
    dcmotor14_stop( &dcmotor14 );
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
