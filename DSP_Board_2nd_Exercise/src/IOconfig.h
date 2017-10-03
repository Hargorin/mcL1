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
 *  IOconfig.h
 * 
 * Description:
 *  This file contains makro definitions for the detection and enable pins.
*******************************************************************************/

#ifndef IOCONFIG_H
#define	IOCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

void io_config(void);
void io_setESPUpdate(void);

#define PWM0_RED        LATEbits.LATE4
#define PWM0_GREEN      LATEbits.LATE3
#define PWM0_BLUE       LATEbits.LATE2
    
#define PWM1_RED        LATEbits.LATE7
#define PWM1_GREEN      LATEbits.LATE6
#define PWM1_BLUE       LATEbits.LATE5
    
#define SW1             PORTBbits.RB8
#define SW2             PORTBbits.RB9
/**
 * SD card detection <p>
 * SDCARD_DET = 1 means an SD card is in the slot. 
 */    
#define SDCARD_DET      PORTGbits.RG9
#define SDCARD_CS       TRISBbits.TRISB4
    
//Audio
/**
 * Mute Amplifier <p>
 * AMP_MUTE = 1 mutes the amplifier.
 */
#define AMP_MUTE        LATBbits.LATB11
/**
 * Line In detection <p>
 * LIN_DET = 1 means a cable is plugged into the line input.
 */    
#define LIN_DET         PORTBbits.RB13
/**
 * Headphone detection <p>
 * HP_DET = 1 means a cable is plugged into the headphone input.
 */    
#define HP_DET          PORTBbits.RB10
/**
 * Line Out detection <p>
 * LOUT_DET = 1 means a cable is plugged into the line output.
 */    
#define LOUT_DET        PORTBbits.RB12
/**
 * Microphone detection <p>
 * MIC_DET = 1 means a cable is plugged into the microphone input.
 */    
#define MIC_DET         !PORTBbits.RB14 //Active Low

// SDR_Detect   
#define SDR_DET         PORTDbits.RD4

// WiFi
#define ESP_FW          PORTDbits.RD8
#define ESP_RST         LATDbits.LATD0
#define ESP_EN          LATCbits.LATC13
#define ESP_RTS         LATDbits.LATD11
    
#ifdef	__cplusplus
}
#endif

#endif	/* IOCONFIG_H */
