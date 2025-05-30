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
 * @file diffpress5.h
 * @brief This file contains API for Diff Press 5 Click Driver.
 */

#ifndef DIFFPRESS5_H
#define DIFFPRESS5_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup diffpress5 Diff Press 5 Click Driver
 * @brief API for configuring and manipulating Diff Press 5 Click driver.
 * @{
 */

/**
 * @defgroup diffpress5_set Diff Press 5 Settings
 * @brief Settings of Diff Press 5 Click driver.
 */

/**
 * @addtogroup diffpress5_set
 * @{
 */

/**
 * @brief Diff Press 5 pressure calculation setting.
 * @details Specified setting for pressure calculation of Diff Press 5 Click driver.
 */
#define DIFFPRESS5_PRESSURE_PA_MIN      0
#define DIFFPRESS5_PRESSURE_PA_MAX      10000
#define DIFFPRESS5_PRESSURE_SENS_PA     0.00045
#define DIFFPRESS5_ADC_VOUT_MULTIPLIER  1.5

/**
 * @brief Diff Press 5 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Diff Press 5 Click driver.
 */
#define DIFFPRESS5_NUM_CONVERSIONS      200

/**
 * @brief Diff Press 5 ADC setting.
 * @details Specified settings for ADC of Diff Press 5 Click driver.
 */
#define DIFFPRESS5_ADC_RESOLUTION       0x0FFF
#define DIFFPRESS5_VREF_3V3             3.3
#define DIFFPRESS5_VREF_5V              5.0

/**
 * @brief Diff Press 5 timeout setting.
 * @details Specified setting for timeout of Diff Press 5 Click driver.
 */
#define DIFFPRESS5_TIMEOUT_MS           2000

/**
 * @brief Diff Press 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Diff Press 5 Click driver.
 */
#define DIFFPRESS5_SET_DEV_ADDR         0x4D

/*! @} */ // diffpress5_set

/**
 * @defgroup diffpress5_map Diff Press 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Diff Press 5 Click driver.
 */

/**
 * @addtogroup diffpress5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Diff Press 5 Click to the selected MikroBUS.
 */
#define DIFFPRESS5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // diffpress5_map
/*! @} */ // diffpress5

/**
 * @brief Diff Press 5 Click driver selector.
 * @details Selects target driver interface of Diff Press 5 Click driver.
 */
typedef enum
{
    DIFFPRESS5_DRV_SEL_ADC,             /**< ADC driver descriptor. */
    DIFFPRESS5_DRV_SEL_I2C              /**< I2C driver descriptor. */

} diffpress5_drv_t;

/**
 * @brief Diff Press 5 Click context object.
 * @details Context object definition of Diff Press 5 Click driver.
 */
typedef struct
{
    analog_in_t  adc;                   /**< ADC module object. */
    i2c_master_t i2c;                   /**< I2C driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    float        vref;                  /**< ADC reference voltage. */
    float        zero_press_offset;     /**< Voltage offset for zero pressure. */
    diffpress5_drv_t drv_sel;           /**< Master driver interface selector. */

} diffpress5_t;

/**
 * @brief Diff Press 5 Click configuration object.
 * @details Configuration object definition of Diff Press 5 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;   /**< I2C serial speed. */
    uint8_t                i2c_address; /**< I2C slave address. */
    
    diffpress5_drv_t drv_sel;           /**< Master driver interface selector. */

} diffpress5_cfg_t;

/**
 * @brief Diff Press 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIFFPRESS5_OK = 0,
    DIFFPRESS5_ERROR = -1

} diffpress5_return_value_t;

/*!
 * @addtogroup diffpress5 Diff Press 5 Click Driver
 * @brief API for configuring and manipulating Diff Press 5 Click driver.
 * @{
 */

/**
 * @brief Diff Press 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #diffpress5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void diffpress5_cfg_setup ( diffpress5_cfg_t *cfg );

/**
 * @brief Diff Press 5 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #diffpress5_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #diffpress5_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void diffpress5_drv_interface_sel ( diffpress5_cfg_t *cfg, diffpress5_drv_t drv_sel );

/**
 * @brief Diff Press 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #diffpress5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress5_init ( diffpress5_t *ctx, diffpress5_cfg_t *cfg );

/**
 * @brief Diff Press 5 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress5_read_adc_raw ( diffpress5_t *ctx, uint16_t *raw_adc );

/**
 * @brief Diff Press 5 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t diffpress5_read_adc_voltage ( diffpress5_t *ctx, float *voltage );

/**
 * @brief Diff Press 5 set vref function.
 * @details This function sets the voltage reference for Diff Press 5 Click driver.
 * @param[in] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b diffpress5_init is 3.3V.
 */
err_t diffpress5_set_vref ( diffpress5_t *ctx, float vref );

/**
 * @brief Diff Press 5 read vout function.
 * @details This function reads the sensor output voltage.
 * @param[in] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @param[out] vout : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress5_read_vout ( diffpress5_t *ctx, float *vout );

/**
 * @brief Diff Press 5 read vout avg function.
 * @details This function reads a desired number of sensor voltage output samples and averages it.
 * @param[in] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] vout_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress5_read_vout_avg ( diffpress5_t *ctx, uint16_t num_conv, float *vout_avg );

/**
 * @brief Diff Press 5 calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no pressure is applied to the sensor.
 */
err_t diffpress5_calib_offset ( diffpress5_t *ctx );

/**
 * @brief Diff Press 5 read pressure function.
 * @details This function reads the differential pressure measurement.
 * @param[in] ctx : Click context object.
 * See #diffpress5_t object definition for detailed explanation.
 * @param[out] pressure : Differential pressure level [Pa].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero pressure offset, see diffpress5_calib_offset function.
 */
err_t diffpress5_read_pressure ( diffpress5_t *ctx, uint16_t *pressure );

#ifdef __cplusplus
}
#endif
#endif // DIFFPRESS5_H

/*! @} */ // diffpress5

// ------------------------------------------------------------------------ END
