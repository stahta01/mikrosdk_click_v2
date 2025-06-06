
---
# Wireless SUN Click

> [Wireless SUN Click](https://www.mikroe.com/?pid_product=MIKROE-5338) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5338&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Wireless SUN Click board by showing the communication between the two Click boards configured as BORDER and ROUTER.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WirelessSUN

### Example Key Functions

- `wirelesssun_cfg_setup` Config Object Initialization function.
```c
void wirelesssun_cfg_setup ( wirelesssun_cfg_t *cfg );
```

- `wirelesssun_init` Initialization function.
```c
err_t wirelesssun_init ( wirelesssun_t *ctx, wirelesssun_cfg_t *cfg );
```

- `wirelesssun_send_cmd` This function sends a specified command to the Click module.
```c
void wirelesssun_send_cmd ( wirelesssun_t *ctx, char *cmd );
```

- `wirelesssun_send_cmd_with_parameter` This function sends a specified command to the Click module with desired parameters appended to.
```c
void wirelesssun_send_cmd_with_parameter ( wirelesssun_t *ctx, char *cmd, char *param_buf );
```

- `wirelesssun_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t wirelesssun_generic_read ( wirelesssun_t *ctx, char *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and configures the Click board by performing a hardware reset
and a clear parameters feature, and setting the device network name, device role to
BORDER or ROUTER depending on the application mode. In the end, it saves settings and reboots device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wirelesssun_cfg_t wirelesssun_cfg;  /**< Click config object. */

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
    wirelesssun_cfg_setup( &wirelesssun_cfg );
    WIRELESSSUN_MAP_MIKROBUS( wirelesssun_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wirelesssun_init( &wirelesssun, &wirelesssun_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    log_printf( &logger, "\r\n - Reset device -\r\n" );
    wirelesssun_reset_device ( &wirelesssun );
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Clear parameters and reboot device -\r\n" );
    wirelesssun_send_cmd ( &wirelesssun, WIRELESSSUN_CMD_CLRST );
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Set device name -\r\n" );
    wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_NETNAME, DEVICE_NETWORK_NAME );
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Set device starting role -\r\n" );
#ifdef DEMO_APP_BORDER
    wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_ATSTART, WIRELESSSUN_DEVICE_ROLE_BORDER );
#else
    wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_ATSTART, WIRELESSSUN_DEVICE_ROLE_ROUTER );
#endif
    wirelesssun_rsp_check ( );
    
    log_printf( &logger, "\r\n - Save settings and reboot device -\r\n" );
    wirelesssun_send_cmd ( &wirelesssun, WIRELESSSUN_CMD_SVRST );
    wirelesssun_rsp_check ( );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected application mode, it reads all the received data and parses
the received TCP/UDP messages (BORDER mode) or waits for the connection, reads the parent
global address, and then starts sending a desired TCP/UDP messages to the parent every 3 seconds (ROUTER mode).

```c
void application_task ( void )
{
#ifdef DEMO_APP_BORDER
    wirelesssun_process( );
    if ( strstr( app_buf, WIRELESSSUN_CMD_PROMPT_SIGN ) )
    {
        uint8_t demo_hex_msg[ 100 ] = { 0 };
        uint8_t demo_text_msg[ 50 ] = { 0 };
        char * __generic_ptr start_msg_ptr = NULL;
        char * __generic_ptr end_msg_ptr = NULL;
        uint8_t msg_len = 0;
        uint8_t msg_cnt = 0;
        if ( ( strstr( app_buf, WIRELESSSUN_RSP_TCPR ) ) || ( strstr( app_buf, WIRELESSSUN_RSP_UDPR ) ) )
        {
            if ( strstr( app_buf, WIRELESSSUN_RSP_TCPR ) )
            {
                start_msg_ptr = strstr( app_buf, WIRELESSSUN_RSP_TCPR );
            }
            else
            {
                start_msg_ptr = strstr( app_buf, WIRELESSSUN_RSP_UDPR );
            }
            start_msg_ptr = strstr ( start_msg_ptr, ">" ) + 2;
            end_msg_ptr = strstr( start_msg_ptr, WIRELESSSUN_CMD_PROMPT_SIGN );
            msg_len = ( end_msg_ptr - start_msg_ptr );
            memcpy ( demo_hex_msg, start_msg_ptr, msg_len );
            for ( msg_cnt = 0; msg_cnt < msg_len; msg_cnt += 2 )
            {
                demo_text_msg[ msg_cnt / 2 ] = hex_to_uint8 ( &demo_hex_msg [ msg_cnt ] );
            }
            if ( strstr( app_buf, WIRELESSSUN_RSP_TCPR ) )
            {
                log_printf( &logger, "\r\n - Received TCP message: \"%s\" -\r\n", demo_text_msg );
            }
            else
            {
                log_printf( &logger, "\r\n - Received UDP message: \"%s\" -\r\n", demo_text_msg );
            }
        }
        wirelesssun_clear_app_buf( );
    }
#else
    wirelesssun_wait_for_connection ( );
    uint8_t gbl_address[ 20 ] = { 0 };
    wirelesssun_get_parent_gbl_address ( gbl_address );
    for ( ; ; )
    {
        uint8_t tcp_udp_params[ 120 ] = { 0 };
        uint8_t demo_hex_msg[ 100 ] = { 0 };
        uint8_t demo_text_msg[ 50 ] = { 0 };
        uint8_t msg_cnt = 0;
        strcpy ( demo_text_msg, DEMO_TEXT_MESSAGE );
        strcpy ( tcp_udp_params, gbl_address );
        strcat ( tcp_udp_params, WIRELESSSUN_CMD_DELIMITER );
        strcat ( tcp_udp_params, WIRELESSSUN_DEFAULT_PORT );
        strcat ( tcp_udp_params, WIRELESSSUN_CMD_DELIMITER );
        for ( msg_cnt = 0; msg_cnt < strlen ( demo_text_msg ); msg_cnt++ )
        {
            uint8_to_hex ( demo_text_msg[ msg_cnt ], &demo_hex_msg[ msg_cnt * 2 ] );
        }
        strcat ( tcp_udp_params, demo_hex_msg );
        log_printf( &logger, "\r\n - Sending \"%s\" message via TCP -\r\n", demo_text_msg );
        wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_TCPS, tcp_udp_params );
        wirelesssun_rsp_check ( );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        log_printf( &logger, "\r\n - Sending \"%s\" message via UDP -\r\n", demo_text_msg );
        wirelesssun_send_cmd_with_parameter ( &wirelesssun, WIRELESSSUN_CMD_UDPS, tcp_udp_params );
        wirelesssun_rsp_check ( );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
}
```

### Note

> By default, the BORDER application mode is selected. comment out the DEMO_APP_BORDER macro definition in order to switch the application mode to ROUTER.

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
