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
 *  constants.h
 * 
 * Description:
 *  This file defines the constants for the project. They should not be changed.
*******************************************************************************/

#ifndef CONSTANTS_H
#define	CONSTANTS_H
#include "user/userConfig.h"


#define USE_SDR 0

#define I2S_WORD_LENGTH 16

#define BUFFERBYTES 512
#define BUFFERLENGTH 256
#define BUFFERLENGTH_DIV_2 128
#define SDUNITSIZE 4096

#define FCY 69000000L
#define FCY_STARTUP 3650000L

#define PCM 1
#define PCMSIZE 16
#define CHANNELS 2
#define BITS_PER_SAMPLE 16
#define BYTERATE (CODEC_SAMPLE_RATE * CHANNELS * BITS_PER_SAMPLE / 8)
#define BLOCKALIGN (CHANNELS * BITS_PER_SAMPLE / 8)

#define CODEC_BOSR 250

#define DCI_BCG_VALUE ((FCY/(2*CODEC_SAMPLE_RATE*2*I2S_WORD_LENGTH))-1)

#define UART_BRG_VAL ((FCY/UART2_BAUDRATE)/16) - 1
#define BRG_115200 ((FCY + 230400) / 460800 - 1)        //BRG value for 115,200 baud with BRGH = 1 (with rounding)
/**
 * Mask for SW1.<p>
 * This mask determines if the switch is pushed.
 * The information in switchStates is already debounced. \n
 * switch pushed: (switchStates & SW1_MASK) == 1
 */
#define SW1_MASK 0b01
/**
 * Mask for SW2.<p>
 * This mask determines if the switch is pushed.
 * The information in switchStates is already debounced. \n
 * switch pushed: (switchStates & SW2_MASK) == 1
 */
#define SW2_MASK 0b10

#define MAX_FILENAME_LENGTH 8

#endif	/* CONSTANTS_H */

