/* Copyright jun/2023, Joel Jassan <joeljassan@hotmail.com>
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

/** \brief Simple brief of a ".h" template*/

#ifndef PANTALLA_H
#define PANTALLA_H

/*---  Includes  --------------------------------------------------------------------------------------------------- */

#include <stdint.h>

/* ---  Macros definitions  ---------------------------------------------------------------------------------------- */

#define SEGMENT_A (1 << 0)
#define SEGMENT_B (1 << 1)
#define SEGMENT_C (1 << 2)
#define SEGMENT_D (1 << 3)
#define SEGMENT_E (1 << 4)
#define SEGMENT_F (1 << 5)
#define SEGMENT_G (1 << 6)
#define SEGMENT_P (1 << 7)

/*---  Public Data Declaration  ------------------------------------------------------------------------------------ */

//! Puntero al descriptor para el manejo de la pantalla de 7 segmentos
typedef struct display_s * display_t;

//! Funcion de callback para apagar los segmentos y digitos de la pantalla
typedef void (*display_screen_off_t)(void);

//! Funcion de callback para prender los segmentos de la pantalla
typedef void (*display_screen_on_t)(uint8_t segments);

//! Funcion de callback para prender un digito de la pantalla
typedef void (*display_digit_on_t)(uint8_t digit);

//! Estructura con las funciones de bajo nivel para manejo de la pantalla
typedef struct display_driver_s {
	display_screen_off_t ScreenTurnOff; //! Funcion para apagar sementos y digitos
	display_screen_on_t SegmentsTurnOn; //! Funcion para encender segmentos
	display_digit_on_t DigitTurnOn;		//! Funcion para prender un digito
} const * const display_driver_t;		//! Puntero al controlador de la pantalla

/*---  Public Function Declaration -------------------------------------------------------------------------------- */

/**
 * @brief Metodo para crear una pantalla 7 segmentos multiplexada
 *
 * @param digits Cantidad de digitos que tiene la pantalla multiplexada
 * @param driver Puntero a las funciones de bajo nivel
 * @return display_t Puntero al descriptor de la pantalla creada
 */
display_t DisplayCreate(uint8_t digits, display_driver_t driver);

/**
 * @brief Medotod para escribir un numero BCD en la pantalla de 7 segmentos
 *
 * @param display Puntero al descriptor de la pantalla en la que se escribe
 * @param number Puntero al primer elemento de numero BCD a escribir
 * @param size Cantidad de elementos en el vector que contienen al numero BCD
 */
void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size);

/**
 * @brief Funcion para refrescar la pantalla. Pasa al display siguiente.
 *
 * @param display Puntero al descriptor de la pantalla que se debe refrescar
 */
void DisplayRefresh(display_t display);

/**
 * @brief Funcion para parpadear ciertos digitos de la pantalla
 *
 * @param display Puntero al descriptor de la pantalla
 * @param from Posicion del primer digito
 * @param to Posicion del ultimo digito
 * @param frequency Factor de division del refresco
 */
void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t frequency);

/**
 * @brief Funcion para conmutar el estado del punto del display
 *
 * @param display Puntero al descriptor de la pantalla
 * @param position Posicion del punto que se conmuta de estado
 */
void DisplayToggleDot(display_t display, uint8_t position);

/**
 * @brief Funcion para conmutar el estado de varios puntos del display
 *
 * @param display Puntero al descriptor de la pantalla
 * @param toggle_from Posicion del primer digito
 * @param toggle_to Posicion del ultimo digito
 */
void DisplayToggleDots(display_t display, uint8_t toggle_from, uint8_t toggle_to);

/**
 * @brief Funcion para setear el estado del punto del display
 *
 * @param display Puntero al descriptor de la pantalla
 * @param position Posicion del punto que se conmuta de estado
 */
void DisplaySetDot(display_t display, uint8_t position);

/*---  End of File ------------------------------------------------------------------------------------------------ */
#endif