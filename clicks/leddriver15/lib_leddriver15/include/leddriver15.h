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
 * @file leddriver15.h
 * @brief This file contains API for LED Driver 15 Click Driver.
 */

#ifndef LEDDRIVER15_H
#define LEDDRIVER15_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup leddriver15 LED Driver 15 Click Driver
 * @brief API for configuring and manipulating LED Driver 15 Click driver.
 * @{
 */

/**
 * @defgroup leddriver15_reg LED Driver 15 Registers List
 * @brief List of registers of LED Driver 15 Click driver.
 */

/**
 * @addtogroup leddriver15_reg
 * @{
 */

/**
 * @brief LED Driver 15 register list.
 * @details Specified register list of LED Driver 15 Click driver.
 */
#define LEDDRIVER15_REG_R0                  0x00
#define LEDDRIVER15_REG_R1                  0x01

/*! @} */ // leddriver15_reg

/**
 * @defgroup leddriver15_set LED Driver 15 Registers Settings
 * @brief Settings for registers of LED Driver 15 Click driver.
 */

/**
 * @addtogroup leddriver15_set
 * @{
 */

/**
 * @brief LED Driver 15 REG_R0 register setting.
 * @details Specified setting for REG_R0 register of LED Driver 15 Click driver.
 */
#define LEDDRIVER15_R0_EN                   0x80
#define LEDDRIVER15_R0_REF_SET_MASK         0x7C
#define LEDDRIVER15_R0_REF_SET_OFFSET       2

/**
 * @brief LED Driver 15 REG_R1 register setting.
 * @details Specified setting for REG_R1 register of LED Driver 15 Click driver.
 */
#define LEDDRIVER15_R1_DIMS_I2C             0x00
#define LEDDRIVER15_R1_DIMS_PWM             0x40
#define LEDDRIVER15_R1_DIMS_MASK            0x40
#define LEDDRIVER15_R1_SYNC_DISABLE         0x00
#define LEDDRIVER15_R1_SYNC_ENABLE          0x20
#define LEDDRIVER15_R1_SYNC_MASK            0x20
#define LEDDRIVER15_R1_OVP_13p5V            0x00
#define LEDDRIVER15_R1_OVP_24V              0x10
#define LEDDRIVER15_R1_OVP_35p5V            0x08
#define LEDDRIVER15_R1_OVP_MASK             0x18
#define LEDDRIVER15_R1_VOS                  0x04
#define LEDDRIVER15_R1_LED0                 0x02
#define LEDDRIVER15_R1_OTP                  0x01

/**
 * @brief LED Driver 15 I2C dimming setting.
 * @details Specified setting for I2C dimming of LED Driver 15 Click driver.
 */
#define LEDDRIVER15_I2C_DIMMING_MIN         0
#define LEDDRIVER15_I2C_DIMMING_MAX         31

/**
 * @brief LED Driver 15 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Driver 15 Click driver.
 */
#define LEDDRIVER15_DEVICE_ADDRESS          0x17

/*! @} */ // leddriver15_set

/**
 * @defgroup leddriver15_map LED Driver 15 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 15 Click driver.
 */

/**
 * @addtogroup leddriver15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 15 Click to the selected MikroBUS.
 */
#define LEDDRIVER15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // leddriver15_map
/*! @} */ // leddriver15

/**
 * @brief LED Driver 15 Click context object.
 * @details Context object definition of LED Driver 15 Click driver.
 */
typedef struct
{
    digital_out_t en;               /**< Enable pin (Active high). */
    
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} leddriver15_t;

/**
 * @brief LED Driver 15 Click configuration object.
 * @details Configuration object definition of LED Driver 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t en;                  /**< Enable pin (Active high). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} leddriver15_cfg_t;

/**
 * @brief LED Driver 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER15_OK = 0,
    LEDDRIVER15_ERROR = -1

} leddriver15_return_value_t;

/*!
 * @addtogroup leddriver15 LED Driver 15 Click Driver
 * @brief API for configuring and manipulating LED Driver 15 Click driver.
 * @{
 */

/**
 * @brief LED Driver 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver15_cfg_setup ( leddriver15_cfg_t *cfg );

/**
 * @brief LED Driver 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #leddriver15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver15_init ( leddriver15_t *ctx, leddriver15_cfg_t *cfg );

/**
 * @brief LED Driver 15 default configuration function.
 * @details This function executes a default configuration of LED Driver 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #leddriver15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver15_default_cfg ( leddriver15_t *ctx );

/**
 * @brief LED Driver 15 write register function.
 * @details This function writes data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver15_write_register ( leddriver15_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LED Driver 15 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver15_read_register ( leddriver15_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LED Driver 15 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void leddriver15_enable_device ( leddriver15_t *ctx );

/**
 * @brief LED Driver 15 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void leddriver15_disable_device ( leddriver15_t *ctx );

/**
 * @brief LED Driver 15 set i2c dimming function.
 * @details This function sets the LEDs dimming level in I2C mode.
 * @param[in] ctx : Click context object.
 * See #leddriver15_t object definition for detailed explanation.
 * @param[in] dimming : LEDs dimming level [0,31].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver15_set_i2c_dimming ( leddriver15_t *ctx, uint8_t dimming );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER15_H

/*! @} */ // leddriver15

// ------------------------------------------------------------------------ END
