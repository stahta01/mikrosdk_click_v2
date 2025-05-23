
---
# FAN 8 Click

> [FAN 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4824) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4824&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of FAN 8 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.FAN8

### Example Key Functions

- `fan8_cfg_setup` Config Object Initialization function.
```c
void fan8_cfg_setup ( fan8_cfg_t *cfg );
```

- `fan8_init` Initialization function.
```c
err_t fan8_init ( fan8_t *ctx, fan8_cfg_t *cfg );
```

- `fan8_default_cfg` Click Default Configuration function.
```c
err_t fan8_default_cfg ( fan8_t *ctx );
```

- `fan8_set_duty_cycle` This function sets the duty cycle of the selected fan channel and waits until the duty cycle is set at the PWM output.
```c
err_t fan8_set_duty_cycle ( fan8_t *ctx, uint8_t fan_ch, uint8_t duty_cycle );
```

- `fan8_measure_rpm` This function measures the RPM of the selected fan channel.
```c
err_t fan8_measure_rpm ( fan8_t *ctx, uint8_t fan_ch, uint8_t num_pulses, uint16_t *fan_rpm );
```

- `fan8_read_temperature` This function reads the temperature from the thermistor attached to the selected temperature channel.
```c
err_t fan8_read_temperature ( fan8_t *ctx, uint8_t temp_ch, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    fan8_cfg_t fan8_cfg;  /**< Click config object. */

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
    fan8_cfg_setup( &fan8_cfg );
    FAN8_MAP_MIKROBUS( fan8_cfg, MIKROBUS_1 );
    err_t init_flag = fan8_init( &fan8, &fan8_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = fan8_default_cfg ( &fan8 );
    if ( FAN8_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the speed of fans at both channels by changing the PWM duty cycle, then calculates 
> the fans RPM from measured tachometer signal. It also reads the temperature of two thermistors.
> The results are being displayed to the USB UART where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t duty_cnt = FAN8_MIN_DUTY_CYCLE;
    static int8_t duty_inc = FAN8_DUTY_CYCLE_STEP_10;
    uint16_t fan_rpm = 0;
    float temperature = 0;
    
    if ( duty_cnt == FAN8_MAX_DUTY_CYCLE )
    {
        duty_inc = -FAN8_DUTY_CYCLE_STEP_10;
    }
    else if ( duty_cnt == ( FAN8_MIN_DUTY_CYCLE + FAN8_DUTY_CYCLE_STEP_10 ) )
    {
        duty_inc = FAN8_DUTY_CYCLE_STEP_10;
    }
    duty_cnt += duty_inc;
        
    log_printf( &logger, " - Channel 1 values -\r\n" );
    fan8_set_duty_cycle ( &fan8, FAN8_FAN_CHANNEL_1, duty_cnt );
    log_printf( &logger, " PWM Duty Cycle : %d\r\n", ( uint16_t ) duty_cnt );
    fan8_measure_rpm ( &fan8, FAN8_FAN_CHANNEL_1, FAN8_2_PULSES_PER_REVOLUTION, &fan_rpm );
    log_printf( &logger, " Last measured fan RPM : %u\r\n", fan_rpm );
    fan8_read_temperature ( &fan8, FAN8_TEMP_CHANNEL_1, &temperature );
    log_printf( &logger, " Temperature : %.2f C\r\n\r\n", temperature );
    
    log_printf( &logger, " - Channel 2 values -\r\n" );
    fan8_set_duty_cycle ( &fan8, FAN8_FAN_CHANNEL_2, duty_cnt );
    log_printf( &logger, " PWM Duty Cycle : %d\r\n", ( uint16_t ) duty_cnt );
    fan8_measure_rpm ( &fan8, FAN8_FAN_CHANNEL_2, FAN8_2_PULSES_PER_REVOLUTION, &fan_rpm );
    log_printf( &logger, " Last measured fan RPM : %u\r\n", fan_rpm );
    fan8_read_temperature ( &fan8, FAN8_TEMP_CHANNEL_2, &temperature );
    log_printf( &logger, " Temperature : %.2f C\r\n\r\n", temperature );
    
    if ( !fan8_check_fault_indicator ( &fan8 ) )
    {
        log_printf( &logger, " Fault detected!\r\n\r\n", temperature );
    }
    
    Delay_ms ( 500 );
}
```

### Note

> The MAX6615 measures the tachometer signal every 67s, therefore 
> the fan RPM value will be updated once per 67s.
> An NTC 10K3 thermistor is required for proper temperature measurements.

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
