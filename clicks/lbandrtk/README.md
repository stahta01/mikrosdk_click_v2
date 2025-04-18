
---
# LBAND RTK Click

> [LBAND RTK Click](https://www.mikroe.com/?pid_product=MIKROE-5411) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5411&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : UART/I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of LBAND RTK Click by setting the Point to multipoint (PMP)
configuration and waiting for the UBX-RXM-PMP message, then parsing it and displaying on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LBANDRTK

### Example Key Functions

- `lbandrtk_cfg_setup` Config Object Initialization function.
```c
void lbandrtk_cfg_setup ( lbandrtk_cfg_t *cfg );
```

- `lbandrtk_init` Initialization function.
```c
err_t lbandrtk_init ( lbandrtk_t *ctx, lbandrtk_cfg_t *cfg );
```

- `lbandrtk_set_default_pmp_cfg` This function sets the Point to multipoint (PMP) to default configuration to RAM layer.
```c
err_t lbandrtk_set_default_pmp_cfg ( lbandrtk_t *ctx );;
```

- `lbandrtk_get_pmp_cfg` This function reads the Point to multipoint (PMP) configuration from RAM layer.
```c
err_t lbandrtk_get_pmp_cfg ( lbandrtk_t *ctx, lbandrtk_pmp_cfg_t *pmp_cfg );
```

- `lbandrtk_read_ubx_frame` This function waits for an UBX frame message to arrive and reads it.
```c
err_t lbandrtk_read_ubx_frame ( lbandrtk_t *ctx, lbandrtk_ubx_frame_t *frame );
```

### Application Init

> Initializes the driver, reads the module version, sets the Point to multipoint (PMP) configuration
(for EU center frequency by default) and then reads that config and displays on the USB UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lbandrtk_cfg_t lbandrtk_cfg;  /**< Click config object. */

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
    lbandrtk_cfg_setup( &lbandrtk_cfg );
    LBANDRTK_MAP_MIKROBUS( lbandrtk_cfg, MIKROBUS_1 );
    if ( LBANDRTK_OK != lbandrtk_init( &lbandrtk, &lbandrtk_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    // Read module version
    lbandrtk.frame.class_id = LBANDRTK_CLASS_ID_UBX_MON;
    lbandrtk.frame.msg_id = LBANDRTK_MSG_ID_UBX_MON_VER;
    lbandrtk.frame.payload_len = 0;
    // send poll request
    lbandrtk_write_ubx_frame ( &lbandrtk, &lbandrtk.frame );
    // read polled message
    if ( LBANDRTK_OK == lbandrtk_read_ubx_frame ( &lbandrtk, &lbandrtk.frame ) )
    {
        log_printf( &logger, " ------ MODULE VERSION ------\r\n" );
        log_printf( &logger, " SW version:\r\n %s\r\n\n", &lbandrtk.frame.payload[ 0 ] );
        log_printf( &logger, " HW version:\r\n %s\r\n\n", &lbandrtk.frame.payload[ 30 ] );
        log_printf( &logger, " Extension:\r\n" );
        for ( uint16_t cnt = 0; cnt < ( ( lbandrtk.frame.payload_len - 40 ) / 30 ); cnt++ )
        {
            log_printf( &logger, " %s\r\n", &lbandrtk.frame.payload[ 40 + cnt * 30 ] );
        }
        log_printf( &logger, " ----------------------------\r\n\n" );
    }
    Delay_ms ( 100 );
    
    if ( LBANDRTK_ERROR == lbandrtk_set_default_pmp_cfg ( &lbandrtk ) )
    {
        log_error( &logger, " Set default PMP configuration." );
        for ( ; ; );
    }
    
    lbandrtk_pmp_cfg_t pmp_cfg;
    if ( LBANDRTK_OK == lbandrtk_get_pmp_cfg ( &lbandrtk, &pmp_cfg ) )
    {
        log_printf( &logger, " ----- PMP CONFIGURATION ----\r\n" );
        log_printf( &logger, " Center frequency: %lu\r\n", pmp_cfg.center_freq );
        log_printf( &logger, " Search window: %u\r\n", pmp_cfg.search_window );
        log_printf( &logger, " Use service ID: %u\r\n", ( uint16_t ) pmp_cfg.use_service_id );
        log_printf( &logger, " Service ID: %u\r\n", pmp_cfg.service_id );
        log_printf( &logger, " Data rate: %u\r\n", pmp_cfg.data_rate );
        log_printf( &logger, " Use descrambler: %u\r\n", ( uint16_t ) pmp_cfg.use_descrambler );
        log_printf( &logger, " Descrambler init: %u\r\n", pmp_cfg.descrambler_init );
        log_printf( &logger, " Use prescrambling: %lu\r\n", ( uint16_t ) pmp_cfg.use_prescrambling );
        log_printf( &logger, " Unique word: 0x%.8LX%.8LX\r\n", pmp_cfg.unique_word_high, pmp_cfg.unique_word_low );
        log_printf( &logger, " ----------------------------\r\n\n" );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for an incoming UBX messages, reads and displays them on the USB UART. If the received message is
PMP data it will be parsed additionally.

```c
void application_task ( void )
{
    if ( LBANDRTK_OK == lbandrtk_read_ubx_frame ( &lbandrtk, &lbandrtk.frame ) )
    {
        if ( ( LBANDRTK_CLASS_ID_UBX_RXM == lbandrtk.frame.class_id ) && ( LBANDRTK_MSG_ID_UBX_RXM_PMP == lbandrtk.frame.msg_id ) )
        {
            log_printf( &logger, " -------- UBX-RXM-PMP -------\r\n" );
            uint16_t num_bytes_user_data = LBANDRTK_UBX_RXM_PMP_MAX_USER_DATA; // Number of bytes for user data for message version 0
            log_printf( &logger, " Version: %u\r\n", ( uint16_t ) lbandrtk.frame.payload[ 0 ] );
            log_printf( &logger, " Time tag [ms]: %lu\r\n", 
                        ( ( uint32_t ) lbandrtk.frame.payload[ 7 ] << 24 ) | ( ( uint32_t ) lbandrtk.frame.payload[ 6 ] << 16 ) | 
                        ( ( uint16_t ) lbandrtk.frame.payload[ 5 ] << 8 ) | lbandrtk.frame.payload[ 4 ] );
            log_printf( &logger, " Unique word: 0x%.8LX%.8LX\r\n", 
                        ( ( uint32_t ) lbandrtk.frame.payload[ 15 ] << 24 ) | ( ( uint32_t ) lbandrtk.frame.payload[ 14 ] << 16 ) | 
                        ( ( uint16_t ) lbandrtk.frame.payload[ 13 ] << 8 ) | lbandrtk.frame.payload[ 12 ], 
                        ( ( uint32_t ) lbandrtk.frame.payload[ 11 ] << 24 ) | ( ( uint32_t ) lbandrtk.frame.payload[ 10 ] << 16 ) | 
                        ( ( uint16_t ) lbandrtk.frame.payload[ 9 ] << 8 ) | lbandrtk.frame.payload[ 8 ] );
            log_printf( &logger, " Unique word bit errors: %u\r\n", ( uint16_t ) lbandrtk.frame.payload[ 19 ] );
            // Check the received message version
            if ( lbandrtk.frame.payload[ 0 ] )
            {
                log_printf( &logger, " FEC bits : %u\r\n", ( ( uint16_t ) lbandrtk.frame.payload[ 21 ] << 8 ) | lbandrtk.frame.payload[ 20 ] );
                log_printf( &logger, " Eb/N0 [dB] : %.3f\r\n", lbandrtk.frame.payload[ 22 ] * LBANDRTK_UBX_RXM_PMP_EBN0_SCALE );
            }
            else
            {
                log_printf( &logger, " FEC bits : %u\r\n", ( ( uint16_t ) lbandrtk.frame.payload[ 525 ] << 8 ) | lbandrtk.frame.payload[ 524 ] );
                log_printf( &logger, " Eb/N0 [dB] : %.3f\r\n", lbandrtk.frame.payload[ 526 ] * LBANDRTK_UBX_RXM_PMP_EBN0_SCALE );
            }
            log_printf( &logger, "\r\n Service ID : %u\r\n", ( ( uint16_t ) lbandrtk.frame.payload[ 17 ] << 8 ) | lbandrtk.frame.payload[ 16 ] );
            log_printf( &logger, " Spare byte: %u\r\n", ( uint16_t ) lbandrtk.frame.payload[ 18 ] );
            // Check the received message version
            if ( lbandrtk.frame.payload[ 0 ] )
            {
                // Get number of bytes for user data for message version 1
                num_bytes_user_data = ( ( uint16_t ) lbandrtk.frame.payload[ 3 ] << 8 ) | lbandrtk.frame.payload[ 2 ];
                if ( num_bytes_user_data > LBANDRTK_UBX_RXM_PMP_MAX_USER_DATA )
                {
                    num_bytes_user_data = LBANDRTK_UBX_RXM_PMP_MAX_USER_DATA;
                }
                log_printf( &logger, " User data bytes: %u\r\n", num_bytes_user_data );
                log_printf( &logger, " User data:\r\n" );
                for ( uint16_t cnt = 0; cnt < num_bytes_user_data; cnt++ )
                {
                    if ( 0 == ( cnt % 20 ) )
                    {
                        log_printf( &logger, "\r\n" );
                    }
                    log_printf( &logger, "%.2X ", ( uint16_t ) lbandrtk.frame.payload[ 24 + cnt ] );
                }
            }
            else
            {
                log_printf( &logger, " User data bytes: %u\r\n", num_bytes_user_data );
                log_printf( &logger, " User data:\r\n" );
                for ( uint16_t cnt = 0; cnt < num_bytes_user_data; cnt++ )
                {
                    if ( 0 == ( cnt % 20 ) )
                    {
                        log_printf( &logger, "\r\n" );
                    }
                    log_printf( &logger, " %.2X", ( uint16_t ) lbandrtk.frame.payload[ 20 + cnt ] );
                }
            }
            log_printf( &logger, "\r\n ----------------------------\r\n\n" );
            Delay_ms ( 100 );
        }
        else
        {
            log_printf( &logger, " ---- UBX FRAME RECEIVED ----\r\n" );
            log_printf( &logger, " Class ID: 0x%.2X\r\n", ( uint16_t ) lbandrtk.frame.class_id );
            log_printf( &logger, " Message ID: 0x%.2X\r\n", ( uint16_t ) lbandrtk.frame.msg_id );
            log_printf( &logger, " Payload length: %u\r\n", lbandrtk.frame.payload_len );
            log_printf( &logger, " Payload:" );
            for ( uint16_t cnt = 0; cnt < lbandrtk.frame.payload_len; cnt++ )
            {
                if ( 0 == ( cnt % 20 ) )
                {
                    log_printf( &logger, "\r\n" );
                }
                log_printf( &logger, " %.2X", ( uint16_t ) lbandrtk.frame.payload[ cnt ] );
            }
            log_printf( &logger, "\r\n ----------------------------\r\n\n" );
            Delay_ms ( 100 );
        }
    }
}
```

### Note

> Make sure to use a correct L-Band antenna and that it's placed outside on open-sky in order to be able to receive PMP data from satellites.

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
