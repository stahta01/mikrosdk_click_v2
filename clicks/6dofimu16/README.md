
---
# 6DOF IMU 16 Click

> [6DOF IMU 16 Click](https://www.mikroe.com/?pid_product=MIKROE-6040) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6040&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of 6DOF IMU 16 Click board by reading and displaying 
 the accelerometer and gyroscope data (X, Y, and Z axis).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.C6DOFIMU16

### Example Key Functions

- `c6dofimu16_cfg_setup` Config Object Initialization function.
```c
void c6dofimu16_cfg_setup ( c6dofimu16_cfg_t *cfg );
```

- `c6dofimu16_init` Initialization function.
```c
err_t c6dofimu16_init ( c6dofimu16_t *ctx, c6dofimu16_cfg_t *cfg );
```

- `c6dofimu16_default_cfg` Click Default Configuration function.
```c
err_t c6dofimu16_default_cfg ( c6dofimu16_t *ctx );
```

- `c6dofimu16_sw_reset` This function performs the device software reset.
```c
err_t c6dofimu16_sw_reset ( c6dofimu16_t *ctx );
```

- `c6dofimu16_get_gyro_data` This function reads the angular rate of X, Y, and Z axis in degrees per second (mdps).
```c
err_t c6dofimu16_get_gyro_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *gyro_data );
```

- `c6dofimu16_get_accel_data` This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (mg).
```c
err_t c6dofimu16_get_accel_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *accel_data );
```

### Application Init

> Initializes the driver performs the Click default configuration, 
  and checks communication by reading device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu16_cfg_t c6dofimu16_cfg;  /**< Click config object. */

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
    c6dofimu16_cfg_setup( &c6dofimu16_cfg );
    C6DOFIMU16_MAP_MIKROBUS( c6dofimu16_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu16_init( &c6dofimu16, &c6dofimu16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU16_ERROR == c6dofimu16_default_cfg ( &c6dofimu16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t dev_id = 0;
    c6dofimu16_reg_read( &c6dofimu16, C6DOFIMU16_REG_WHO_AM_I, &dev_id );
    if ( C6DOFIMU16_DEVICE_ID != dev_id )
    {
        log_error( &logger, " Communication error " );
        for ( ; ; );
    }
    log_printf( &logger, " Device ID: 0x%.2X \r\n", ( uint16_t ) dev_id );

    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reading the accelerometer and gyroscope measurements, results are displayed on the USB UART every second.

```c
void application_task ( void )
{
    c6dofimu16_axis_t accel_data;
    c6dofimu16_axis_t gyro_data;

    c6dofimu16_get_accel_data( &c6dofimu16, &accel_data );
    c6dofimu16_get_gyro_data( &c6dofimu16, &gyro_data );
    log_printf( &logger, " Accel data | Gyro data \r\n" );
    log_printf( &logger, " X: %.2f g  | %.2f dps \r\n", accel_data.x_data, gyro_data.x_data );
    log_printf( &logger, " Y: %.2f g  | %.2f dps \r\n", accel_data.y_data, gyro_data.y_data );
    log_printf( &logger, " Z: %.2f g  | %.2f dps \r\n", accel_data.z_data, gyro_data.z_data );
    Delay_ms ( 1000 );
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
