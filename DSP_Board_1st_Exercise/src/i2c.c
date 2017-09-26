/*******************************************************************************
 * FHNW, Labor mcL1
 * 1st_Exercise_Vorlage
 *
 * Aufgabe
 *       Folgende Dateien sind zu vervollständigen:
 *      - dci.c
 *      - dma.c
 *      - i2c.c
 *      - tlv320aic.c
 *  
*******************************************************************************/


#include <p33EP256MU806.h>
#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"
#include "constants.h"

/**************************************************************************
 * Initiation
 ***************************************************************************/

void i2c_init(uint32_t fsys)
{
    I2C1CON = 0x00;
            
    I2C1CONbits.A10M = 0;
    I2C1BRG = (uint16_t)((1.0/I2C_CLK_SPEED) * fsys/2.0) - 2;
    I2C1CONbits.I2CEN = 1;
}

/***************************************************************************
 * Private Functions
 ***************************************************************************/

void StartI2C1(void)
{
    I2C1CONbits.SEN = 1;
}

void WaitForIdleI2C1(void)
{
    while(  I2C1CONbits.SEN == 1 || 
            I2C1CONbits.PEN == 1 || 
            I2C1CONbits.RCEN == 1 || 
            I2C1CONbits.ACKEN == 1 || 
            I2C1STATbits.TRSTAT == 1 )
    {}
}

char MasterWriteI2C1(uint8_t data_out)
{
    I2C1TRN = data_out;
    
    if (I2C1STATbits.IWCOL == 1) {
        I2C1STATbits.IWCOL = 0;
        return -1;
    }
    return 0;
}

void StopI2C1(void)
{
    I2C1CONbits.PEN = 1;
}

/**************************************************************************
 * Public Functions
 ***************************************************************************/

int i2c_write(uint8_t *i2cData, uint16_t nData)
{
    StartI2C1();
    WaitForIdleI2C1();
    
    int i;
    for (i = 0; i < nData; i++) {
        MasterWriteI2C1(i2cData[i]);
        WaitForIdleI2C1();
    }
            
    StopI2C1();
    WaitForIdleI2C1();
    
    if (I2C1STATbits.ACKSTAT == 0) {
        return -1;
    }
    return 0;
}

