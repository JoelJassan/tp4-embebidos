/*---  Header Information ---------------------------------------------------------------------- */
// Autor: Jassan, Joel
// Date:
//
// Header: Abstraction functions layer declaration
/*---------------------------------------------------------------------------------------------- */

#ifndef DIGITAL_H
#define DIGITAL_H

/*---  Includes  ------------------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>

/*---  Macros  --------------------------------------------------------------------------------- */

typedef struct digital_output_s * digital_output_t;
typedef struct digital_input_s * digital_input_t;

/*---  Definitions  ---------------------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

// --- Soporte de Salidas

/**
 * @brief Metodo para crear un descriptor de salida
 *
 * @param port          Puerto GPIO que contiene la entrada
 * @param pin           Terminal del GPIO asignado a la entrada
 * @param inverted      Flag que indica si trabaja con logica invertida
 * @return digital_output_t Puntero al descriptor de entrada
 */
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin, bool inverted);

/**
 * @brief Metodo para activar el estado de un terminal de un puerto GPIO
 *
 * @param output Puntero al descriptor de salida
 */
void DigitalOutputActivate(digital_output_t output);

/**
 * @brief Metodo para desactivar el estado de un terminal de un puerto GPIO
 *
 * @param output Puntero al descriptor de salida
 */
void DigitalOutputDeactivate(digital_output_t output);

/**
 * @brief Metodo para conmutar el estado de un terminal de un puerto GPIO
 *
 * @param output Puntero al descriptor de salida
 */
void DigitalOutputToggle(digital_output_t output);

// --- Soporte de Entradas

/**
 * @brief Metodo para crear un descriptor de entrada
 *
 * @param port          Puerto GPIO que contiene la entrada
 * @param pin           Terminal del GPIO asignado a la entrada
 * @param inverted      Flag que indica si trabaja con logica invertida
 * @return digital_input_t  Puntero al descriptor de entrada
 */
digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted);

/**
 * @brief Metodo para leer una entrada
 *
 * @param input     Puntero al descriptor de la entrada
 * @return true     Entrada activa
 * @return false    Entrada inactiva
 */
bool DigitalInputRead(digital_input_t input);

/**
 * @brief Metodo para determinar si hubo cambio en la entrada
 *
 * @param input     Puntero al descriptor de la entrada
 * @return true     La entrada tuvo cambios
 * @return false    La entrada no tuvo cambios
 */
bool DigitalInputHasChanged(digital_input_t input);

/**
 * @brief Metodo para determinar si la entrada fue activada
 *
 * @param input     Puntero al descriptor de la entrada
 * @return true     La entrada fue activada
 * @return false    La entrada no fue activada
 */
bool DigitalInputHasActivated(digital_input_t input);

/**
 * @brief Metodo para determinar si la entrada fue desactivada
 *
 * @param input     Puntero al descriptor de la entrada
 * @return true     La entrada fue desactivada
 * @return false    La entrada no fue desactivada
 */
bool DigitalInputHasDeactivated(digital_input_t input);

/*---  End of File  ---------------------------------------------------------------------------- */
#endif
