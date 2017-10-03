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
 *  IOconfig.c
 * 
 * Description:
 *  This file maps the interfaces to the desired pins.
*******************************************************************************/

#include <p33EP256MU806.h>
#include <libpic30.h>

#include "constants.h"
#include "IOconfig.h"

/**************************************************************************
 * Initiation
 ***************************************************************************/

void io_config (void)
{
  // Unlock Registers
  __builtin_write_OSCCONL (OSCCON & ~(1 << 6));
 
  // Convert all I/O pins to digital.
  ANSELB = 0x0000;
  ANSELC = 0x0000;
  ANSELD = 0x0000;
  ANSELE = 0x0000;
  ANSELG = 0x0000;

  // QEI
  RPINR14bits.QEA1R = 35;       // QEI1 Phase A tied to RPI35 (Pin 13)
  RPINR14bits.QEB1R = 34;       // QEI1 Phase B tied to RPI34 (Pin 14)

  RPINR16bits.QEA2R = 33;       // QEI2 Phase A tied to RPI33 (Pin 15)
  RPINR16bits.QEB2R = 32;       // QEI2 Phase B tied to RPI32 (Pin 16)
 
  // GPIO (Outputs only)
  TRISBbits.TRISB11 = 0;        // AMP_MUTE on RB11 (Pin 24)
  TRISDbits.TRISD0 = 0;         // ESP_RST on RD0 (Pin 46)
  TRISCbits.TRISC13 = 0;        // ESP_EN on RC13 (Pin 47)

  // Pull up
  CNPUDbits.CNPUD4=1;           // SDR_DETECT pull up RD4 (Pin 52))

  // SPI
  // SD Card
  // Inputs
  RPINR20bits.SDI1R = 81;       // SDI1 tied to RPI81 (Pin 61)
  // Outputs
  RPOR4bits.RP80R = 0b000110;   // SCLK1 tied to RP80 (Pin 60)
  RPOR7bits.RP97R = 0b000101;   // SDO1 tied to RP97 (Pin 59)
  TRISBbits.TRISB4 = 0;         // SD_SS is output (Pin 12)
  TRISBbits.TRISB5 = 0;         // EXT_SS is output (Pin 11)
 
  // UART
  // WiFi UART1
  if(ESP_FW==1) 
  {
    // Inputs
     RPINR18bits.U1RXR = 62;       // U1RX tied to RPI62 (Pin 48)
  
    // Outputs
    RPOR0bits.RP65R = 0b000001;   // U1TX tied to RPI65 (Pin 49)
  
  }

    TRISDbits.TRISD11 = 0;           //ESP RTS pin RPI75 (Pin 45)

    // Extern UART2
    // Input
    RPINR19bits.U2RXR = 96;       // U2RX tied to RP96 (Pin 58)
    // Output
    RPOR3bits.RP71R = 0b000011;   // U2TX tied to RP71 (Pin 55) 
  
  // DCI / I2S
  // Inputs
#if USE_SDR ==1
  RPINR24bits.CSDIR = 67;       // DCI Data Input (CSDI) tied to RP67 (Pin 51) --> SDR!
#else
  RPINR24bits.CSDIR = 47;       // DCI Data Input (CSDI) tied to RPI47 (Pin 30)
#endif
  RPINR24bits.CSCKR = 99;       // DCI Clock (CSCKIN) tied to RP99 (Pin 33)
  RPINR25bits.COFSR = 100;      // DCI FSYNC (COFSIN) tied to RP100 (Pin 31)
  // Outputs 
  RPOR9bits.RP101R = 0b001011;  // DCI Data Output (CSDO) tied to RP101 (Pin 32)
 
  // Lock Registers
  __builtin_write_OSCCONL (OSCCON | (1 << 6));
}

void io_setESPUpdate()
{
    TRISDbits.TRISD8 = 1; // ESP_FW (Pin 42)
    TRISDbits.TRISD0 = 0; // ESP_RST (Pin 46)
    TRISCbits.TRISC13 = 0; // ESP_EN (Pin 47)
    
    // Wifi UART1
      TRISDbits.TRISD11 = 0;           //ESP RTS pin
}