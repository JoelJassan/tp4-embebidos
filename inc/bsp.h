/*---  Header Information ---------------------------------------------------------------------- */
// Autor: Jassan, Joel
// Date:
//
// Header: Hardware Abstration Layer declaration
/*---------------------------------------------------------------------------------------------- */

#ifndef BSP_H
#define BSP_H

/*---  Includes  ------------------------------------------------------------------------------- */

#include "chip.h"

#include "ciaa.h"
#include "digital.h"
#include "pantalla.h"
#include "poncho.h"

/*---  Macros  --------------------------------------------------------------------------------- */

/*---  Definitions  ---------------------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

typedef struct board_s {

	// edu-ciaa
	digital_output_t led_RGB_rojo;
	digital_output_t led_RGB_verde;
	digital_output_t led_RGB_azul;
	digital_output_t led_rojo;
	digital_output_t led_verde;
	digital_output_t led_amarillo;

	digital_input_t tec_1;
	digital_input_t tec_2;
	digital_input_t tec_3;
	digital_input_t tec_4;

	// poncho
	digital_output_t seg_A, seg_B, seg_C, seg_D, seg_E, seg_F, seg_G, seg_P;

	digital_output_t dig_1;
	digital_output_t dig_2;
	digital_output_t dig_3;
	digital_output_t dig_4;

	display_t display;

	digital_output_t buzzer;   // conectado a led_RGB_azul
	digital_input_t set_time;  // F1
	digital_input_t set_alarm; // F2
	digital_input_t decrement; // F3
	digital_input_t increment; // F4
	digital_input_t accept;
	digital_input_t cancel;

} const * board_t; // aqui saco el puntero constante, pero no se si seria correcto

/*---  Public Function Declaration  ------------------------------------------------------------ */

board_t BoardCreate(void);

/*---  End of File  ---------------------------------------------------------------------------- */
#endif
