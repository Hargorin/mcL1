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
 *  userConfig.c
 * 
 * Description:
 *  This file allows the user to make the allowed configurations.
*******************************************************************************/

#ifndef USERCONFIG_H
#define	USERCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif
/**
 * Config option CODEC_SAMPLE_RATE<p>
 * Allowed options: 8000L, 32000L, 44100L, 48000L, 88200L, 96000L 
 */
#define CODEC_SAMPLE_RATE 48000L
/**
 * Config option BAUDRATE<p>
 * Defines de baudrate for the UART2 interface that connects to the "Control Header".
 * Recommended: 115200
 */  
#define UART2_BAUDRATE 115200


#ifdef	__cplusplus
}
#endif

#endif	/* USERCONFIG_H */

