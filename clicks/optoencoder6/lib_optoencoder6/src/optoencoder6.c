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
 * @file optoencoder6.c
 * @brief Opto Encoder 6 Click Driver.
 */

#include "optoencoder6.h"

void optoencoder6_cfg_setup ( optoencoder6_cfg_t *cfg ) 
{
    cfg->en = HAL_PIN_NC;
    cfg->out = HAL_PIN_NC;
}

err_t optoencoder6_init ( optoencoder6_t *ctx, optoencoder6_cfg_t *cfg ) 
{
    err_t error_flag = OPTOENCODER6_OK;

    error_flag |= digital_out_init( &ctx->en, cfg->en );

    error_flag |= digital_in_init( &ctx->out, cfg->out );

    return error_flag;
}

void optoencoder6_enable_output ( optoencoder6_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void optoencoder6_disable_output ( optoencoder6_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

uint8_t optoencoder6_get_out_pin ( optoencoder6_t *ctx )
{
    return digital_in_read( &ctx->out );
}

// ------------------------------------------------------------------------- END
