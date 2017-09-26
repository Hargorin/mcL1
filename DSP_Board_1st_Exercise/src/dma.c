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
#include "dma.h"
#include "init.h"


/**************************************************************************
 * Initiation
 ***************************************************************************/

void dma_init(void)
{
    // DMA 0 - RAM to DCI  
                                // Data Transfer Size: Word  
                                // Transfer Direction: Read from DPSRAM (or RAM) address, write to peripheral address  
                                // DMA Channel Addressing Mode: Register Indirect with Post-Increment mode 
                                // DMA Channel Operating Mode: Continuous, Ping-Pong modes enabled 
                                // Block Transfer Interrupt: Block Transfer Interrupt
                                // Null Data Peripheral Write Mode: Normal operation

                                // Automatic DMA transfer initiation by DMA request
                                // Peripheral IRQ Number: $3C (DCI)

    DMA0STAH = 0x00;            // __builtin_dmaoffset(txBufferA) >> 8;
    DMA0STAL = __builtin_dmaoffset(txBufferA);
    DMA0STBH = 0x00;            //__builtin_dmaoffset(txBufferB) >> 8;
    DMA0STBL = __builtin_dmaoffset(txBufferB);
    
                                // DMA Channel 0 Peripherial Address  
                                // DMA Channel 0 Transfer Count: Transfer FRAMELENGTH elements 

    // DMA 2 - DCI to RAM  
                                // Data Transfer size: Word  
                                // Read from Peripheral address, write to DPSRAM (or RAM) address  
                                // Block Transfer Interrupt: Block Transfer Interrupt
                                // Null Data Peripheral Write Mode: Normal operation
                                // DMA Channel Addressing Mode: Register Indirect with Post-Increment mode
                                // DMA Channel Operating Mode: Continuous, Ping-Pong modes enabled
                                // Automatic DMA transfer initiation by DMA request
                                // Peripheral IRQ Number: $3C (DCI) 

    DMA2STAH = 0x00;            //__builtin_dmaoffset(rxBufferA) >> 8;
    DMA2STAL = __builtin_dmaoffset(rxBufferA);
    DMA2STBH = 0x00;            //__builtin_dmaoffset(rxBufferB) >> 8;
    DMA2STBL = __builtin_dmaoffset(rxBufferB);

                                // DMA Channel 2 Peripherial Address  
                                // DMA Channel 2 Transfer Count: Transfer FRAMELENGTH elements

                                // Clear DMA Channel 2 Interrupt Flag  
                                // Enable DMA Channel 2 Interrupt  

                                // Enable DMA channel 0  
                                // Enable DMA channel 2  
}
