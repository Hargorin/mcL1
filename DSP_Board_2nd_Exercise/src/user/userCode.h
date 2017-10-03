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
 *  userCode.h
 * 
 * Description:
 *  This file contains the user specific instructions that will be called at 
 *  the correct location in the main loop.
*******************************************************************************/

#ifndef USERCODE_H
#define	USERCODE_H

#ifdef	__cplusplus
extern "C"
{
#endif
#include <dsp.h>

void user_init();
void user_mainLoop();
void user_processData(fractional *targetBuffer, fractional *sourceBuffer);

//DEBUG for measurement
extern volatile int8_t mode;
extern uint16_t freq;

#ifdef	__cplusplus
}
#endif

#endif	/* USERCODE_H */

