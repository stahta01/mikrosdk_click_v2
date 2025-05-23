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
 * @file magicrfid.h
 * @brief This file contains API for Magic RFID Click Driver.
 */

#ifndef MAGICRFID_H
#define MAGICRFID_H

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
 * @addtogroup magicrfid Magic RFID Click Driver
 * @brief API for configuring and manipulating Magic RFID Click driver.
 * @{
 */

/**
 * @defgroup magicrfid_cmd Magic RFID Device Settings
 * @brief Settings for registers of Magic RFID Click driver.
 */

/**
 * @addtogroup magicrfid_cmd
 * @{
 */

/**
 * @brief Magic RFID control commands.
 * @details Specified setting for control commands of Magic RFID Click driver.
 */
#define MAGICRFID_OPCODE_VERSION                        0x03
#define MAGICRFID_OPCODE_SET_BAUD_RATE                  0x06
#define MAGICRFID_OPCODE_READ_TAG_ID_SINGLE             0x21
#define MAGICRFID_OPCODE_READ_TAG_ID_MULTIPLE           0x22
#define MAGICRFID_OPCODE_WRITE_TAG_ID                   0x23
#define MAGICRFID_OPCODE_WRITE_TAG_DATA                 0x24
#define MAGICRFID_OPCODE_KILL_TAG                       0x26
#define MAGICRFID_OPCODE_READ_TAG_DATA                  0x28
#define MAGICRFID_OPCODE_CLEAR_TAG_ID_BUFFER            0x2A
#define MAGICRFID_OPCODE_MULTI_PROTOCOL_TAG_OP          0x2F
#define MAGICRFID_OPCODE_GET_READ_TX_POWER              0x62
#define MAGICRFID_OPCODE_GET_WRITE_TX_POWER             0x64
#define MAGICRFID_OPCODE_GET_POWER_MODE                 0x68
#define MAGICRFID_OPCODE_GET_READER_OPTIONAL_PARAMS     0x6A
#define MAGICRFID_OPCODE_GET_PROTOCOL_PARAM             0x6B
#define MAGICRFID_OPCODE_SET_ANTENNA_PORT               0x91
#define MAGICRFID_OPCODE_SET_TAG_PROTOCOL               0x93
#define MAGICRFID_OPCODE_SET_READ_TX_POWER              0x92
#define MAGICRFID_OPCODE_SET_WRITE_TX_POWER             0x94
#define MAGICRFID_OPCODE_SET_REGION                     0x97
#define MAGICRFID_OPCODE_SET_READER_OPTIONAL_PARAMS     0x9A
#define MAGICRFID_OPCODE_SET_PROTOCOL_PARAM             0x9B

/**
 * @brief Magic RFID region commands.
 * @details Specified setting for region commands of Magic RFID Click driver.
 */
#define MAGICRFID_REGION_INDIA                          0x04
#define MAGICRFID_REGION_JAPAN                          0x05
#define MAGICRFID_REGION_CHINA                          0x06
#define MAGICRFID_REGION_EUROPE                         0x08
#define MAGICRFID_REGION_KOREA                          0x09
#define MAGICRFID_REGION_AUSTRALIA                      0x0B
#define MAGICRFID_REGION_NEWZEALAND                     0x0C
#define MAGICRFID_REGION_NORTHAMERICA                   0x0D
#define MAGICRFID_REGION_OPEN                           0xFF

/**
 * @brief Magic RFID tag protocol commands.
 * @details Specified setting for tag protocol commands of Magic RFID Click driver.
 */
#define MAGICRFID_TAG_PROTOCOL_NONE                     0x00
#define MAGICRFID_TAG_PROTOCOL_ISO180006B               0x03
#define MAGICRFID_TAG_PROTOCOL_GEN2                     0x05
#define MAGICRFID_TAG_PROTOCOL_ISO180006B_UCODE         0x06
#define MAGICRFID_TAG_PROTOCOL_IPX64                    0x07
#define MAGICRFID_TAG_PROTOCOL_IPX256                   0x08
#define MAGICRFID_TAG_PROTOCOL_ATA                      0x1D

/**
 * @brief Magic RFID timeout and delays.
 * @details Specified setting for timeout and delays of Magic RFID Click driver.
 */
#define MAGICRFID_NORMAL_DELAY_TIME                     50
#define MAGICRFID_LONG_DELAY_TIME                       100
#define MAGICRFID_TIMEOUT_MS                            3000

/**
 * @brief Magic RFID command and response settings.
 * @details Specified setting for command and response of Magic RFID Click driver.
 */
#define MAGICRFID_HEADER                                0xFF
#define MAGICRFID_COMMAND_MAX_DATA_LEN                  250
#define MAGICRFID_RESPONSE_MAX_DATA_LEN                 248
#define MAGICRFID_EPC_MAX_DATA_LEN                      16

/**
 * @brief Magic RFID driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define MAGICRFID_TX_DRV_BUFFER_SIZE                    255
#define MAGICRFID_RX_DRV_BUFFER_SIZE                    255

/*! @} */ // magicrfid_cmd

/**
 * @defgroup magicrfid_map Magic RFID MikroBUS Map
 * @brief MikroBUS pin mapping of Magic RFID Click driver.
 */

/**
 * @addtogroup magicrfid_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magic RFID Click to the selected MikroBUS.
 */
#define MAGICRFID_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // magicrfid_map
/*! @} */ // magicrfid

/**
 * @brief Magic RFID Click context object.
 * @details Context object definition of Magic RFID Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Shutdown Control. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ MAGICRFID_RX_DRV_BUFFER_SIZE ];     /**< Buffer size. */
    uint8_t uart_tx_buffer[ MAGICRFID_TX_DRV_BUFFER_SIZE ];     /**< Buffer size. */

} magicrfid_t;

/**
 * @brief Magic RFID Click configuration object.
 * @details Configuration object definition of Magic RFID Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;          /**< Shutdown Control. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} magicrfid_cfg_t;

/**
 * @brief Magic RFID Click command object.
 * @details Command object definition of Magic RFID Click driver.
 */
typedef struct
{
    uint8_t data_len;
    uint8_t opcode;
    uint8_t data_buf[ MAGICRFID_COMMAND_MAX_DATA_LEN ];

} magicrfid_command_t;

/**
 * @brief Magic RFID Click response object.
 * @details Response object definition of Magic RFID Click driver.
 */
typedef struct
{
    uint8_t data_len;
    uint8_t opcode;
    uint16_t status;
    uint8_t data_buf[ MAGICRFID_RESPONSE_MAX_DATA_LEN ];

} magicrfid_response_t;

/**
 * @brief Magic RFID Click EPC data object.
 * @details EPC data object definition of Magic RFID Click driver.
 */
typedef struct
{
    uint8_t data_len;
    uint16_t epc_pc;
    uint8_t data_buf[ MAGICRFID_EPC_MAX_DATA_LEN ];
    uint16_t epc_crc;

} magicrfid_epc_t;

/**
 * @brief Magic RFID Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGICRFID_OK = 0,
    MAGICRFID_ERROR = -1

} magicrfid_return_value_t;

/*!
 * @addtogroup magicrfid Magic RFID Click Driver
 * @brief API for configuring and manipulating Magic RFID Click driver.
 * @{
 */

/**
 * @brief Magic RFID configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magicrfid_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magicrfid_cfg_setup ( magicrfid_cfg_t *cfg );

/**
 * @brief Magic RFID initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magicrfid_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magicrfid_init ( magicrfid_t *ctx, magicrfid_cfg_t *cfg );

/**
 * @brief Magic RFID default configuration function.
 * @details This function executes a default configuration of Magic RFID
 * Click board.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void magicrfid_default_cfg ( magicrfid_t *ctx );

/**
 * @brief Magic RFID data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t magicrfid_generic_write ( magicrfid_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Magic RFID data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 */
err_t magicrfid_generic_read ( magicrfid_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Magic RFID device reset function.
 * @details Device reset and wake up module.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @return Nothing.
 */
void magicrfid_device_reset ( magicrfid_t *ctx );

/**
 * @brief Magic RFID send command function.
 * @details Send command function.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] cmd : Command object.
 * See #magicrfid_command_t object definition for detailed explanation.
 * @return Nothing.
 */
void magicrfid_send_command ( magicrfid_t *ctx, magicrfid_command_t cmd );

/**
 * @brief Magic RFID get response function.
 * @details Get response function.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[out] rsp : Response object.
 * See #magicrfid_response_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t magicrfid_get_response ( magicrfid_t *ctx, magicrfid_response_t *rsp );

/**
 * @brief Parse Tag RSSI value.
 * @details This function parses RSSI value of the tag.
 * @param[in] rsp : Response object.
 * See #magicrfid_response_t object definition for detailed explanation.
 * @return RSSI value
 */
int8_t magicrfid_parse_tag_rssi ( magicrfid_response_t rsp );

/**
 * @brief Parse Tag Freq value.
 * @details This function parses the frequency value the tag was detected at.
 * @param[in] rsp : Response object.
 * See #magicrfid_response_t object definition for detailed explanation.
 * @return Frequency value.
 */
uint32_t magicrfid_parse_tag_freq ( magicrfid_response_t rsp );

/**
 * @brief Parse Tag EPC bytes.
 * @details This function parses EPC bytes of the tag.
 * @param[in] rsp : Response object.
 * See #magicrfid_response_t object definition for detailed explanation.
 * @param[out] epc : EPC data object.
 * See #magicrfid_epc_t object definition for detailed explanation.
 * @return Nothing.
 */
void magicrfid_parse_tag_epc ( magicrfid_response_t rsp, magicrfid_epc_t *epc );

/**
 * @brief Magic RFID set protocol function.
 * @details This function is used for setting up protocol of Magic RFID Click Board by using UART 
 * serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] protocol : Selected protocol.
 * @return Nothing.
 */
void magicrfid_set_tag_protocol ( magicrfid_t *ctx, uint8_t protocol );

/**
 * @brief Magic RFID set region function.
 * @details This function is used for setting up region of Magic RFID Click Board by using UART 
 * serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] region : Selected region.
 * @return Nothing.
 */
void magicrfid_set_region ( magicrfid_t *ctx, uint8_t region );

/**
 * @brief Magic RFID turn on antenna port function.
 * @details This function is used for setting up antenna port of Magic RFID Click Board by using 
 * UART serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @return Nothing.
 */
void magicrfid_set_antenna_port ( magicrfid_t *ctx );

/**
 * @brief Magic RFID set baud rate function.
 * @details This function is used for setting up baud rate of Magic RFID Click Board by using UART 
 * serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] baud_rate : Baud rate value.
 * @return Nothing.
 */
void magicrfid_set_baud_rate ( magicrfid_t *ctx, uint32_t baud_rate );

/**
 * @brief Magic RFID set read function power.
 * @details This function is used for setting up read power of Magic RFID Click Board in dBm by 
 * using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] power_setting : Power setting value in dBm.
 * @return Nothing.
 */
void magicrfid_set_read_power ( magicrfid_t *ctx, uint16_t power_setting );

/**
 * @brief Magic RFID set write function power.
 * @details This function is used for setting up write power of Magic RFID Click Board in dBm by 
 * using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @param[in] power_setting : Power setting value in dBm.
 * @return Nothing.
 */
void magicrfid_set_write_power ( magicrfid_t *ctx, uint16_t power_setting );

/**
 * @brief Magic RFID set reader configuration function.
 * @details This function is used for sending optional parameters to Magic RFID Click BoardSends 
 * optional parameters by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @return Nothing.
 */
void magicrfid_set_reader_config ( magicrfid_t *ctx, uint8_t option1, uint8_t option2 );

/**
 * @brief Magic RFID enable reading function.
 * @details This function is used for setting up Magic RFID Click Board in continuous reading mode 
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @return Nothing.
 */
void magicrfid_start_reading ( magicrfid_t *ctx );

/**
 * @brief Magic RFID clear buffers function.
 * @details This function clears UART ring buffers.
 * @param[in] ctx : Click context object.
 * See #magicrfid_t object definition for detailed explanation.
 * @return Nothing.
 */
void magicrfid_clear_buffers ( magicrfid_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MAGICRFID_H

/*! @} */ // magicrfid

// ------------------------------------------------------------------------ END
