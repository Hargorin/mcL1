/*******************************************************************************
 * Project:
 *  "Neuentwicklung DSP-Board fuer das Labor MikroComm"
 * 
 * Version / Date:
 *  0.9 / August 2016
 * 
 * Authors:
 *  Simon Gerber, Belinda Kneubuehler
 *  Hochschule fuer Technik, FHNW, Windisch
 * 
 * File Name:
 *  dma.h
 * 
 * Description:
 *  This file configures the DMA to work with the I2S interface.
*******************************************************************************/
#ifndef DMA_H
#define	DMA_H


#include "constants.h"

extern int txBufferA[BUFFERLENGTH] __attribute__((space(dma)));
extern int txBufferB[BUFFERLENGTH] __attribute__((space(dma)));
extern int rxBufferA[BUFFERLENGTH] __attribute__((space(dma)));
extern int rxBufferB[BUFFERLENGTH] __attribute__((space(dma)));

void dma_init(void);

#endif	/* DMA_H */

