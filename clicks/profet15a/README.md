
---
# PROFET 15A Click

> [PROFET 15A Click](https://www.mikroe.com/?pid_product=MIKROE-4701) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4701&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example showcases the ability of the PROFET 15A Click board.
It configures Host MCU for communication and then enables 
and disables output channel. Besides that, it reads the voltage 
of IS pin and calculates current on output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PROFET15A

### Example Key Functions

- `profet15a_cfg_setup` Config Object Initialization function.
```c
void profet15a_cfg_setup ( profet15a_cfg_t *cfg );
```

- `profet15a_init` Initialization function.
```c
err_t profet15a_init ( profet15a_t *ctx, profet15a_cfg_t *cfg );
```

- `profet15a_read_an_pin_voltage` PROFET 15A read AN pin voltage level function.
```c
err_t profet15a_read_an_pin_voltage ( profet15a_t *ctx, float *data_out );
```

- `profet15a_set_mode` PROFET 15A set mode.
```c
err_t profet15a_set_mode ( profet15a_t *ctx, uint8_t mode );
```

### Application Init

> Initialization of the communication modules(ADC and UART) 
and additional pins for controlling the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    profet15a_cfg_t profet15a_cfg;  /**< Click config object. */

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
    profet15a_cfg_setup( &profet15a_cfg );
    PROFET15A_MAP_MIKROBUS( profet15a_cfg, MIKROBUS_1 );
    if ( profet15a_init( &profet15a, &profet15a_cfg ) == ADC_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    
    profet15a_set_mode( &profet15a, PROFET15A_DIAGNOSTIC_ON );
    Delay_ms ( 1000 );
}
```

### Application Task

> On every iteration of the task device switches between 
DIAGNOSTIC and OFF mode while it reads the voltage of IS pin 
and with that calculates current on output.

```c
void application_task ( void )
{
    static uint8_t mode = PROFET15A_DIAGNOSTIC_ON;
    float profet15a_an_voltage = 0;
    
    profet15a_set_mode( &profet15a, mode );
    
    if ( PROFET15A_DIAGNOSTIC_ON == profet15a.mode )
    {
        mode = PROFET15A_MODE_OFF;
        log_printf( &logger, " > Output ON diagnostic mode\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        mode = PROFET15A_DIAGNOSTIC_ON;
        log_printf( &logger, " > Output OFF\r\n" );
    }

    if ( profet15a_read_an_pin_voltage ( &profet15a, &profet15a_an_voltage ) != ADC_ERROR )
    {
        log_printf( &logger, " > IS Voltage \t~ %.3f[V]\r\n", profet15a_an_voltage );
        
        float current = profet15a_an_voltage * profet15a.kilis / profet15a.rsens;
        log_printf( &logger, " > OUT Current \t~ %.3f[A]\r\n", current );
    }  
    
    log_printf( &logger, "*******************************************\r\n" );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Formula for calculating current on load: 
I_load = voltage(IS) x kILIS / 1.2 kΩ

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
