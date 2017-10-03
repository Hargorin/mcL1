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
 *  init.c
 * 
 * Description:
 *  This file initialises summons up the initialisations of the different 
 *  interfaces and contains the initialisation of the clock and a timer.
*******************************************************************************/

#include "constants.h"
#include <p33EP256MU806.h>
#include <libpic30.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "IOconfig.h"
#include "init.h"
#include "i2c.h"
#include "dma.h"
#include "dci.h"
#include "tlv320aic.h"
#include "globals.h"
#include "pwm.h"
#include "UART.h"


/**************************************************************************
 * Global Definitions
 ***************************************************************************/
// SDR commands
// [0]: SDR addess  [1,2]: command addess [3]: value 
//uint8_t sdr_ledOn[] = {0x10, 0x00, 0x03, 0xFF};
//uint8_t sdr_ledOff[] = {0x10, 0x00, 0x03, 0x00};
//uint8_t sdr_clockOn[] = {0x10, 0x00, 0x04, 0x01}; 


/**************************************************************************
 * Private Functions
 ***************************************************************************/

void clock_init(void)
{
    int current_cpu_ipl;

    /* set fclk = 2*fcy = 2*69000000 with an 
     * input frequency of 12000000 (M/(N1*N2) */
    
    PLLFBD = 44; // M=46
    
    CLKDIVbits.PLLPOST = 0;             // N2=2
    CLKDIVbits.PLLPRE = 0;              // N1=2
//pllpost default div 4 01 -> 00
    // USB clk config
    ACLKCON3bits.ASRCSEL = 1;           // Use clk from primary OSC (12MHz))
    ACLKCON3bits.FRCSEL = 0;            // Use clk from primary OSC
    ACLKCON3bits.SELACLK = 1;           // Use clk from aux PLL (MHz)
    ACLKCON3bits.ENAPLL = 1;            // Enable aux PLL
    ACLKCON3bits.APLLPRE = 0b010;       // Pre PLL div 3 (-> 4MHz)
    ACLKDIV3bits.APLLDIV = 0b111;       // PLL div 24 (->96MHz)
    ACLKCON3bits.APLLPOST = 0b110;      // Post PLL div 2 (-> 48HMz)

    // Ref clk output
    REFOCONbits.ROON = 1;               // Enable ref clk output on pin REFCLK
    REFOCONbits.ROSEL = 1;              // System clk
    REFOCONbits.RODIV = 0b0001;         // Div 2 -> ref clk = fcy = 69MHz

    SET_AND_SAVE_CPU_IPL(current_cpu_ipl, 7);   // disable interrupts

    // Clock switch to incorporate PLL
    __builtin_write_OSCCONH(0x03);      // Initiate Clock Switch to
    // Primary Osc with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(0x01);      // Start clock switching

    RESTORE_CPU_IPL(current_cpu_ipl);   // reenable interrupts 

    while (OSCCONbits.COSC != 0b011);   // Wait for Clock switch to occur

    while (OSCCONbits.LOCK != 1)
    {
    }; // Wait for PLL to lock
}

void timer3_init(void)
{
    // Configure Timer 3 to give an interrupt every 1 ms
    T3CONbits.TON = 0;                  // Disable Timer
    T3CONbits.TCKPS = 0b01;             // Select 1:8 prescaler
    TMR3 = 0x0000;                      // Clear Timer Register
    PR3 = FCY / 8000 - 1;               // Load Period Value ((1e-3)*FCY/8 - 1)
    IFS0bits.T3IF = 0;                  // Clear Interrupt Flag
    IEC0bits.T3IE = 1;                  // Enable Interrupt
    T3CONbits.TON = 1;                  // Start Timer
}

/**************************************************************************
 * Public Functions
 ***************************************************************************/

void init_all(void)
{
    __delay_ms(5);                    /* make sure voltage is stable and 
                                         * codec is alive. */

    io_config(); 
    i2c_init(FCY_STARTUP);
  
    codec_init();                       // init codec to forward external clock
    __delay_ms(5);

    clock_init();                       // Switch to external clock
    i2c_init(FCY);                      // Init I2C for high system frequency
    
    dma_init();
    dci_init();
    timer3_init();
    pwm_init();
    uart_init();

    printf("Init & Clock switch done!\n");
    
    
    AMP_MUTE = 1;
}


