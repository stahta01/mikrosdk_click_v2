
---
# Vibro Motor 4 Click

> [Vibro Motor 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4825) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4825&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Vibro Motor 4 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers and PWM module.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VibroMotor4

### Example Key Functions

- `vibromotor4_cfg_setup` Config Object Initialization function.
```c
void vibromotor4_cfg_setup ( vibromotor4_cfg_t *cfg );
```

- `vibromotor4_init` Initialization function.
```c
err_t vibromotor4_init ( vibromotor4_t *ctx, vibromotor4_cfg_t *cfg );
```

- `vibromotor4_default_cfg` Click Default Configuration function.
```c
err_t vibromotor4_default_cfg ( vibromotor4_t *ctx );
```

- `vibromotor4_set_mode` Vibro Motor 4 sets the desired mode function.
```c
err_t vibromotor4_set_mode ( vibromotor4_t *ctx, uint8_t mode_sel );
```

- `vibromotor4_set_duty_cycle` Vibro Motor 4 sets PWM duty cycle.
```c
err_t vibromotor4_set_duty_cycle ( vibromotor4_t *ctx, float duty_cycle );
```

- `vibromotor4_pwm_start` Vibro Motor 4 start PWM module.
```c
err_t vibromotor4_pwm_start ( vibromotor4_t *ctx );
```

### Application Init

> The initialization of I2C and PWM module, log UART, and additional pins. 
> After successful driver init, executes a default configuration
> and configures Vibro Motor 4 Click board&trade;.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    vibromotor4_cfg_t vibromotor4_cfg;  /**< Click config object. */

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
    vibromotor4_cfg_setup( &vibromotor4_cfg );
    VIBROMOTOR4_MAP_MIKROBUS( vibromotor4_cfg, MIKROBUS_1 );
    err_t init_flag = vibromotor4_init( &vibromotor4, &vibromotor4_cfg );
    if ( I2C_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vibromotor4_enable( &vibromotor4, VIBROMOTOR4_PROPERTY_ENABLE );
    Delay_ms ( 100 );

    vibromotor4_soft_rst( &vibromotor4 );
    Delay_ms ( 100 );

    vibromotor4_default_cfg ( &vibromotor4 );
    Delay_ms ( 100 );

    vibromotor4_set_duty_cycle( &vibromotor4, 0.0 );
    Delay_ms ( 100 );

    vibromotor4_pwm_start( &vibromotor4 );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of Vibro Motor 4 Click board&trade;.
> Changing duty cycle results in different vibrations.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 0;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    vibromotor4_set_duty_cycle ( &vibromotor4, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );

    Delay_ms ( 1000 );

    if ( 5 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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
