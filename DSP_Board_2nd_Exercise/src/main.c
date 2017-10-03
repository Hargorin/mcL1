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
 *  main.c
 * 
 * Description:
 *  The main file of the project. This contains the interrupt routines.
*******************************************************************************/

#include "constants.h"
#include <p33EP256MU806.h>
#include <libpic30.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "IOconfig.h"
#include "init.h"
#include "i2c.h"
#include "dma.h"
#include "dci.h"
#include "tlv320aic.h"
#include "globals.h"
#include "pwm.h"
#include "UART.h"

// USER
#include "user/userCode.h"
#include "user/userConfig.h"


/**************************************************************************
 * configuration bits
 ***************************************************************************/

/* Initial Oscillator Source = FRC
 * Two Speed Oscillator Startup = Start device with the user-selected
 * oscillator source*/
//_FOSCSEL(FNOSC_FRC & IESO_OFF);
#pragma config FNOSC=FRC
#pragma config IESO=OFF

/* Clock Switching Mode = Clock switching is enabled; 
 * Fail-Safe Clock Monitor is disabled
 * OSC2 Pin Function bit = OSC2 is clock output
 * Primary Oscillator Mode Select bits = EC (External Clock) mode */
//_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_EC);
#pragma config FCKSM=CSECMD
#pragma config OSCIOFNC=OFF
#pragma config POSCMD=EC
//_FOSC(FCKSM_CSECME & OSCIOFNC_OFF );

/* Watchdog Timer Enable Mode = Watchdog Timer enabled/disabled 
 * by user software */
//_FWDT(FWDTEN_OFF);
#pragma config FWDTEN=OFF

/* Power-on Reset Timer Value = 128ms & alternate I2C position */
//_FPOR(FPWRT_PWR128 & ALTI2C1_ON);
#pragma config FPWRT=PWR128
#pragma config ALTI2C1=ON


/**************************************************************************
 * Global Definitions
 ***************************************************************************/

// USB Flags
volatile bool USBReady=false;

// define buffers for DMA
int txBufferA[BUFFERLENGTH] __attribute__((space(dma)));
int txBufferB[BUFFERLENGTH] __attribute__((space(dma)));
int rxBufferA[BUFFERLENGTH] __attribute__((space(dma)));
int rxBufferB[BUFFERLENGTH] __attribute__((space(dma)));
// DMA flags
volatile bool rxBufferIndicator = 0;

// states of switches
volatile uint8_t switchStates = 0xFF;
volatile uint8_t switchStatesChanged = 0;

/**************************************************************************
 * Main Loop
 ***************************************************************************/

int main(void)
{
    init_all();
    user_init();
    AMP_MUTE=0;
    __delay_ms(100);
    while (1)
    {
        user_mainLoop();
    }

}


/**************************************************************************
 * Interrupt Routines
 ***************************************************************************/
void __attribute__((__interrupt__, no_auto_psv)) _DMA2Interrupt(void)
{
    rxBufferIndicator = !rxBufferIndicator; // Toggle the indicator
    if (rxBufferIndicator) {
        user_processData(rxBufferA, txBufferA);
    } else {
        user_processData(rxBufferB, txBufferB);
    }
    
    
    IFS1bits.DMA2IF = 0; // Clear DMA channel 2 interrupt status flag
}

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T3Interrupt(void)
{
    static uint8_t debounceFilter1, debounceFilter2;
    static uint8_t oldSwitchStates = 0xFF;

    debounceFilter1 = debounceFilter1 << 1;
    debounceFilter1 |= SW1;
    if (debounceFilter1 == 0xFF)
    {
        switchStates |= SW1_MASK;
    }
    if (debounceFilter1 == 0x00)
    {
        switchStates &= ~SW1_MASK;
    }

    debounceFilter2 = debounceFilter2 << 1;
    debounceFilter2 |= SW2;
    if (debounceFilter2 == 0xFF)
    {
        switchStates |= SW2_MASK;
    }
    if (debounceFilter2 == 0x00)
    {
        switchStates &= ~SW2_MASK;
    }

    switchStatesChanged |= switchStates ^ oldSwitchStates;
    oldSwitchStates = switchStates;

    IFS0bits.T3IF = 0; // Clear Timer3 interrupt flag
    return;
}
