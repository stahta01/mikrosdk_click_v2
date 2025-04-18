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
 * @file rotaryo2.h
 * @brief This file contains API for Rotary O 2 Click Driver.
 */

#ifndef ROTARYO2_H
#define ROTARYO2_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup rotaryo2 Rotary O 2 Click Driver
 * @brief API for configuring and manipulating Rotary O 2 Click driver.
 * @{
 */

/**
 * @defgroup rotaryo2_set Rotary O 2 Registers Settings
 * @brief Settings for registers of Rotary O 2 Click driver.
 */

/**
 * @addtogroup rotaryo2_set
 * @{
 */

/**
 * @brief Rotary O 2 led data values.
 * @details Led data values of Rotary O 2 Click driver.
 */
#define ROTARYO2_SET_LED_OFF               0x0000u
#define ROTARYO2_SET_LED_DATA_1            0x0001u
#define ROTARYO2_SET_LED_DATA_2            0x0002u
#define ROTARYO2_SET_LED_DATA_3            0x0004u
#define ROTARYO2_SET_LED_DATA_4            0x0008u
#define ROTARYO2_SET_LED_DATA_5            0x0010u
#define ROTARYO2_SET_LED_DATA_6            0x0020u
#define ROTARYO2_SET_LED_DATA_7            0x0040u
#define ROTARYO2_SET_LED_DATA_8            0x0080u
#define ROTARYO2_SET_LED_DATA_9            0x0100u
#define ROTARYO2_SET_LED_DATA_10           0x0200u
#define ROTARYO2_SET_LED_DATA_11           0x0400u
#define ROTARYO2_SET_LED_DATA_12           0x0800u
#define ROTARYO2_SET_LED_DATA_13           0x1000u
#define ROTARYO2_SET_LED_DATA_14           0x2000u
#define ROTARYO2_SET_LED_DATA_15           0x4000u
#define ROTARYO2_SET_LED_DATA_16           0x8000u

/**
 * @brief Rotary O 2 led position values.
 * @details Led position values of Rotary O 2 Click driver.
 */
#define ROTARYO2_SET_LED_POS_1             1 
#define ROTARYO2_SET_LED_POS_2             2 
#define ROTARYO2_SET_LED_POS_3             3 
#define ROTARYO2_SET_LED_POS_4             4 
#define ROTARYO2_SET_LED_POS_5             5 
#define ROTARYO2_SET_LED_POS_6             6 
#define ROTARYO2_SET_LED_POS_7             7 
#define ROTARYO2_SET_LED_POS_8             8 
#define ROTARYO2_SET_LED_POS_9             9 
#define ROTARYO2_SET_LED_POS_10            10
#define ROTARYO2_SET_LED_POS_11            11
#define ROTARYO2_SET_LED_POS_12            12
#define ROTARYO2_SET_LED_POS_13            13
#define ROTARYO2_SET_LED_POS_14            14
#define ROTARYO2_SET_LED_POS_15            15
#define ROTARYO2_SET_LED_POS_16            16

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b rotaryo2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ROTARYO2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ROTARYO2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // rotaryo2_set

/**
 * @defgroup rotaryo2_map Rotary O 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Rotary O 2 Click driver.
 */

/**
 * @addtogroup rotaryo2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Rotary O 2 Click to the selected MikroBUS.
 */
#define ROTARYO2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.enb  = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.ena  = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.sw   = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rotaryo2_map
/*! @} */ // rotaryo2

/**
 * @brief Rotary O 2 Click context object.
 * @details Context object definition of Rotary O 2 Click driver.
 */
typedef struct
{
   // Input pins
    digital_in_t enb;            /**< Rotary encoder B signal. */
    digital_in_t ena;            /**< Rotary encoder A signal. */
    digital_in_t sw;             /**< Rotary encoder switch signal. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} rotaryo2_t;

/**
 * @brief Rotary O 2 Click configuration object.
 * @details Configuration object definition of Rotary O 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t enb;             /**< Rotary encoder B signal. */
    pin_name_t ena;             /**< Rotary encoder A signal. */
    pin_name_t sw;              /**< Rotary encoder switch signal. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} rotaryo2_cfg_t;

/**
 * @brief Rotary O 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ROTARYO2_OK = 0,
    ROTARYO2_ERROR = -1

} rotaryo2_return_value_t;

/*!
 * @addtogroup rotaryo2 Rotary O 2 Click Driver
 * @brief API for configuring and manipulating Rotary O 2 Click driver.
 * @{
 */

/**
 * @brief Rotary O 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rotaryo2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rotaryo2_cfg_setup ( rotaryo2_cfg_t *cfg );

/**
 * @brief Rotary O 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rotaryo2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryo2_init ( rotaryo2_t *ctx, rotaryo2_cfg_t *cfg );

/**
 * @brief Rotary O 2 default configuration function.
 * @details This function executes a default configuration of Rotary O 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rotaryo2_default_cfg ( rotaryo2_t *ctx );

/**
 * @brief Rotary O 2 set LED data function.
 * @details This function, using SPI serial interface, writes a desired 16-bit data 
 * of the TLC5925, Low-Power 16-Channel Constant-Current LED Sink Driver
 * on the Rotary O 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryo2_set_led_data ( rotaryo2_t *ctx, uint16_t data_in );

/**
 * @brief Rotary O 2 get LED data function.
 * @details This function, using SPI serial interface, reads a 16-bit data
 * from the TLC5925, Low-Power 16-Channel Constant-Current LED Sink Driver
 * on the Rotary O 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryo2_get_led_data ( rotaryo2_t *ctx, uint16_t *data_out );

/**
 * @brief Rotary O 2 set LED position function.
 * @details This function turns on the LED for the selected LED position
 * of the TLC5925, Low-Power 16-Channel Constant-Current LED Sink Driver
 * on the Rotary O 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @param[in] led_pos : LED position [1-16].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryo2_set_led_pos ( rotaryo2_t *ctx, uint8_t led_pos );

/**
 * @brief Rotary O 2 get switch state function.
 * @details This function return rotary encoder switch signal, states of the SW(INT) pin
 * of the EC12D1564402 on the Rotary O 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @return @li @c 0 - Released state,
 *         @li @c 1 - Pressed state.
 * @note None.
 */
uint8_t rotaryo2_get_state_switch ( rotaryo2_t *ctx );

/**
 * @brief Rotary O 2 get ena state function.
 * @details This function return rotary encoder A signal, states of the ENA(PWM) pin
 * of the EC12D1564402 on the Rotary O 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @return @li @c 0 - Low state,
 *         @li @c 1 - High state.
 * @note None.
 */
uint8_t rotaryo2_get_state_ena ( rotaryo2_t *ctx );

/**
 * @brief Rotary O 2 get enb state function.
 * @details This function return rotary encoder A signal, states of the ENB(PWM) pin
 * of the EC12D1564402 on the Rotary O 2 Click board?.
 * @param[in] ctx : Click context object.
 * See #rotaryo2_t object definition for detailed explanation.
 * @return @li @c 0 - Low state,
 *         @li @c 1 - High state.
 * @note None.
 */
uint8_t rotaryo2_get_state_enb ( rotaryo2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ROTARYO2_H

/*! @} */ // rotaryo2

// ------------------------------------------------------------------------ END
