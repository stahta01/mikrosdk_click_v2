\mainpage Main Page
 
---
# Audio Xover Click

Audio Xover Click is an analog active crossover solution for two-way loudspeakers. The primary purpose of the crossover circuit in a loudspeaker is to split an incoming audio signal into frequency bands that are passed to the speaker or “driver” best suited.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audio_xover_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/audio-xover-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioXover Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioXover Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audioxover_cfg_setup ( audioxover_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOXOVER_RETVAL audioxover_init ( audioxover_t *ctx, audioxover_cfg_t *cfg );

#### Example key functions :

- Device power on function.
> void audioxover_power_on ( audioxover_t *ctx );

- Device shut down function.
> void audioxover_shut_down ( audioxover_t *ctx );

## Examples Description

> This function initializes the driver and makes an initial log. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the Click and logger modules. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioxover_cfg_t cfg;

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

    audioxover_cfg_setup( &cfg );
    AUDIOXOVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioxover_init( &audioxover, &cfg );
}
  
```

### Application Task

> This function enables and disables the Click board every 10 seconds, and logs an appropriate message on the USB UART.

```c

void application_task ( void )
{
    log_printf( &logger, " * Switch: ON *\r\n" );
    audioxover_power_on ( &audioxover );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " * Switch: OFF *\r\n" );
    audioxover_shut_down ( &audioxover );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioXover

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
