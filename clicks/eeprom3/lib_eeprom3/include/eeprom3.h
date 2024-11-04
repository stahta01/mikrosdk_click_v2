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
 * \brief This file contains API for EEPROM 3 Click driver.
 *
 * \addtogroup eeprom3 EEPROM 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EEPROM3_H
#define EEPROM3_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define EEPROM3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EEPROM3_OK          0
#define EEPROM3_ERROR      -1
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} eeprom3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} eeprom3_cfg_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void eeprom3_cfg_setup ( eeprom3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t eeprom3_init ( eeprom3_t *ctx, eeprom3_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx                  Click object.
 * @param reg_address          Register address.
 * @param data_in              Data to be written.
 *
 * @details This function writes data to the desired register.
 */
void eeprom3_write_byte ( eeprom3_t *ctx, uint16_t reg_address, uint8_t data_in );

/**
 * @brief Generic write page function.
 *
 * @param ctx                  Click object.
 * @param reg_address          Register address.
 * @param data_in              Data to be written.
 * @param count                Number of bytes to be written.
 * @details This function writes given number of data to the desired register.
 */
void eeprom3_write_page( eeprom3_t *ctx, uint16_t reg_address, uint8_t* data_in, uint8_t count );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_out     Output data.
 * @param count        Number of the bytes to be read.
 *
 * @details This function reads data from the desired register.
 */
void eeprom3_read ( eeprom3_t *ctx, uint16_t reg_address, uint8_t *data_out, uint16_t count );

#ifdef __cplusplus
}
#endif
#endif  // _EEPROM3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
