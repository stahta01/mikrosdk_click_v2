/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file bt840.c
 * @brief BT840 Click Driver.
 */

#include "bt840.h"

void bt840_cfg_setup ( bt840_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wup = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cmd = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t bt840_init ( bt840_t *ctx, bt840_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->wup, cfg->wup );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cmd, cfg->cmd );
    digital_out_low ( &ctx->wup );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->cmd );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );

    return UART_SUCCESS;
}

err_t bt840_generic_write ( bt840_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t bt840_generic_read ( bt840_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void bt840_set_rst_pin ( bt840_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void bt840_reset_device ( bt840_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
}

void bt840_set_wup_pin ( bt840_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void bt840_wakeup_device ( bt840_t *ctx )
{
    digital_out_low ( &ctx->wup );
    Delay_1ms ( );
    digital_out_high ( &ctx->wup );
    Delay_1ms ( );
}

void bt840_set_cmd_mode ( bt840_t *ctx )
{
    digital_out_high ( &ctx->cmd );
    Delay_1ms ( );
}

void bt840_set_data_mode ( bt840_t *ctx )
{
    digital_out_low ( &ctx->cmd );
    Delay_1ms ( );
}

void bt840_cmd_run ( bt840_t *ctx, uint8_t *cmd )
{
    uint8_t cr_lf[ 3 ] = { '\r', '\n', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, cr_lf );
    bt840_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms(  );
}

void bt840_cmd_set ( bt840_t *ctx, uint8_t *cmd, uint8_t *value )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, value );
    bt840_cmd_run( ctx, ctx->cmd_buffer );
}

void bt840_cmd_get ( bt840_t *ctx, uint8_t *cmd )
{
    uint8_t check_char[ 2 ] = { '?', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, check_char );
    bt840_cmd_run( ctx, ctx->cmd_buffer );
}

// ------------------------------------------------------------------------- END
