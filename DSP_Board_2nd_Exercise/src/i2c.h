/*******************************************************************************
 * Project:
 *  "Neuentwicklung DSP-Board fuer das Labor MikroComm"
 * 
 * Version / Date:
 *  0.9 / August 2016
 * 
 * Authors:
 *  Simon Gerber, Belinda Kneubuehler
 * 
 * File Name:
 *  i2c.h
 * 
 * Description:
 *  This file initialises the I2C interface and provides the functions to read
 *  and write commands over the interface.
*******************************************************************************/

#ifndef I2C_H
#define	I2C_H

#include <stdint.h>

#define I2C_CLK_SPEED 400000

void i2c_init(uint32_t fsys);
int i2c_write(uint8_t *data, uint16_t DataSz);
void i2c_read(uint8_t address, uint16_t registerAdress, uint8_t *buffer, uint8_t size);


#endif	/* I2C_H */

