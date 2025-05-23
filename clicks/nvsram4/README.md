
---
# nvSRAM 4 Click

> [nvSRAM 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4482) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4482&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the nvSRAM 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.nvSRAM4

### Example Key Functions

- `nvsram4_cfg_setup` Config Object Initialization function.
```c
void nvsram4_cfg_setup ( nvsram4_cfg_t *cfg );
```

- `nvsram4_init` Initialization function.
```c
err_t nvsram4_init ( nvsram4_t *ctx, nvsram4_cfg_t *cfg );
```

- `nvsram4_default_cfg` Click Default Configuration function.
```c
void nvsram4_default_cfg ( nvsram4_t *ctx );
```

- `nvsram4_burst_read_memory` nvSRAM 4 burst read memory function.
```c
err_t nvsram4_burst_read_memory ( nvsram4_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t n_bytes );
```

- `nvsram4_burst_write_memory` nvSRAM 4 burst write memory function.
```c
err_t nvsram4_burst_write_memory ( nvsram4_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t n_bytes );
```

- `nvsram4_get_rtc_time` nvSRAM 4 get RTC time function.
```c
void nvsram4_get_rtc_time ( nvsram4_t *ctx, nvsram4_rtc_time_t *rtc_time );
```

### Application Init

> Initialization driver enables - SPI, 
> write demo_data string ( mikroE ), starting from the selected memory_addr ( 112233 ), 
> set the time to 12:30:31 and set the date to 31-12-20.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;           /**< Logger config object. */
    nvsram4_cfg_t nvsram4_cfg;   /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    nvsram4_cfg_setup( &nvsram4_cfg );
    NVSRAM4_MAP_MIKROBUS( nvsram4_cfg, MIKROBUS_1 );
    err_t init_flag  = nvsram4_init( &nvsram4, &nvsram4_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    nvsram4_default_cfg ( &nvsram4 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     nvSRAM 4 Click    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    memory_addr = 112233;
    
    nvsram4_set_cmd( &nvsram4, NVSRAM4_STATUS_WREN );
    Delay_ms ( 100 );
    
    log_printf( &logger, "  Write data : %s", demo_data );
    nvsram4_burst_write_memory( &nvsram4, memory_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    
    date.day_of_week = 4;
    date.day = 31;
    date.month = 12;
    date.year = 20;
    nvsram4_set_rtc_date( &nvsram4, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    nvsram4_set_rtc_time( &nvsram4, time );
    Delay_ms ( 100 );
}
```

### Application Task

> In this example, we read a data string, which we have previously written to memory, 
> starting from the selected memory_addr ( 112233 ) 
> and read and display the current time and date, which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.

```c
void application_task ( void ) 
{
    nvsram4_get_rtc_time( &nvsram4, &time );
    Delay_ms ( 1 );
    nvsram4_get_rtc_date( &nvsram4, &date );
    Delay_ms ( 1 );
    
    if ( time.sec != new_sec ) {
        log_printf( &logger, "  Date      : %.2d-%.2d-%.2d\r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, "  Time      : %.2d:%.2d:%.2d\r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "- - - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        Delay_ms ( 10 );
        
        if ( date.year != c_year ) {
            log_printf( &logger, "     Happy New Year    \r\n" );
            c_year = date.year;
            Delay_ms ( 10 );
        } else {
            nvsram4_burst_read_memory( &nvsram4, memory_addr, &rx_data[ 0 ], 9 );
            log_printf( &logger, "  Read data : %s", rx_data );    
        }
               
        log_printf( &logger, "-----------------------\r\n" );
    } else {
        Delay_ms ( 1 );    
    }
}
```

### Note

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
