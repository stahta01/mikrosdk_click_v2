/*!
 * @file main.c
 * @brief c7x10Y Click example
 *
 * # Description
 * This demo example shows a drawing of pixels, characters and a number on the screen.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring the Click board.
 *
 * ## Application Task
 * Draws characters, numbers, and pixels to the display.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "c7x10y.h"

// ------------------------------------------------------------------ VARIABLES

static c7x10y_t c7x10y;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    
    c7x10y_cfg_t c7x10y_cfg;  /**< Click config object. */

    //  Click initialization.

    c7x10y_cfg_setup( &c7x10y_cfg );
    C7X10Y_MAP_MIKROBUS( c7x10y_cfg, MIKROBUS_1 );
    c7x10y_init( &c7x10y, &c7x10y_cfg );
}

void application_task ( void ) {
    
    c7x10y_pixel_t pixel;
    uint8_t cnt;
    uint8_t cnt_x;
    uint8_t cnt_y;
    
    // CHAR PROCEDURE
    
    for ( cnt = 'A'; cnt < 'Z'; cnt+=2 ) {
        
        c7x10y_draw_char( &c7x10y, cnt, C7X10Y_DISPLAY_LEFT, C7X10Y_DISPLAY_DELAY_50MS );
        c7x10y_draw_char( &c7x10y, cnt + 1, C7X10Y_DISPLAY_RIGHT | C7X10Y_DISPLAY_REFRESH, C7X10Y_DISPLAY_DELAY_50MS );
       
        Delay_ms ( 1000 );
    }

    // COUNTER PROCEDURE
    
    for ( cnt = 0; cnt < 15; cnt++ ) {
        
        c7x10y_draw_number( &c7x10y, cnt, C7X10Y_DISPLAY_DELAY_50MS );
        
        Delay_ms ( 500 );
    }
    
    // PIXELS PROCEDURE
    
    for ( cnt_x = 0; cnt_x <= 7; cnt_x++ ) {
        
        for ( cnt_y = 0; cnt_y <= 10; cnt_y++ ) {
            
            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y;
            c7x10y_draw_pixel( &c7x10y, &pixel, C7X10Y_DISPLAY_PIXEL_STORAGE, C7X10Y_DISPLAY_DELAY_20MS );

            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y + 1;
            c7x10y_draw_pixel( &c7x10y, &pixel, C7X10Y_DISPLAY_PIXEL_REFRESH, C7X10Y_DISPLAY_DELAY_20MS );
        }
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

// ------------------------------------------------------------------------ END
