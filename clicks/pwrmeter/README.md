
---
# PWR Meter Click

> [PWR Meter Click](https://www.mikroe.com/?pid_product=MIKROE-3150) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3150&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This Click is capable of measuring voltage and current through the load, connected to either 
> AC or DC power source. It is used to calculate all the measurement parameters, returning 
> values of multiple power parameters directly, over the UART interface, reducing the processing 
> load on the host MCU. These parameters include active, reactive, and apparent power, current 
> and voltage RMS, line frequency, and power factor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PwrMeter

### Example Key Functions

- `pwrmeter_cfg_setup` Config Object Initialization function. 
```c
void pwrmeter_cfg_setup ( pwrmeter_cfg_t *cfg );
``` 
 
- `pwrmeter_init` Initialization function. 
```c
err_t pwrmeter_init ( pwrmeter_t *ctx, pwrmeter_cfg_t *cfg );
```

- `pwrmeter_read_reg_word` Function reads 16-bit data from the desired register. 
```c
err_t pwrmeter_read_reg_word ( pwrmeter_t *ctx, uint16_t register_addr, uint16_t *data_out );
```
 
- `pwrmeter_read_reg_dword` Function reads 32-bit data from the desired register. 
```c
err_t pwrmeter_read_reg_dword ( pwrmeter_t *ctx, uint16_t register_addr, uint32_t *data_out );
```

- `pwrmeter_read_reg_signed` Function reads signed 16bit or 32bit data from the desired register. 
```c
err_t pwrmeter_read_reg_signed ( pwrmeter_t *ctx, uint16_t register_addr, uint8_t data_mode, int32_t *data_out );
```

### Application Init

> Initializes UART interface, puts output of regulator in active state and
> configures gain channel and uart baud rate.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pwrmeter_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    pwrmeter_cfg_setup( &cfg );
    PWRMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwrmeter_init( &pwrmeter, &cfg );
    Delay_ms ( 500 );
    
    pwrmeter_enable( &pwrmeter, PWRMETER_ENABLE );
    Delay_ms ( 100 );
    
    response_byte = pwrmeter_write_reg_dword ( &pwrmeter, PWRMETER_SYS_CONFIG_REG, PWRMETER_VOLT_GAIN_1 | PWRMETER_CURR_GAIN_8 | PWRMETER_UART_BR_9600 );
    check_response( );
    response_byte = pwrmeter_send_command( &pwrmeter, PWRMETER_SAVE_TO_FLASH_COMM );
    check_response( );

    log_printf( &logger, "PWR Meter is initialized\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads voltage, current and power measurements from data registers, then converts this values
> to determined units and logs all results on uart terminal each second.

```c
void application_task ( void )
{
    response_byte = pwrmeter_read_reg_word( &pwrmeter, PWRMETER_VOLT_RMS_REG, &voltage_rms );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_CURR_RMS_REG, &current_rms );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_ACTIVE_PWR_REG, &active_power );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_REACTIVE_PWR_REG, &reactive_power );
    check_response( );
    response_byte = pwrmeter_read_reg_dword( &pwrmeter, PWRMETER_APPARENT_PWR_REG, &apparent_power );
    check_response( );
    response_byte = pwrmeter_read_reg_signed( &pwrmeter, PWRMETER_PWR_FACTOR_REG, PWRMETER_16BIT_DATA, &power_factor );
    check_response( );
    
    meas_data[ 0 ] = ( float ) voltage_rms / 100;
    meas_data[ 1 ] = ( float ) current_rms / 1000;
    meas_data[ 2 ] = ( float ) active_power / 100000;
    meas_data[ 3 ] = ( float ) reactive_power / 100000;
    meas_data[ 4 ] = ( float ) apparent_power / 100000;
    meas_data[ 5 ] = ( float ) power_factor / 32767;
    
    response_byte = pwrmeter_get_status( &pwrmeter, &status_byte );
    check_response( );
    
    if ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0 )
    {
        log_printf( &logger, "DC mode\r\n" );
    }
    else
    {
        log_printf( &logger, "AC mode\r\n" );
    }
    

    log_printf( &logger, "RMS voltage:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0) && ( ( status_byte & PWRMETER_DCVOLT_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ V ]\r\n", meas_data[ 0 ] );
    
    
    log_printf( &logger, "RMS current:  " );
    if ( ( ( status_byte & PWRMETER_DCMODE_MASK ) != 0 ) && ( ( status_byte & PWRMETER_DCCURR_SIGN_MASK ) == 0 ) )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ mA ]\r\n", meas_data[ 1 ] );
    
    
    log_printf( &logger, "Active power:  " );
    if ( ( status_byte & PWRMETER_PA_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ W ]\r\n", meas_data[ 2 ] );
    
    
    log_printf( &logger, "Reactive power:  " );
    if ( ( status_byte & PWRMETER_PR_SIGN_MASK ) == 0 )
    {
        log_printf( &logger, "-" );
    }
    log_printf( &logger, "%.2f[ VAr ]\r\n", meas_data[ 3 ] );
    
   
    log_printf( &logger, "Apparent power:  " );
    log_printf( &logger, "%.2f[ VA ]\r\n", meas_data[ 4 ] );

    
    log_printf( &logger, "Power factor:  %.2f\r\n", meas_data[ 5 ] );
    log_printf( &logger, "-----------------------------------\r\n" );
    
    Delay_ms ( 1000 );
}
```

### Note

> Do not apply higher voltage than 60V to this board! This Click is designed for lower voltage 
> monitoring and evaluation of the MCP39F511A and its basic functionalities. 

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
