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
 *  userCode.c
 *
 * Description:
 *  This file contains the user specific instructions that will be called at
 *  the correct location in the main loop.
 *******************************************************************************/

#include <dsp.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "userConfig.h"
#include "../globals.h"
#include "../tlv320aic.h"
#include "../IOconfig.h"
#include "../pwm.h"
#include "userCode.h"
#include "h/SineTable.h"
#include "h/FIR.h"


/**************************************************************************
 * User Global Definitions
 ***************************************************************************/
#define F_SIN 1000

volatile int8_t mode = 0;
FIRStruct FIRfilterL, FIRfilterR;


bool updateMode(void);
fractional dds(unsigned int);

/**************************************************************************
 * User Public Functions
 ***************************************************************************/

/**
 * This user function is called once in the begining. It can be used to
 * initialise user buffers ect.
 */
void user_init()
{
    codec_setInput(LINE);
    FIRStructInit(&FIRfilterL,NTAPS,coefficients,COEFFS_IN_DATA,delayBufferL);
    FIRStructInit(&FIRfilterR,NTAPS,coefficients,COEFFS_IN_DATA,delayBufferR);
}

/**
 * This user function is called once in the main loop.
 */
void user_mainLoop()
{
    if (updateMode()) {
        led_setColour(LED2, mode & 0x01 ? 255 : 0, 0, 0);
        led_setColour(LED1, (mode >> 1) & 0x01 ? 255 : 0, 0, 0);
    }

}

/**
 * This user function is called when new data is ready from the DMA.
 * @param sourceBuffer  is the buffer that contains the available input data
 * @param targetBuffer  is the buffer that the processed data has to be written into
 */
void user_processData(fractional *sourceBuffer, fractional *targetBuffer)
{
    uint16_t i, index1, index2;

    static fractional rxLeft[BUFFERLENGTH_DIV_2], rxRight[BUFFERLENGTH_DIV_2];
    static fractional txLeft[BUFFERLENGTH_DIV_2], txRight[BUFFERLENGTH_DIV_2];

    // copy sourceBuffer to leftSignalBuffer and rightSignalBuffer
    for (index1 = 0, index2 = 0; index1 < BUFFERLENGTH_DIV_2; index1++) {
        rxLeft[index1] = sourceBuffer[index2++];
        rxRight[index1] = sourceBuffer[index2++];
    }

    switch (mode) {
        case 0:
            //talk through: just copy input (rx) into output (tx) 
            for (i = 0; i < BUFFERLENGTH_DIV_2; i++) {
                txLeft[i] = rxLeft[i];
            }
            for (i = 0; i < BUFFERLENGTH_DIV_2; i++) {
                txRight[i] = rxRight[i];
            }
            break;
            
        case 1:
            //Sine Wave Oscillator
            for (i = 0; i < BUFFERLENGTH_DIV_2; i++) {
                static uint16_t phase;
                
                phase += (uint16_t)(65536 * F_SIN / CODEC_SAMPLE_RATE);
                txLeft[i] = SINE_TABLE[(phase >> 4) & 0xfff];
                txRight[i] = SINE_TABLE[(phase >> 4) & 0xfff];
            }
            break;   

        case 2:
            //FIR Filter    
            FIR(BUFFERLENGTH_DIV_2, &txLeft[0], &rxLeft[0], &FIRfilterL);
            //FIR(BUFFERLENGTH_DIV_2, &txRight[0], &rxRight[0], &FIRfilterR); 
            for (i = 0; i < BUFFERLENGTH_DIV_2; i++) {
                txRight[i] = rxLeft[i];
            }
            break;
    }

    //copy left and right txBuffer into targetBuffer
    for (index1 = 0, index2 = 0; index1 < BUFFERLENGTH_DIV_2; index1++) {
        targetBuffer[index2++] = txLeft[index1];
        targetBuffer[index2++] = txRight[index1]; //txRight[index1];
    }
}

/**************************************************************************
 * User Private Functions
 ***************************************************************************/

/**
 * This function changes between four different modes whenever a switch is
 * pushed. The switches are used to count the mode up or down.
 * @return a bool that is true whenever the mode has changed (a switch has been
 * pushed)
 */
bool updateMode(void)
{
    bool modeChanged = false;
    if (switchStatesChanged) // Any changes in the state of the switches?
    {
        if (switchStatesChanged & SW1_MASK) // Has state of switch 1 changed?
        {
            switchStatesChanged &= ~SW1_MASK;
            if ((switchStates & SW1_MASK) == 0) // Is new state = 0?
            {
                mode++;
                if (mode > 3) {
                    mode = 0;
                }
            }
        }
        if (switchStatesChanged & SW2_MASK) // Has state of switch 2 changed?
        {
            switchStatesChanged &= ~SW2_MASK;
            if ((switchStates & SW2_MASK) == 0) // Is new state = 0?
            {
                mode--;
                if (mode < 0) {
                    mode = 3;
                }
            }
        }
        modeChanged = true;
    }
    return modeChanged;
}

fractional dds(unsigned int deltaPsiRegister){
    static unsigned int psiRegister;
    
    return psiRegister; //just to make the compiler happy!
}