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

#ifndef PWM_H_H
#define	PWM_H_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PWM_PRESCALER 4 // 64
#define PWM_PERIOD 255

#define LED1BLUE SDC2   // PWM2L
#define LED1GREEN PDC2  // PWM2H
#define LED1RED SDC3    // PWM3L
#define LED2BLUE PDC3   // PWM3H
#define LED2GREEN SDC4  // PWM4L
#define LED2RED PDC4    // PWM4H


typedef enum {
LED1, LED2
} led_t;/**< @typedef that represents the two RGB LEDs.
         * @enum LED1 the left RGB LED
         * @enum LED2 the right RGB LED
 */

/**
 * Initialises the PWM interface.
 */
void pwm_init();
/**
 * Sets the colour of the specified LED. The colour is given as an RGB value.
 * @param led   specifies the LED whose colour should be changed
 * @param red   gives the amount of red in the desired colour
 * @param green gives the amount of green in the desired colour
 * @param blue  gives the amount of blue in the desired colour
 */
void led_setColour(led_t led, uint8_t red, uint8_t green, uint8_t blue);
/**
 * Turns the specified LED on or off. The colour is stored. If no colour was 
 * set the LED will be white (255,255,255).
 * @param led   specifies the LED that is turned on/off
 * @param on    specifies whether the LED should be turned on or off
 */
void led_on(led_t led, bool on);
/**
 * Reduces the brightness of both LEDs.
 * @param setBright must be a value between 0 and 100.
 */
void led_setBrightness(uint8_t setBright);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H_H */
