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
 * @file gnss16.h
 * @brief This file contains API for GNSS 16 Click Driver.
 */

#ifndef GNSS16_H
#define GNSS16_H

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
#include "drv_uart.h"

/*!
 * @addtogroup gnss16 GNSS 16 Click Driver
 * @brief API for configuring and manipulating GNSS 16 Click driver.
 * @{
 */

/**
 * @defgroup gnss16_cmd GNSS 16 Device Settings
 * @brief Settings for registers of GNSS 16 Click driver.
 */

/**
 * @addtogroup gnss16_cmd
 * @{
 */

/**
 * @brief GNSS 16 control commands.
 * @details Specified setting for control commands of GNSS 16 Click driver.
 */
#define GNSS16_RSP_START                              "$"
#define GNSS16_RSP_DELIMITER                          ","
#define GNSS16_RSP_GNGGA                              "$GNGGA"

/**
 * @brief GNSS 16 GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS 16 Click driver.
 */
#define GNSS16_GNGGA_ELEMENT_SIZE                     15
#define GNSS16_GNGGA_TIME                             1
#define GNSS16_GNGGA_LATITUDE                         2
#define GNSS16_GNGGA_LATITUDE_SIDE                    3
#define GNSS16_GNGGA_LONGITUDE                        4
#define GNSS16_GNGGA_LONGITUDE_SIDE                   5
#define GNSS16_GNGGA_QUALITY_INDICATOR                6
#define GNSS16_GNGGA_NUMBER_OF_SATELLITES             7
#define GNSS16_GNGGA_H_DILUTION_OF_POS                8
#define GNSS16_GNGGA_ALTITUDE                         9
#define GNSS16_GNGGA_ALTITUDE_UNIT                    10
#define GNSS16_GNGGA_GEOIDAL_SEPARATION               11
#define GNSS16_GNGGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS16_GNGGA_TIME_SINCE_LAST_DGPS             13
#define GNSS16_GNGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS 16 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS16_TX_DRV_BUFFER_SIZE                     100
#define GNSS16_RX_DRV_BUFFER_SIZE                     300

/*! @} */ // gnss16_cmd

/**
 * @defgroup gnss16_map GNSS 16 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 16 Click driver.
 */

/**
 * @addtogroup gnss16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 16 Click to the selected MikroBUS.
 */
#define GNSS16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX );  \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );  \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnss16_map
/*! @} */ // gnss16

/**
 * @brief GNSS 16 Click context object.
 * @details Context object definition of GNSS 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;       /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;    /**< Interrupt pin. */

    // Modules
    uart_t uart;             /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS16_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GNSS16_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} gnss16_t;

/**
 * @brief GNSS 16 Click configuration object.
 * @details Configuration object definition of GNSS 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;       /**< Reset pin. */
    pin_name_t int_pin;   /**< Interrupt pin. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} gnss16_cfg_t;

/**
 * @brief GNSS 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS16_OK = 0,
    GNSS16_ERROR = -1

} gnss16_return_value_t;

/*!
 * @addtogroup gnss16 GNSS 16 Click Driver
 * @brief API for configuring and manipulating GNSS 16 Click driver.
 * @{
 */

/**
 * @brief GNSS 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss16_cfg_setup ( gnss16_cfg_t *cfg );

/**
 * @brief GNSS 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss16_init ( gnss16_t *ctx, gnss16_cfg_t *cfg );

/**
 * @brief GNSS 16 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @note None.
 */
void gnss16_set_rst_pin ( gnss16_t *ctx, uint8_t state );

/**
 * @brief GNSS 16 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
void gnss16_reset_device ( gnss16_t *ctx );

/**
 * @brief GNSS 16 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss16_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss16_generic_write ( gnss16_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 16 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss16_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss16_generic_read ( gnss16_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 16 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss16_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

/**
 * @brief GNSS 16 get interrupt pin state function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss16_get_int_pin ( gnss16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // GNSS16_H

/*! @} */ // gnss16

// ------------------------------------------------------------------------ END
