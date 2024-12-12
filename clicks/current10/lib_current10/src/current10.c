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
 * @file current10.c
 * @brief Current 10 Click Driver.
 */

#include "current10.h"

void current10_cfg_setup ( current10_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENT10_SET_DEV_ADDR;
    cfg->vref        = CURRENT10_VREF_3V3;
    cfg->drv_sel     = CURRENT10_DRV_SEL_ADC;
}

void current10_drv_interface_sel ( current10_cfg_t *cfg, current10_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t current10_init ( current10_t *ctx, current10_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( CURRENT10_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }
    }
    else
    {
        analog_in_config_t adc_cfg;

        analog_in_configure_default( &adc_cfg );

        adc_cfg.input_pin = cfg->an;

        if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
        {
            return ADC_ERROR;
        }
    }

    return CURRENT10_OK;
}

err_t current10_read_raw_adc ( current10_t *ctx, uint16_t *raw_adc ) 
{
    if ( CURRENT10_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ] = { 0 };
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & CURRENT10_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t current10_read_voltage ( current10_t *ctx, float *voltage ) 
{
    if ( CURRENT10_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc = 0;
        err_t err_flag = current10_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) CURRENT10_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t current10_read_voltage_avg ( current10_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < CURRENT10_NUM_CONVERSIONS )
    {
        if ( CURRENT10_OK == current10_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > CURRENT10_TIMEOUT_MS )
        {
            return CURRENT10_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / CURRENT10_NUM_CONVERSIONS );
    return CURRENT10_OK;
}

err_t current10_set_vref ( current10_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( CURRENT10_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return CURRENT10_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t current10_calib_offset ( current10_t *ctx )
{
    float voltage = 0;
    err_t error_flag = current10_read_voltage_avg ( ctx, CURRENT10_NUM_CONVERSIONS, &voltage );
    ctx->zero_curr_offset = voltage;
    return error_flag;
}

err_t current10_calib_resolution ( current10_t *ctx, float calib_current )
{
    float voltage = 0;
    err_t error_flag = current10_read_voltage_avg ( ctx, CURRENT10_NUM_CONVERSIONS, &voltage );
    ctx->data_resolution = calib_current / ( voltage - ctx->zero_curr_offset );
    return error_flag;
}

err_t current10_read_current ( current10_t *ctx, float *current )
{
    float voltage = 0;
    err_t error_flag = current10_read_voltage_avg ( ctx, CURRENT10_NUM_CONVERSIONS, &voltage );
    *current = ( voltage - ctx->zero_curr_offset ) * ctx->data_resolution;
    return error_flag;
}

// ------------------------------------------------------------------------- END