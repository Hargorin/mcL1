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

#include "constants.h"
#include <libpic30.h>
#include <stdint.h>
#include <stdbool.h>
#include <p33EP256MU806.h>
#include "tlv320aic.h"
#include "i2c.h"

/**************************************************************************
 * Global Definitions
 ***************************************************************************/

const uint16_t TLV320_init_data[10] = {
    0x01B       // Reg 00: Left Line In (6dB, mute OFF)
    0x01B       // Reg 01: Right Line In (6dB, mute OFF)
    0x0F9       // Reg 02: Left Headphone out (-12dB)
    0x0F9       // Reg 03: Right Headphone out (-12dB)
    0x012       // Reg 04: Analog Audio Path Control (DAC sel, Mute Mic)
    0x000       // Reg 05: Digital Audio Path Control
                // Reg 06: Power Down Control (All ON)
                // Reg 07: Digital Audio Interface Format (I2S, 16-bit, master)
    #if CODEC_SAMPLE_RATE == 96000
                // Reg 08: Sampling Control (Clock Out divided by 1, USB, 250x, 96k ADC/DAC)
    #endif
    #if CODEC_SAMPLE_RATE == 44100
                // Reg 08: Sampling Control (Clock Out divided by 1, USB, 250x, 44.1k ADC/DAC)
    #endif
    #if CODEC_SAMPLE_RATE == 48000
                // Reg 08: Sampling Control (Clock Out divided by 2, USB, 250x, 48k ADC/DAC)
    #endif
    #if CODEC_SAMPLE_RATE == 32000
                // Reg 08: Sampling Control (Clock Out divided by 1, USB, 250x, 32k ADC/DAC)
    #endif
    #if CODEC_SAMPLE_RATE == 8000
                // Reg 08: Sampling Control (Clock Out divided by 1, USB, 250x, 8k ADC/DAC)
    #endif
                // Reg 09: Active Control
};
    unsigned long samplerate=CODEC_SAMPLE_RATE;

/**************************************************************************
 * Private Functions
 ***************************************************************************/
/**
 * Writes the configuration in <em>data</em> into the <em>register</em>.
 * @param reg   is a register address, the makros defined in <em>tlv320aic.h</em> 
 *              should be used.
 * @param data  is a one byte value depending on the expected inputs of the register.
 */
void codec_write(uint8_t reg, uint16_t data)
{
    /*
     * Fill this with code! 
     */
}

/**************************************************************************
 * Initiation
 ***************************************************************************/

void codec_init()
{
    /*
     * Fill this with code! 
     */
}

/**************************************************************************
 * Public Functions
 ***************************************************************************/

void codec_mute(bool on)
{
    if (on)
    {
        // Reg 00: Left Line In (-34.5dB, mute ON)
        codec_write(TLV320_LEFT_IN_VOL_REG, 0x080);
        // Reg 01: Right Line In (-34.5dB, mute ON)
        codec_write(TLV320_RIGHT_IN_VOL_REG, 0x080);
    }
    else
    {
        // Reg 00: Left Line In (6dB, mute OFF)
        codec_write(TLV320_LEFT_IN_VOL_REG, 0x01B);
        // Reg 01: Right Line In (6dB, mute OFF)
        codec_write(TLV320_RIGHT_IN_VOL_REG, 0x01B);
    }

}

void codec_setInput(input_t in)
{
    switch (in)
    {
    case LINE:
        // Reg 04: Analog Audio Path Control (DAC sel, Mute Mic)
        codec_write(TLV320_ANALOG_AUDIO_PATH_REG, 0x012);
        break;

    case MIC:
    default:
        // Reg 04: Analog Audio Path Control (DAC sel, Mic, 20dB boost)
        codec_write(TLV320_ANALOG_AUDIO_PATH_REG, 0x015);
        break;
    }
}

void codec_setMicboost(bool boost)
{
    unsigned int value;
    value = boost ? 0x015 : 0x014;
    // Reg 04: Analog Audio Path Control (DAC sel, Mic, 20dB boost)
    codec_write(TLV320_ANALOG_AUDIO_PATH_REG, value);
}

void codec_setLineInVol(uint8_t vol)
{
    if (vol > 0x01F)
        vol = 0x01F;
    codec_write(TLV320_LEFT_IN_VOL_REG, 0x100 | (vol & 0x01F));
    codec_write(TLV320_RIGHT_IN_VOL_REG, 0x100 | (vol & 0x01F));
}

void codec_setHeadphoneVol(uint8_t vol)
{
    vol += 0x030;
    if (vol > 0x07F)
        vol = 0x07F;
    codec_write(TLV320_LEFT_HP_VOL_REG, 0x100 | vol);
    codec_write(TLV320_RIGHT_HP_VOL_REG, 0x100 | vol);
}

void codec_reset()
{
    codec_write(TLV320_RESET_REG, 0);
}




