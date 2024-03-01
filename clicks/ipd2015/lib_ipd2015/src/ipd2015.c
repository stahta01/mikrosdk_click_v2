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
 * @file ipd2015.c
 * @brief IPD 2015 Click Driver.
 */

#include "ipd2015.h"

void ipd2015_cfg_setup ( ipd2015_cfg_t *cfg ) 
{
    cfg->in1   = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->in3 = HAL_PIN_NC;
    cfg->in4 = HAL_PIN_NC;
}

err_t ipd2015_init ( ipd2015_t *ctx, ipd2015_cfg_t *cfg ) 
{
    err_t error_flag = IPD2015_OK;

    error_flag |= digital_out_init( &ctx->in1, cfg->in1 );
    error_flag |= digital_out_init( &ctx->in2, cfg->in2 );
    error_flag |= digital_out_init( &ctx->in3, cfg->in3 );
    error_flag |= digital_out_init( &ctx->in4, cfg->in4 );

    return error_flag;
}

void ipd2015_all_pins_set ( ipd2015_t *ctx ) 
{
    digital_out_high( &ctx->in1 );
    digital_out_high( &ctx->in2 );
    digital_out_high( &ctx->in3 );
    digital_out_high( &ctx->in4 );
    ctx->state = IPD2015_ALL_PIN_MASK;
}

void ipd2015_all_pins_clear ( ipd2015_t *ctx ) 
{
    digital_out_low( &ctx->in1 );
    digital_out_low( &ctx->in2 );
    digital_out_low( &ctx->in3 );
    digital_out_low( &ctx->in4 );
    ctx->state = IPD2015_NONE_PIN_MASK;
}

err_t ipd2015_set_out_level ( ipd2015_t *ctx, uint8_t out_sel, uint8_t state )
{
    switch ( out_sel )
    {
        case IPD2015_OUT1_PIN_MASK:
        {
            if ( IPD2015_PIN_STATE_HIGH == state )
            {
                digital_out_high( &ctx->in1 );
                ctx->state |= IPD2015_OUT1_PIN_MASK;
            }
            else
            {
                digital_out_low( &ctx->in1 );
                ctx->state &= ~IPD2015_OUT1_PIN_MASK;
            }
            break;
        }
        case IPD2015_OUT2_PIN_MASK:
        {
            if ( IPD2015_PIN_STATE_HIGH == state )
            {
                digital_out_high( &ctx->in2 );
                ctx->state |= IPD2015_OUT2_PIN_MASK;
            }
            else
            {
                digital_out_low( &ctx->in2 );
                ctx->state &= ~IPD2015_OUT2_PIN_MASK;
            }
            break;
        }
        case IPD2015_OUT3_PIN_MASK:
        {
            if ( IPD2015_PIN_STATE_HIGH == state )
            {
                digital_out_high( &ctx->in3 );
                ctx->state |= IPD2015_OUT3_PIN_MASK;
            }
            else
            {
                digital_out_low( &ctx->in3 );
                ctx->state &= ~IPD2015_OUT3_PIN_MASK;
            }
            break;
        }
        case IPD2015_OUT4_PIN_MASK:
        {
            if ( IPD2015_PIN_STATE_HIGH == state )
            {
                digital_out_high( &ctx->in4 );
                ctx->state |= IPD2015_OUT4_PIN_MASK;
            }
            else
            {
                digital_out_low( &ctx->in4 );
                ctx->state &= ~IPD2015_OUT4_PIN_MASK;
            }
            break;
        }
        default:
        {
            return IPD2015_ERROR;
        }
    }
    return IPD2015_OK;
}

uint8_t ipd2015_get_out_state ( ipd2015_t *ctx )
{
    return ctx->state;
}

// ------------------------------------------------------------------------- END
