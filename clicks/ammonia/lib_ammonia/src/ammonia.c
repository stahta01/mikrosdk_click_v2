/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "ammonia.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define DUMMY  0x00

#define AMMONIA_ADC_VREF_VAL  5
#define AMMONIA_ADC_SPI_RESOLUTION  2097152

#define AMMONIA_MEAS_VAL_PPM_MIN  5
#define AMMONIA_MEAS_VAL_PPM_MAX  200
#define AMMONIA_VOLT_TO_PPM_STEP  40

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ammonia_cfg_setup ( ammonia_cfg_t *cfg )
{
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->an = HAL_PIN_NC;

    cfg->spi_speed = 100000;
    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref = AMMONIA_ADC_VREF_VAL;    /**< [V] - recommended. */

    cfg->adc_sel = AMMONIA_ADC_SEL_SPI;  /**< ADC selection. */
}

err_t ammonia_init ( ammonia_t *ctx, ammonia_cfg_t *cfg )
{
    if ( cfg->adc_sel == AMMONIA_ADC_SEL_SPI )
    {
        if ( digital_in_init( &ctx->miso, cfg->miso ) == DIGITAL_IN_UNSUPPORTED_PIN )
        {
            return AMMONIA_INIT_ERROR;
        }

        // SPI serial communication init

        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.speed = cfg->spi_speed;
        spi_cfg.mode  = cfg->spi_mode;
        spi_cfg.sck   = cfg->sck;
        spi_cfg.miso  = cfg->miso;
        spi_cfg.mosi  = cfg->mosi;
        spi_cfg.default_write_data = DUMMY;

        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }

        if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }

        if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }

        if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        // Analog pin init for AD conversion

        analog_in_config_t an_cfg;

        analog_in_configure_default( &an_cfg );

        an_cfg.input_pin = cfg->an;

        if ( analog_in_open( &ctx->an, &an_cfg ) == ADC_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }

        if ( analog_in_set_resolution( &ctx->an, cfg->resolution ) == ADC_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }

        if ( analog_in_set_vref_value( &ctx->an, cfg->vref ) == ADC_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }
    }

    ctx->adc_sel = cfg->adc_sel;

    return AMMONIA_OK;
}

err_t ammonia_read_signal_voltage ( ammonia_t *ctx, float *data_out )
{
    if ( ctx->adc_sel )
    {
        uint8_t rx_buf[ 3 ];

        spi_master_select_device( ctx->chip_select );
        Delay_10us( );
        while ( digital_in_read( &ctx->miso ) );
        err_t error = spi_master_read( &ctx->spi, rx_buf, 3 );
        spi_master_deselect_device( ctx->chip_select );
        Delay_10us( );

        if ( error == SPI_MASTER_ERROR )
        {
            return AMMONIA_INIT_ERROR;
        }

        int32_t adc_val = rx_buf[ 0 ];
        adc_val <<= 8;
        adc_val |= rx_buf[ 1 ];
        adc_val <<= 8;
        adc_val |= rx_buf[ 2 ];

        if ( ( adc_val >> 22 ) == 2 )
        {
            adc_val |= 0xFFC00000;
        }
        else if ( ( adc_val >> 22 ) == 0 )
        {
            if ( adc_val & 0x200000 )
            {
                adc_val |= 0xFFC00000;
            }
        }
        else if ( ( adc_val >> 22 ) == 1 )
        {
            adc_val &= 0x003FFFFF;
        }

        float res = adc_val;
        res /= AMMONIA_ADC_SPI_RESOLUTION;
        res *= AMMONIA_ADC_VREF_VAL;

        *data_out = res;

        return AMMONIA_OK;
    }
    else
    {
        return analog_in_read_voltage( &ctx->an, data_out );
    }
}

err_t ammonia_read_measurement ( ammonia_t *ctx, uint16_t *data_out )
{
    float res;

    if ( ammonia_read_signal_voltage( ctx, &res ) == AMMONIA_INIT_ERROR )
    {
        return AMMONIA_INIT_ERROR;
    }

    res *= AMMONIA_VOLT_TO_PPM_STEP;

    if ( res <= AMMONIA_MEAS_VAL_PPM_MIN )
    {
        *data_out = AMMONIA_MEAS_VAL_PPM_MIN;
    }
    else if ( res >= AMMONIA_MEAS_VAL_PPM_MAX )
    {
        *data_out = AMMONIA_MEAS_VAL_PPM_MAX;
    }
    else
    {
        *data_out = (uint16_t)res;
    }

    return AMMONIA_OK;
}

// ------------------------------------------------------------------------ END
