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
 * @file stepper20.h
 * @brief This file contains API for Stepper 20 Click Driver.
 */

#ifndef STEPPER20_H
#define STEPPER20_H

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
 * @addtogroup stepper20 Stepper 20 Click Driver
 * @brief API for configuring and manipulating Stepper 20 Click driver.
 * @{
 */

/**
 * @defgroup stepper20_reg Stepper 20 Registers List
 * @brief List of registers of Stepper 20 Click driver.
 */

/**
 * @addtogroup stepper20_reg
 * @{
 */

/**
 * @brief Stepper 20 PCA9538A registers.
 * @details Specified PCA9538A registers of Stepper 20 Click driver.
 */
#define STEPPER20_REG_INPUT                      0x00
#define STEPPER20_REG_OUTPUT                     0x01
#define STEPPER20_REG_POLARITY                   0x02
#define STEPPER20_REG_CONFIG                     0x03

/*! @} */ // stepper20_reg

/**
 * @defgroup stepper20_set Stepper 20 Registers Settings
 * @brief Settings for registers of Stepper 20 Click driver.
 */

/**
 * @addtogroup stepper20_set
 * @{
 */

/**
 * @brief Stepper 20 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Stepper 20 Click driver.
 */
#define STEPPER20_DMODE0_PIN                     0x01
#define STEPPER20_DMODE1_PIN                     0x02
#define STEPPER20_DMODE2_PIN                     0x04
#define STEPPER20_SLEEP_X_PIN                    0x08
#define STEPPER20_LO_PIN                         0x10
#define STEPPER20_MO_PIN                         0x20

/**
 * @brief Stepper 20 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Stepper 20 Click driver.
 */
#define STEPPER20_DEFAULT_CONFIG                 0xF0

/**
 * @brief Stepper 20 direction setting.
 * @details Specified setting for direction of Stepper 20 Click driver.
 */
#define STEPPER20_DIR_CCW                        0
#define STEPPER20_DIR_CW                         1

/**
 * @brief Stepper 20 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 20 Click driver.
 */
#define STEPPER20_PIN_LOW_LEVEL                  0
#define STEPPER20_PIN_HIGH_LEVEL                 1

/**
 * @brief Stepper 20 step resolution setting.
 * @details Specified setting for step resolution of Stepper 20 Click driver.
 */
#define STEPPER20_MODE_FULL_STEP                 0x00
#define STEPPER20_MODE_HALF_STEP                 0x01
#define STEPPER20_MODE_QUARTER_STEP              0x02
#define STEPPER20_MODE_1_OVER_8                  0x03
#define STEPPER20_MODE_1_OVER_16                 0x04
#define STEPPER20_MODE_1_OVER_32                 0x05
#define STEPPER20_MODE_MASK                      0x07

/**
 * @brief Stepper 20 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER20_SPEED_VERY_SLOW                0
#define STEPPER20_SPEED_SLOW                     1
#define STEPPER20_SPEED_MEDIUM                   2
#define STEPPER20_SPEED_FAST                     3
#define STEPPER20_SPEED_VERY_FAST                4 

/**
 * @brief Stepper 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 20 Click driver.
 */
#define STEPPER20_DEVICE_ADDRESS_A1A0_00         0x70
#define STEPPER20_DEVICE_ADDRESS_A1A0_01         0x71
#define STEPPER20_DEVICE_ADDRESS_A1A0_10         0x72
#define STEPPER20_DEVICE_ADDRESS_A1A0_11         0x73

/*! @} */ // stepper20_set

/**
 * @defgroup stepper20_map Stepper 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 20 Click driver.
 */

/**
 * @addtogroup stepper20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 20 Click to the selected MikroBUS.
 */
#define STEPPER20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper20_map
/*! @} */ // stepper20

/**
 * @brief Stepper 20 Click context object.
 * @details Context object definition of Stepper 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable output pin. */
    digital_out_t dir;          /**< Direction control pin. */
    digital_out_t rst;          /**< Electric angle reset pin. */
    digital_out_t clk;          /**< Clock signal input pin. */

    // Input pins
    digital_in_t int_pin;       /**< PCA9538A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepper20_t;

/**
 * @brief Stepper 20 Click configuration object.
 * @details Configuration object definition of Stepper 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable output pin. */
    pin_name_t dir;             /**< Direction control pin. */
    pin_name_t rst;             /**< Electric angle reset pin. */
    pin_name_t clk;             /**< Clock signal input pin. */
    pin_name_t int_pin;         /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepper20_cfg_t;

/**
 * @brief Stepper 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER20_OK = 0,
    STEPPER20_ERROR = -1

} stepper20_return_value_t;

/*!
 * @addtogroup stepper20 Stepper 20 Click Driver
 * @brief API for configuring and manipulating Stepper 20 Click driver.
 * @{
 */

/**
 * @brief Stepper 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper20_cfg_setup ( stepper20_cfg_t *cfg );

/**
 * @brief Stepper 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_init ( stepper20_t *ctx, stepper20_cfg_t *cfg );

/**
 * @brief Stepper 20 default configuration function.
 * @details This function executes a default configuration of Stepper 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper20_default_cfg ( stepper20_t *ctx );

/**
 * @brief Stepper 20 write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_write_register ( stepper20_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 20 read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_read_register ( stepper20_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 20 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_get_step_mode ( stepper20_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 20 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_set_step_mode ( stepper20_t *ctx, uint8_t mode );

/**
 * @brief Stepper 20 get sleep x pin function.
 * @details This function reads the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_get_sleep_x_pin ( stepper20_t *ctx, uint8_t *state );

/**
 * @brief Stepper 20 set sleep x pin function.
 * @details This function sets the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_set_sleep_x_pin ( stepper20_t *ctx, uint8_t state );

/**
 * @brief Stepper 20 get lo pin function.
 * @details This function reads the lo pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_get_lo_pin ( stepper20_t *ctx, uint8_t *state );

/**
 * @brief Stepper 20 get mo pin function.
 * @details This function reads the mo pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper20_get_mo_pin ( stepper20_t *ctx, uint8_t *state );

/**
 * @brief Stepper 20 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return None.
 * @note None.
 */
void stepper20_drive_motor ( stepper20_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 20 enable device function.
 * @details This function enables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper20_enable_device ( stepper20_t *ctx );

/**
 * @brief Stepper 20 disable device function.
 * @details This function disables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper20_disable_device ( stepper20_t *ctx );

/**
 * @brief Stepper 20 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper20_set_direction ( stepper20_t *ctx, uint8_t dir );

/**
 * @brief Stepper 20 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper20_switch_direction ( stepper20_t *ctx );

/**
 * @brief Stepper 20 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper20_reset_device ( stepper20_t *ctx );

/**
 * @brief Stepper 20 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper20_get_int_pin ( stepper20_t *ctx );

/**
 * @brief Stepper 20 set clk pin function.
 * @details This function sets the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper20_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper20_set_clk_pin ( stepper20_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER20_H

/*! @} */ // stepper20

// ------------------------------------------------------------------------ END
