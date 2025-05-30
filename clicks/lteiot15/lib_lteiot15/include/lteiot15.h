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
 * @file lteiot15.h
 * @brief This file contains API for LTE IoT 15 Click Driver.
 */

#ifndef LTEIOT15_H
#define LTEIOT15_H

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
 * @addtogroup lteiot15 LTE IoT 15 Click Driver
 * @brief API for configuring and manipulating LTE IoT 15 Click driver.
 * @{
 */

/**
 * @defgroup lteiot15_cmd LTE IoT 15 Device Settings
 * @brief Settings for registers of LTE IoT 15 Click driver.
 */

/**
 * @addtogroup lteiot15_cmd
 * @{
 */

/**
 * @brief LTE IoT 15 control commands.
 * @details Specified setting for control commands of LTE IoT 15 Click driver.
 */
#define LTEIOT15_CMD_AT                             "AT"
#define LTEIOT15_CMD_GET_MODEL_ID                   "AT+CGMM"
#define LTEIOT15_CMD_GET_SW_VERSION                 "AT+CGMR"
#define LTEIOT15_CMD_GET_SERIAL_NUM                 "AT+CGSN"
#define LTEIOT15_CMD_FACTORY_RESET                  "AT&F"
#define LTEIOT15_CMD_SET_MODULE_FUNCTIONALITY       "AT+CFUN"
#define LTEIOT15_CMD_EPS_NETWORK_REGISTRATION       "AT+CEREG"
#define LTEIOT15_CMD_SIGNAL_QUALITY_REPORT          "AT+CSQ"
#define LTEIOT15_CMD_OPERATOR_SELECTION             "AT+COPS"
#define LTEIOT15_CMD_SEND_SMS                       "AT+CMGS"
#define LTEIOT15_CMD_SELECT_SMS_FORMAT              "AT+CMGF"
#define LTEIOT15_CMD_DEFINE_PDP_CONTEXT             "AT+CGDCONT"
#define LTEIOT15_CMD_SHOW_PDP_ADDRESS               "AT+CGPADDR"
#define LTEIOT15_CMD_ACTIVATE_PDP_CONTEXT           "AT+CGACT"
#define LTEIOT15_CMD_PSD_CONFIG                     "AT+UPSD"
#define LTEIOT15_CMD_PSD_ACTION                     "AT+UPSDA"
#define LTEIOT15_CMD_CREATE_SOCKET                  "AT+USOCR"
#define LTEIOT15_CMD_CLOSE_SOCKET                   "AT+USOCL"
#define LTEIOT15_CMD_CONNECT_SOCKET                 "AT+USOCO"
#define LTEIOT15_CMD_WRITE_SOCKET_DATA              "AT+USOWR"
#define LTEIOT15_CMD_READ_SOCKET_DATA               "AT+USORD"
#define LTEIOT15_CMD_GPIO_CONFIG                    "AT+UGPIOC"

/**
 * @brief LTE IoT 15 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT15_RSP_OK                             "OK"
#define LTEIOT15_RSP_ERROR                          "ERROR"

/**
 * @brief LTE IoT 15 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTEIOT15_URC_CREATE_SOCKET                  "+USOCR: "
#define LTEIOT15_URC_RECEIVED_DATA                  "+UUSORD: "

/**
 * @brief LTE IoT 15 power state settings.
 * @details Specified power state settings of LTE IoT 15 Click driver.
 */
#define LTEIOT15_POWER_STATE_OFF                    0
#define LTEIOT15_POWER_STATE_ON                     1
#define LTEIOT15_POWER_STATE_RESET                  2

/**
 * @brief LTE IoT 15 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTEIOT15_TX_DRV_BUFFER_SIZE                 300
#define LTEIOT15_RX_DRV_BUFFER_SIZE                 300

/*! @} */ // lteiot15_cmd

/**
 * @defgroup lteiot15_map LTE IoT 15 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 15 Click driver.
 */

/**
 * @addtogroup lteiot15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 15 Click to the selected MikroBUS.
 */
#define LTEIOT15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot15_map
/*! @} */ // lteiot15

/**
 * @brief LTE IoT 15 Click context object.
 * @details Context object definition of LTE IoT 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;              /**< Power pin. */
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t rts;              /**< UART ready to send pin. */

    // Input pins
    digital_in_t ring;              /**< Ring indicator pin. */
    digital_in_t cts;               /**< UART clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTEIOT15_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTEIOT15_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTEIOT15_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lteiot15_t;

/**
 * @brief LTE IoT 15 Click configuration object.
 * @details Configuration object definition of LTE IoT 15 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t pwr;                 /**< Power pin. */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t rts;                 /**< UART ready to send pin. */
    pin_name_t ring;                /**< Ring indicator pin. */
    pin_name_t cts;                 /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} lteiot15_cfg_t;

/**
 * @brief LTE IoT 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT15_OK = 0,
    LTEIOT15_ERROR = -1,
    LTEIOT15_ERROR_TIMEOUT = -2,
    LTEIOT15_ERROR_CMD = -3

} lteiot15_return_value_t;

/*!
 * @addtogroup lteiot15 LTE IoT 15 Click Driver
 * @brief API for configuring and manipulating LTE IoT 15 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot15_cfg_setup ( lteiot15_cfg_t *cfg );

/**
 * @brief LTE IoT 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot15_init ( lteiot15_t *ctx, lteiot15_cfg_t *cfg );

/**
 * @brief LTE IoT 15 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot15_generic_write ( lteiot15_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE IoT 15 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot15_generic_read ( lteiot15_t *ctx, uint8_t *data_out, uint16_t len );


/**
 * @brief LTE IoT 15 set PWR pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot15_set_pwr_pin ( lteiot15_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 15 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot15_set_rst_pin ( lteiot15_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 15 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot15_set_rts_pin ( lteiot15_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 15 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot15_get_ring_pin ( lteiot15_t *ctx );

/**
 * @brief LTE IoT 15 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot15_get_cts_pin ( lteiot15_t *ctx );

/**
 * @brief LTE IoT 15 set power state function.
 * @details This function sets a desired power state by toggling PWR and RST pins with a specific timing.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void lteiot15_set_power_state ( lteiot15_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 15 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot15_cmd_run ( lteiot15_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 15 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lteiot15_cmd_set ( lteiot15_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LTE IoT 15 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot15_cmd_get ( lteiot15_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 15 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot15_cmd_help ( lteiot15_t *ctx, uint8_t *cmd );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void lteiot15_set_sim_apn ( lteiot15_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE IoT 15 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void lteiot15_send_sms_text ( lteiot15_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 15 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot15_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot15_send_sms_pdu ( lteiot15_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT15_H

/*! @} */ // lteiot15

// ------------------------------------------------------------------------ END
