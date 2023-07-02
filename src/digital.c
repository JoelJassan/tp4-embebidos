//---  Code Information ------------------------------------------------------------------------ */
// Autor: Jassan, Joel
// Date: may/2023
//
// Project: Abstraction functions layer. Include inputs and outputs in edu-ciaa-nxp.
/*---------------------------------------------------------------------------------------------- */

/*---  Includes  ------------------------------------------------------------------------------- */
#include "digital.h"
#include "chip.h"

/*---  Macros and Definitions  ----------------------------------------------------------------- */

#ifndef OUTPUT_INSTANCES
#define OUTPUT_INSTANCES 14
// 12
#endif

#ifndef INPUT_INSTANCES
#define INPUT_INSTANCES 6
// 6
#endif

/*---  Private Data Declaration  --------------------------------------------------------------- */

//! Estructura que almacena el descriptor de una salida
struct digital_output_s {
	uint8_t port;		//!< Puerto GPIO de la salida
	uint8_t pin;		//!< Terminal del puerto GPIO de la salida
	bool inverted : 1;	//!< Indicador si opera con logica invertida
	bool allocated : 1; //!< Flag indicador si se esta usando el descriptor
};

//! Estructura que almacena el descriptor de una entrada
struct digital_input_s {
	uint8_t port;		 //!< Puerto GPIO de la entrada
	uint8_t pin;		 //!< Terminal del puerto GPIO de la entrada
	bool inverted : 1;	 //!< Indicador si opera con logica invertida
	bool allocated : 1;	 //!< Flag indicador si se esta usando el descriptor
	bool last_state : 1; //!< Flag que almacena el ultimo estado de la entrada
};

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

digital_output_t DigitalOutputAllocate(void);

digital_input_t DigitalInputAllocate(void);

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------ */

/*---  Private Function Implementation  -------------------------------------------------------- */

/**
 * @brief Funcion para alocar una instanciacion del descriptor de salida
 *
 * @return digital_output_t Puntero al descriptor de salida
 */
digital_output_t DigitalOutputAllocate(void) {
	digital_output_t output = NULL;

	static struct digital_output_s instances[OUTPUT_INSTANCES] = {0};

	for (int index = 0; index < OUTPUT_INSTANCES; index++) {
		if (!instances[index].allocated) {
			instances[index].allocated = true;
			output = &instances[index];
			break;
		}
	}

	return output;
}

/**
 * @brief Funcion para alocar una instanciacion del descriptor de entrada
 *
 * @return digital_input_t Puntero al descriptor de entrada
 */
digital_input_t DigitalInputAllocate(void) {
	digital_input_t input = NULL;

	static struct digital_input_s instances[INPUT_INSTANCES] = {0};

	for (int index = 0; index < INPUT_INSTANCES; index++) {
		if (!instances[index].allocated) {
			instances[index].allocated = true;
			input = &instances[index];
			break;
		}
	}

	return input;
}

/*---  Public Function Implementation  --------------------------------------------------------- */

// Soporte de Salidas
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin, bool inverted) {
	digital_output_t output = DigitalOutputAllocate();

	if (output) {
		output->port = port;
		output->pin = pin;
		output->inverted = inverted;
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
		Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port, output->pin, true);
	}

	return output;
}

void DigitalOutputActivate(digital_output_t output) {
	// Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, output->inverted ^ true);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, true);
}

void DigitalOutputDeactivate(digital_output_t output) {
	// Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, output->inverted ^ false);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
}

void DigitalOutputToggle(digital_output_t output) {
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);
}

// Soporte de Entradas
digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted) {
	digital_input_t input = DigitalInputAllocate();

	if (input) {
		input->port = port;
		input->pin = pin;
		input->inverted = inverted;
		Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, input->port, input->pin, false);
	}

	return input;
}

bool DigitalInputRead(digital_input_t input) {
	return input->inverted ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port, input->pin);
}

bool DigitalInputHasChanged(digital_input_t input) {
	bool state = DigitalInputRead(input);
	bool result = state != input->last_state;
	input->last_state = state;
	return result;
}

bool DigitalInputHasActivated(digital_input_t input) {
	bool state = DigitalInputRead(input);
	bool result = state && !input->last_state;
	input->last_state = state;
	return result;
}

bool DigitalInputHasDeactivated(digital_input_t input) {
	bool state = DigitalInputRead(input);
	bool result = !state && input->last_state;
	input->last_state = state;
	return result;
}