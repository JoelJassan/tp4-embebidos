/*
 * 
 * Copyright jun/2023, Joel Jassan <joeljassan@hotmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/** \brief Macros of edu-ciaa*/



#ifndef CIAA_H
#define CIAA_H

/*---  Includes  ------------------------------------------------------------------------------- */

/* ---  Macros definitions  -------------------------------------------------------------------- */
#define LED_R_PORT 2
#define LED_R_PIN 0
#define LED_R_FUNC SCU_MODE_FUNC4
#define LED_R_GPIO 5
#define LED_R_BIT 0

#define LED_G_PORT 2
#define LED_G_PIN 1
#define LED_G_FUNC SCU_MODE_FUNC4
#define LED_G_GPIO 5
#define LED_G_BIT 1

#define LED_B_PORT 2
#define LED_B_PIN 2
#define LED_B_FUNC SCU_MODE_FUNC4
#define LED_B_GPIO 5
#define LED_B_BIT 2

// Esta led_1_gpio y led_1_bit invertido con led_2_gpio y led_2_bit respectivamente
#define LED_1_PORT 2
#define LED_1_PIN 10
#define LED_1_FUNC SCU_MODE_FUNC0
#define LED_1_GPIO 1
#define LED_1_BIT 11

#define LED_2_PORT 2
#define LED_2_PIN 11
#define LED_2_FUNC SCU_MODE_FUNC0
#define LED_2_GPIO 0
#define LED_2_BIT 14

#define LED_3_PORT 2
#define LED_3_PIN 12
#define LED_3_FUNC SCU_MODE_FUNC0
#define LED_3_GPIO 1
#define LED_3_BIT 12

#define TEC_1_PORT 1
#define TEC_1_PIN 0
#define TEC_1_FUNC SCU_MODE_FUNC0
#define TEC_1_GPIO 0
#define TEC_1_BIT 4

#define TEC_2_PORT 1
#define TEC_2_PIN 1
#define TEC_2_FUNC SCU_MODE_FUNC0
#define TEC_2_GPIO 0
#define TEC_2_BIT 8

#define TEC_3_PORT 1
#define TEC_3_PIN 2
#define TEC_3_FUNC SCU_MODE_FUNC0
#define TEC_3_GPIO 0
#define TEC_3_BIT 9

#define TEC_4_PORT 1
#define TEC_4_PIN 6
#define TEC_4_FUNC SCU_MODE_FUNC0
#define TEC_4_GPIO 1
#define TEC_4_BIT 9
/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  End of File  ---------------------------------------------------------------------------- */
#endif