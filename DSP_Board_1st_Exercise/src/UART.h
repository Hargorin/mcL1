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
 *  UART.h
 * 
 * Description:
 *  This file implements the functionalities of the codec. The public functions
 *  can be used to control the codec.
*******************************************************************************/

#ifndef UART_H
#define	UART_H

#include <stdint.h>

void uart_init();
void uart_putChar(char c);
void uart_sendString(char* s);
int uart_getChar(char* c);


void Ext_UART_TxStart(void);
void Ext_WriteTxBuffer(char TxByte);


#endif	/* UART_H */

