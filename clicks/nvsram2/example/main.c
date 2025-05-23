/*!
 * @file main.c
 * @brief nvSRAM2 Click example
 *
 * # Description
 * This is an example using nvSRAM 2 Click based on CY14B101Q which is combines a 1-Mbit nvSRAM with a
 * nonvolatile element in each memory cell with serial SPI interface. The memory is organized as 128K words of 8 bits each.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI and UART LOG, sets CS and PWM pins as outputs. 
 * Disables hold, sets write enable latch, targets the memory address at 12345 ( 0x00003039 ) 
 * for burst write starting point and writes data which is also displayed on the log.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the nvSRAM 2 Click board. In this example, the data is read from
 * the targeted memory address. The results are being sent to the Usart Terminal. This task repeats every 5 sec.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "nvsram2.h"

static nvsram2_t nvsram2;
static log_t logger;
static char demo_data[ 9 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static char rx_data[ 9 ];
static uint32_t memory_addr; 

void application_init ( void ) {
    log_cfg_t log_cfg;               /**< Logger config object. */
    nvsram2_cfg_t nvsram2_cfg;       /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    nvsram2_cfg_setup( &nvsram2_cfg );
    NVSRAM2_MAP_MIKROBUS( nvsram2_cfg, MIKROBUS_1 );
    err_t init_flag  = nvsram2_init( &nvsram2, &nvsram2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    nvsram2_default_cfg ( &nvsram2 );
    log_info( &logger, " Application Task " );

    memory_addr = 12345;

    nvsram2_burst_write( &nvsram2, memory_addr, demo_data, 9 );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "-> Write data : %s \r\n", demo_data );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    nvsram2_burst_read( &nvsram2, memory_addr, rx_data, 9 );
    log_printf( &logger, "-----------------------\r\n"  );
    log_printf( &logger, "<- Read data  : %s \r\n", rx_data );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

// ------------------------------------------------------------------------ END
