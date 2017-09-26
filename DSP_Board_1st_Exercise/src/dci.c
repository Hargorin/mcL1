/*******************************************************************************
 * FHNW, Labor mcL1
 * 1st_Exercise_Vorlage
 *
 * Aufgabe
 *       Folgende Dateien sind zu vervollständigen:
 *      - dci.c
 *      - dma.c
 *      - i2c.c
 *      - tlv320aic.c
 *  
*******************************************************************************/

#include <p33EP256MU806.h>
#include "dci.h"
#include "constants.h"

/**************************************************************************
 * Initiation
 ***************************************************************************/

void dci_init()
{
    // Fill this with code!
    DCICON1 = 0;
                                // Data changes on serial clock falling edge, sampled on serial clock rising edge
                                // I2S Frame Sync mode
                                // Data transmission/reception begins one serial clock cycle after the frame synchronization pulse
                                // Transmit ?0?s on a transmit underflow
                                // CSDO pin is tri-stated during disabled transmit time slots
                                // COFS pin is an input when DCI module is enabled
                                // CSCK pin is an input when DCI module is enabled
  
    DCICON2 = 0;            
                                // Data frame has one word (In I2S mode: two words)
                                // Data word size is 16 bits
    
                                // Transmit slot 0
                                // Receive slot 0

                                // Clear the TX buffer

                                // Disable DCI interrupt (we use DMA)
                                // Enable DCI
} 