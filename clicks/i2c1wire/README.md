
---
# I2C 1 Wire Click

> [I2C 1-Wire Click](https://www.mikroe.com/?pid_product=MIKROE-1892) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1892&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to initialize, confiure and use the I2C 1-Wire Click. The Click
  is a I2C (host) to 1-Wire interface (slave). In order for the example to work one or more 
  1-Wire (GPIO) Click modules are required. Gnd goes to gnd, power goes to power and the cha-
  nnels are there to read data from connected modules.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2C1Wire

### Example Key Functions

- `i2c1wire_cfg_setup` Config Object Initialization function.
```c
void i2c1wire_cfg_setup ( i2c1wire_cfg_t *cfg ); 
```

- `i2c1wire_init` Initialization function.
```c
err_t i2c1wire_init ( i2c1wire_t *ctx, i2c1wire_cfg_t *cfg );
```

- `i2c1wire_write_byte_one_wire` This function writes one byte to the Click module.
```c
void i2c1wire_write_byte_one_wire ( i2c1wire_t *ctx, uint8_t input );
```

- `i2c1wire_read_byte_one_wire` This function reads one byte from the Click module.
```c
uint8_t i2c1wire_read_byte_one_wire ( i2c1wire_t *ctx );
```

- `i2c1wire_one_wire_reset` This function does a hardware reset of the Click module.
```c
void i2c1wire_one_wire_reset ( i2c1wire_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    i2c1wire_cfg_t cfg;

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
    i2c1wire_cfg_setup( &cfg );
    I2C1WIRE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2c1wire_init( &i2c1wire, &cfg );
    Delay_1sec( );
}
```

### Application Task

> This function reads all of the channels on the Click module and displays any data it acqu-
  ires from them with a 100 millisecond delay. 

```c
void application_task ( void )
{
    uint8_t chan_state = 0;
    uint8_t cnt_chan = 0;
    uint8_t cnt_val = 0;
    uint8_t id_code[ 9 ] = { 0 };

    chan_state = 1;

    i2c1wire_soft_reset( &i2c1wire );
    Delay_10ms( );
    i2c1wire_set_config( &i2c1wire, I2C1WIRE_CONFIG_1WS_HIGH |
                                    I2C1WIRE_CONFIG_SPU_HIGH |
                                    I2C1WIRE_CONFIG_APU_LOW );
    Delay_10ms( );

    for ( cnt_chan = 0; cnt_chan < 8; cnt_chan++ )
    {
        i2c1wire_set_channel( &i2c1wire, cnt_chan );
        i2c1wire_one_wire_reset( &i2c1wire );
        Delay_10ms( );

        i2c1wire_write_byte_one_wire( &i2c1wire, I2C1WIRE_WIRE_COMMAND_READ_ROM );
        Delay_10ms();

        for ( cnt_val = 8; cnt_val > 0; cnt_val-- )
        {
            id_code[ cnt_val ] = i2c1wire_read_byte_one_wire( &i2c1wire );

            if ( id_code[ cnt_val ] == I2C1WIRE_WIRE_RESULT_OK )
            {
                log_printf( &logger, "\r\n Channel %d : No device on the channel\r\n", ( uint16_t ) cnt_chan );
                Delay_100ms( );
                break;
            }
            else if ( chan_state )
            {
                log_printf( &logger, " Channel %d : ID = 0x", ( uint16_t ) cnt_chan );
                chan_state = 0;
            }

            log_printf( &logger, "%d", ( uint16_t ) id_code[ cnt_val ] );
            Delay_10ms( );
        }

        log_printf( &logger, "\r\n---------------------------------------\r\n" );
    }

    log_printf( &logger, "***\r\n" );
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
