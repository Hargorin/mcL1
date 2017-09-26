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
 *  pwm.c
 * 
 * Description:
 *  This file initialises the PWM interface to control two RGB LEDs and 
 *  provides the functionality to change their colour.
*******************************************************************************/

#include <p33EP256MU806.h>
#include <stdbool.h>
#include "constants.h"
#include <stdint.h>
#include "pwm.h"

/**************************************************************************
 * Global Definitions
 ***************************************************************************/

static uint8_t red1,green1,blue1,red2,green2,blue2;

/**************************************************************************
 * Initiation
 ***************************************************************************/

void pwm_init()
{
    PTCONbits.PTEN = 0; // Disabling PWM for configuration
    PTCON2bits.PCLKDIV = 6; // PWM Input Clock Prescaler: 64
    SEVTCMP = 0; // Special Event Compare Count Value bits
    PTPER = PWM_PERIOD; // Sets period 
    /*  Independent Time Base Mode bit (0 = PTPER register 
     * provides timing for this PWM generator) */
    PWMCON2bits.ITB = PWMCON3bits.ITB = PWMCON4bits.ITB = 0;

    /*  Master Duty Cycle Register Select bit (0: PDCx and SDCx registers 
     * provide duty cycle information for this PWM generator) */
    PWMCON2bits.MDCS = PWMCON3bits.MDCS = PWMCON4bits.MDCS = 0;

    //  Dead Time Control bits (10 = Dead time function is disabled)
    PWMCON2bits.DTC = PWMCON3bits.DTC = PWMCON4bits.DTC = 0b10;

    // Immediate Update Enable bit (0 = Off)
    PWMCON2bits.IUE = PWMCON3bits.IUE = PWMCON4bits.IUE = 0;

    // (S)PHASEx: PWM Primary Phase Shift register - All off
    PHASE2 = PHASE3 = PHASE4 = 0;
    SPHASE2 = SPHASE3 = SPHASE4 = 0;

    // IOCONx: PWM I/O Control register
    IOCON2 = IOCON3 = IOCON4 = 0;

    /* PENH: PWMxH / PENL: PWMxL
     * Output Pin Ownership bit (1 = PWM module controls pin)*/
    IOCON2bits.PENH = IOCON3bits.PENH = IOCON4bits.PENH = 1;
    IOCON2bits.PENL = IOCON3bits.PENL = IOCON4bits.PENL = 1;
    IOCON2bits.POLH = IOCON3bits.POLH = IOCON4bits.POLH = 0;
    IOCON2bits.POLL = IOCON3bits.POLL = IOCON4bits.POLL = 0;

    // True Independent Output mode
    IOCON2bits.PMOD = IOCON3bits.PMOD = IOCON4bits.PMOD = 0b11;

    // Enable PWM
    PTCONbits.PTEN = 1;
    red1 = green1 = blue1 = red2 = green2 = blue2 = 255;
}

/**************************************************************************
 * Private Functions
 ***************************************************************************/

/**
 * Changes the counter value of a Period.\n Standard is 255.
 * @param pwmPeriod can be any 16 bit value
 */
void pwm_setPeriod(uint16_t pwmPeriod)
{
    PTCONbits.PTEN = 0;
    PTPER = pwmPeriod;
    PTCONbits.PTEN = 1;
}

/**************************************************************************
 * Public Functions
 ***************************************************************************/

void led_setColour(led_t led, uint8_t red, uint8_t green, uint8_t blue)
{

    switch (led)
    {
    case LED1:
        LED1RED = red;
        LED1GREEN = green;
        LED1BLUE = blue;
        red1 = red;
        green1 = green;
        blue1 = blue;
        break;
    case LED2:
        LED2RED = red;
        LED2GREEN = green;
        LED2BLUE = blue;
        red2 = red;
        green2 = green;
        blue2 = blue;
        break;
    }
}

void led_on(led_t led, bool on)
{

    switch (led)
    {
    case LED1:
        if (on)
        {
            LED1RED = red1;
            LED1GREEN = green1;
            LED1BLUE = blue1;
        }
        else
        {
            LED1RED = 0;
            LED1GREEN = 0;
            LED1BLUE = 0;
        }
        break;
    case LED2:
        if (on)
        {
            LED2RED = red2;
            LED2GREEN = green2;
            LED2BLUE = blue2;
        }
        else
        {
            LED2RED = 0;
            LED2GREEN = 0;
            LED2BLUE = 0;
        }
        break;
    }

}

void led_setBrightness(uint8_t setBright)
{
    if (setBright <= 100 && setBright > 0)
    {
        unsigned int newPeriod = 32755 - (setBright * 325);
        pwm_setPeriod(newPeriod);
    }
}



