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
 *  UART.c
 * 
 * Description:
 *  This file implements the functionalities to communicate over the UART2 
 *  interface. It contains functions to send and receive as well as interrupts.
*******************************************************************************/

#include <p33EP256MU806.h>
#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "UART.h"

/**************************************************************************
 * Global Definitions
 ***************************************************************************/
#define SIZE_TxBuffer 128

static volatile char txBuffer[SIZE_TxBuffer], *txBufRdPtr, *txBufWrPtr;    //Buffer and pointers for bytes to transmit

char uart_char;
volatile bool newchar = false;

/**************************************************************************
 * Initiation
 ***************************************************************************/

void uart_init()
{
    txBufRdPtr = txBufWrPtr = &txBuffer[0]; //Init read & write pointers of ringbuffer
    U2MODE = 0;
    U2STA = 0;

    U2BRG = UART_BRG_VAL;       // Calculated in UART.h

    IEC1bits.U2RXIE = 1;        //Enable RX Interrupt
    U2MODEbits.UARTEN = 1;      //UART Enable bit
    U2STAbits.UTXEN = 1;        //UART Transmit Enable bit
}
/**************************************************************************
 * Private Functions
 ***************************************************************************/

int write(int handle, void *buffer, unsigned int len)
{
    int i;
    switch (handle)
    {
    case 0: // handle 0 corresponds to stdout
    case 1: // handle 1 corresponds to stdin
    case 2: // handle 2 corresponds to stderr
    default:
        for (i = 0; i < len; i++)
            Ext_WriteTxBuffer(*(char*) buffer++);
            //uart_put_char(*(char*) buffer++);
        Ext_UART_TxStart();
        break;
    }
    return (len);
}

/**************************************************************************
 * Public Functions
 ***************************************************************************/

int uart_getChar(char* byte)
{
    int ret = 0;
    if (U2STAbits.UTXBF);   // buffer is full
    if (U2STAbits.URXDA)    // data available
    {
        *byte = (char) U2RXREG;
        ret = 1;
        if (U2STAbits.OERR)
        {
            U2STAbits.OERR = 0;
        }
    }
    return ret;
}

void uart_putChar(char byte)
{
    while (U2STAbits.UTXBF); // wait for TX buffer to be empty
    U2TXREG = byte;
}

void uart_sendString(char* s)
{
    int i;
    for (i = 0; s[i] != 0; i++)
        Ext_WriteTxBuffer(s[i]);
    Ext_UART_TxStart();
}


void Ext_UART_TxStart(void)
{
    IEC1bits.U2TXIE = 1;                    //Enable transmit interrupts
}

/**
 * Write a byte to the transmit buffer.
 * @param TxByte the buffer to write
 */
void Ext_WriteTxBuffer(char TxByte)
{
    *txBufWrPtr++ = TxByte;                 //Put the byte in the transmit buffer and increment the pointer
    if (txBufWrPtr > &txBuffer[SIZE_TxBuffer - 1]) //Check if at end of buffer
        txBufWrPtr = &txBuffer[0];          //Wrap pointer to beginning
}


/**************************************************************************
 * Interrupt Routines
 ***************************************************************************/

void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt(void)
{
    if (txBufRdPtr != txBufWrPtr)           //Check if more data is in the buffer
    {
        IFS1bits.U2TXIF = 0;                //Clear UART 2 Receive interrupt flag
        U2TXREG = *txBufRdPtr++;            //Get next byte from the buffer
        if (txBufRdPtr > &txBuffer[SIZE_TxBuffer - 1])  //Check if end of buffer
            txBufRdPtr = &txBuffer[0];      //Wrap pointer to beginning
    }
    else
        IEC1bits.U2TXIE = 0;                //No data so stop interrupts
}

void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void)
{
    newchar = true;
    IFS1bits.U2RXIF = 0;
    uart_getChar(&uart_char);
    uart_putChar(uart_char);

}