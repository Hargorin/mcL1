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
 *  globals.h
 * 
 * Description:
 *  This file contains the global buffers and variables.
*******************************************************************************/

#ifndef GLOBALS_H
#define	GLOBALS_H

#include "constants.h"

#define USE_USBCDC 

extern int txBufferA[BUFFERLENGTH] __attribute__((space(dma)));
extern int txBufferB[BUFFERLENGTH] __attribute__((space(dma)));
extern int rxBufferA[BUFFERLENGTH] __attribute__((space(dma)));
extern int rxBufferB[BUFFERLENGTH] __attribute__((space(dma)));

extern volatile unsigned char switchStates;
extern volatile unsigned char switchStatesChanged;

#endif	/* GLOBALS_H */

