/*!
 * @file main.c
 * @brief Nano GPS 3 Click example
 *
 * # Description
 * This example demonstrates the use of Nano GPS 3 Click by reading and displaying
 * the GPS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the Click board.
 *
 * ## Application Task
 * Reads the received data, parses the GNGGA info from it, and once it receives the position fix
 * it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void nanogps3_clear_app_buf ( void )
 * - static err_t nanogps3_process ( nanogps3_t *ctx )
 * - static void nanogps3_parser_application ( char *rsp )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nanogps3.h"

static nanogps3_t nanogps3;
static log_t logger;

static char app_buf[ NANOGPS3_RX_DRV_BUFFER_SIZE ];
static int32_t app_buf_len = 0;

/**
 * @brief Nano GPS 3 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void nanogps3_clear_app_buf ( void );

/**
 * @brief Nano GPS 3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read or Application buffer overflow.
 * @note None.
 */
static err_t nanogps3_process ( nanogps3_t *ctx );

/**
 * @brief Nano GPS 3 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void nanogps3_parser_application ( char *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanogps3_cfg_t nanogps3_cfg;  /**< Click config object. */

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
    nanogps3_cfg_setup( &nanogps3_cfg );
    NANOGPS3_MAP_MIKROBUS( nanogps3_cfg, MIKROBUS_1 );
    err_t init_flag = nanogps3_init( &nanogps3, &nanogps3_cfg ); 
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    nanogps3_default_cfg( &nanogps3 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    nanogps3_process( &nanogps3 );
    if ( app_buf_len > ( sizeof( NANOGPS3_RSP_GNGGA ) + NANOGPS3_NMEA_GNGGA_NUM_ELEMENT ) ) 
    {
        nanogps3_parser_application( app_buf );
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void nanogps3_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t nanogps3_process ( nanogps3_t *ctx )
{
    int32_t rx_size;
    char rx_buf[ NANOGPS3_RX_DRV_BUFFER_SIZE ] = { 0 };

    if ( NANOGPS3_DRV_SEL_UART == ctx->drv_sel )
    {
        rx_size = nanogps3_generic_read( &nanogps3, &rx_buf, NANOGPS3_RX_DRV_BUFFER_SIZE );
    }
    else
    {
        if ( NANOGPS3_OK == nanogps3_generic_read( ctx, rx_buf, 1 ) )
        {
            if ( NANOGPS3_DUMMY != rx_buf[ 0 ] )
            {
                rx_size = 1;
            }
        }
    }
    if ( rx_size > 0 )
    {  
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > NANOGPS3_RX_DRV_BUFFER_SIZE ) 
        {
            nanogps3_clear_app_buf( );
            return NANOGPS3_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buf[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return NANOGPS3_OK;
    }
    return NANOGPS3_ERROR;
}

static void nanogps3_parser_application ( char *rsp )
{
    char element_buf[ 100 ] = { 0 };
    if ( NANOGPS3_OK == nanogps3_parse_gngga( rsp, NANOGPS3_GNGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( 0 < strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", 
                        element_buf, &element_buf[ 2 ] );
            nanogps3_parse_gngga( rsp, NANOGPS3_GNGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", 
                        element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            nanogps3_parse_gngga( rsp, NANOGPS3_GNGGA_ALTITUDE, element_buf );
            log_printf( &logger, " Altitude: %s m \r\n", element_buf );
            wait_for_fix_cnt = 0;
        }
        else
        {
            if ( wait_for_fix_cnt % 5 == 0 )
            {
                log_printf( &logger, " Waiting for the position fix...\r\n\n" );
                wait_for_fix_cnt = 0;
            }
            wait_for_fix_cnt++;
        }
        nanogps3_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
