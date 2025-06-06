
---
# Plug n Trust Click

> [Plug n Trust Click](https://www.mikroe.com/?pid_product=MIKROE-4656) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4656&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is showcasing basic functionality of Plug&Trust
Click board. It gets identify data from device, selects card 
manager and applet. Then checks free memory, reads all objects and 
deletes not reserved ones. After that showcases a few of functionality: 
Generating random data, 
Creating, reading and deleteing binary objects, 
Creating AES symmetrical key and cipher with it;
In the end it is showcasing funcionality in the endless loop.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PlugnTrust

### Example Key Functions

- `plugntrust_cfg_setup` Config Object Initialization function.
```c
void plugntrust_cfg_setup ( plugntrust_cfg_t *cfg );
```

- `plugntrust_init` Initialization function.
```c
err_t plugntrust_init ( plugntrust_t *ctx, plugntrust_cfg_t *cfg );
```

- `plugntrust_default_cfg` Click Default Configuration function.
```c
err_t plugntrust_default_cfg ( plugntrust_t *ctx );
```

- `plugntrust_apdu_transfer` Write-Read frame data function.
```c
err_t plugntrust_apdu_transfer ( plugntrust_t *ctx, plugntrust_frame_data_t *frame_data );
```

- `plugntrust_select_card_manager` Select card manager.
```c
err_t plugntrust_select_card_manager ( plugntrust_t *ctx, uint8_t rsp, uint8_t *cardmanager_rsp, uint8_t *cardmanager_rsp_len );
```

- `plugntrust_select_applet` Selects Clicks Applet and returns info that device sends back to host.
```c
err_t plugntrust_select_applet ( plugntrust_t *ctx, uint8_t ns_encode, plugntrust_version_info_t *ver_info );
```

### Application Init

> At the start it sets comunication interface from default
configuration[I2C]. Reads indetifing data from device, 
and then selects Card manager and applet. After that it 
reads free presistant memory, reads all objects and deletes
objects that are not reserved by the Applet. Then it generates
2 byte of random data, and gets the version information 
from the Applet. Thtas followed up with creating binary
object and 'MikroE' data is wrriten in it. Then its checked
it object is created, and reads data back, in the end its 
deleted and checked if it still exists. Finally it creates
128AES key (16bytes), and then it encrypts and then decrypts
data with that key, and in the end it deletes that key object.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    plugntrust_cfg_t plugntrust_cfg;  /**< Click config object. */
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
    plugntrust_cfg_setup( &plugntrust_cfg );
    PLUGNTRUST_MAP_MIKROBUS( plugntrust_cfg, MIKROBUS_1 );
    err_t init_flag = plugntrust_init( &plugntrust, &plugntrust_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    } 
    
    frame_data.apdu = &apdu_data;
    
    plugntrust_default_cfg ( &plugntrust );
    
    if ( PLUGNTRUST_INTERFACE_ISO14443 == plugntrust.interface )
    {
        log_info( &logger, " ISO14443 Interface active..." );
        for ( ; ; );
    }
    
    soft_reset( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_data_identify( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    select_card_manger( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    select_applet( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    check_free_memory( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    list_and_delete_objects( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_random( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    read_uid_object( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    get_version(  );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    create_check_delete( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    aes_cipher( );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> It generates 16bytes of data, writes it in binary object and
then reads it and logs it. Then creates AES key and encrypts
that random data with it, and then decrypts it. In the end it
deletes both AES key object and binary object thats created 
at the start of task.

```c
void application_task ( void ) 
{
    #define DATA_LEN 16
    static uint8_t aes_value[ DATA_LEN ]    = { 0x40, 0x41, 0x42, 0x43,0x44, 0x45, 0x46, 0x47,
                                                0x48, 0x49, 0x4A, 0x4B,0x4C, 0x4D, 0x4E, 0x4F };
    static uint32_t binary_id               = 0xBBBBBBBBul;
    static uint32_t aes_id                  = 0xCCCCCCCCul;
    uint8_t random_data[ DATA_LEN ]         = { 0 };
    uint8_t read_data[ DATA_LEN ]           = { 0 };
    uint8_t encrypted_data[ DATA_LEN ]      = { 0 };
    uint32_t read_len = DATA_LEN;
    
    if ( PLUGNTRUST_OK == plugntrust_get_random_numbers( &plugntrust, random_data, DATA_LEN ) )
    {
        log_printf( &logger, " > Generated random data: 0x" );
        log_buf_hex( random_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Random" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( PLUGNTRUST_OBJECT_DOESNT_EXIST == plugntrust_check_object_exist( &plugntrust, binary_id ) )
    {
        log_printf( &logger, " Write random data to binary object...\r\n" );
        if ( PLUGNTRUST_OK != plugntrust_write_binary_object( &plugntrust, binary_id, 0, DATA_LEN, random_data ) )
        {
            log_error( &logger, " Write Binary" );
        }
        else
        {
            log_info( &logger, " Status OK" );
        }
    }
    else
    {
        log_error( &logger, " Binary object already exist" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( PLUGNTRUST_OBJECT_DOES_EXISTS == plugntrust_check_object_exist( &plugntrust, binary_id ) )
    {
        if ( PLUGNTRUST_OK == plugntrust_read_object( &plugntrust, binary_id, 0, 0, read_data, &read_len ) )
        {
            log_printf( &logger, " > Read data from binary object: 0x" );
            log_buf_hex( read_data, read_len );
            log_printf( &logger, "\r\n" );
        }
        else
        {
            log_error( &logger, " Read binray object" );
        } 
    }
    else
    {
        log_error( &logger, " Binary object doesn't exist" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Create AES key...\r\n" );
    create_128_aes_key( aes_id, aes_value );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, PLUGNTRUST_P2_ENCRYPT_ONESHOT, read_data, encrypted_data ) )
    {
        log_printf( &logger, " > Encrypted data: 0x" );
        log_buf_hex( encrypted_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Encrypting data" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( PLUGNTRUST_OK == cipher_data_with_aes_key( aes_id, PLUGNTRUST_P2_DECRYPT_ONESHOT, encrypted_data, read_data ) )
    {
        log_printf( &logger, " > Decrypted data: 0x" );
        log_buf_hex( read_data, DATA_LEN );
        log_printf( &logger, "\r\n" );
    }
    else
    {
        log_error( &logger, " Decrypting data" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Delete Binary and AES object...\r\n" );
    if ( ( PLUGNTRUST_OK != plugntrust_delete_object( &plugntrust, binary_id ) ) || ( PLUGNTRUST_OK != plugntrust_delete_object( &plugntrust, aes_id ) ) )
    {
        log_error( &logger, " Deleting objects" );
    }
    log_printf( &logger, "*****************************************************************************\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> For more informations and explanations refer to documents 
from NXP->AN12413 and UM11225.

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
