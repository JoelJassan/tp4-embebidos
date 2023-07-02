/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * Modificacion Joel Jassan
 *
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

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions * =============================================================== */

#include "bsp.h"
#include "reloj.h"
#include <stdbool.h>
#include <stddef.h>

/* === Macros definitions * ==================================================================== */

#define REFRESH_TIME 1000			   //! Cuenta del Systick
#define SNOOZE_TIME 5				   //! Tiempo que se posterga la alarma
#define TIME_TO_SET 3000			   //! Tiempo que se pulsa el boton
#define TIME_TO_CLEAN TIME_TO_SET * 10 //! Tiempo para reiniciar el estado

/* === Private data type declarations ========================================================== */

typedef enum {
	HORA_SIN_CONFIGURAR,
	MOSTRANDO_HORA,
	AJUSTANDO_MINUTOS_ACTUAL,
	AJUSTANDO_HORAS_ACTUAL,
	AJUSTANDO_MINUTOS_ALARMA,
	AJUSTANDO_HORAS_ALARMA,
} modo_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

void SisTick_Init(uint32_t time);

/* === Public variable definitions ============================================================= */

static board_t board;
static clock_t reloj;
static modo_t modo;

/* === Private variable definitions ============================================================ */

static const uint8_t LIMITE_MINUTOS[] = {5, 9};
static const uint8_t LIMITE_HORAS[] = {2, 3};

// static bool set_config = 0;
static uint16_t contador_set_config = TIME_TO_SET;
static uint16_t tiempo_muerto = TIME_TO_CLEAN;

/* === Private function implementation ========================================================= */

/**
 * @brief Funcion para contar el tiempo de boton presionado
 *
 * @param button_state estado del boton que se lee
 * @param max_count tiempo limite de cuenta
 */
void CounterSetRefresh(bool button_state, uint16_t max_count) {
	if (button_state == 1) {
		if (contador_set_config > 0)
			contador_set_config -= 1;
	} else {
		contador_set_config = max_count;
		if (tiempo_muerto > 0)
			tiempo_muerto -= 1;
	}
}

/* === Public function implementation ========================================================== */

void SwitchMode(modo_t valor) {
	modo = valor;
	switch (modo) {
	case HORA_SIN_CONFIGURAR:
		DisplayFlashDigits(board->display, 0, 3, 200);
		break;
	case MOSTRANDO_HORA:
		DisplayFlashDigits(board->display, 0, 0, 0);
		break;
	case AJUSTANDO_MINUTOS_ACTUAL:
		DisplayFlashDigits(board->display, 2, 3, 100);
		break;
	case AJUSTANDO_HORAS_ACTUAL:
		DisplayFlashDigits(board->display, 0, 1, 100);
		break;
	case AJUSTANDO_MINUTOS_ALARMA:
		DisplayFlashDigits(board->display, 2, 3, 50);
		break;
	case AJUSTANDO_HORAS_ALARMA:
		DisplayFlashDigits(board->display, 0, 1, 50);
		break;
	default:
		break;
	}
}

void IncrementBCD(uint8_t numero[2], const uint8_t limite[2]) {
	numero[1]++;

	if (numero[1] > limite[1] && numero[0] >= limite[0]) {
		numero[1] = 0;
		numero[0] = 0;
	}

	if (numero[1] > 9) {
		numero[1] = 0;
		numero[0]++;
	}
}

void DecrementBCD(uint8_t numero[2], const uint8_t limite[2]) {
	numero[1]--;

	if (numero[1] > 9) {
		numero[1] = 9;
		if (numero[0] > 0)
			numero[0]--;
		else {
			numero[0] = limite[0];
			numero[1] = limite[1];
		}
	}
}

void TriggerAbstraction(clock_t clock) {
	if (IsAlarmRinging(reloj))
		DigitalOutputActivate(board->led_RGB_azul);
	else
		DigitalOutputDeactivate(board->led_RGB_azul);
}

int main(void) {
	uint8_t entrada[ALARM_SIZE];

	reloj = ClockCreate(REFRESH_TIME / 60, TriggerAbstraction);
	board = BoardCreate();

	SisTick_Init(REFRESH_TIME);
	SwitchMode(HORA_SIN_CONFIGURAR);

	// -- Infinite loop
	while (true) {

		// -------------------------

		if (DigitalInputHasActivated(board->accept)) {
			tiempo_muerto = TIME_TO_CLEAN;

			if (modo == MOSTRANDO_HORA) {
				if (IsAlarmRinging(reloj))
					SnoozeAlarm(reloj, SNOOZE_TIME);
				else if (!AlarmGetTime(reloj, entrada, sizeof(entrada)))
					ActivateAlarm(reloj);
			} else if (modo == AJUSTANDO_MINUTOS_ACTUAL) {
				SwitchMode(AJUSTANDO_HORAS_ACTUAL);
			} else if (modo == AJUSTANDO_HORAS_ACTUAL) {
				ClockSetTime(reloj, entrada, sizeof(entrada));
				SwitchMode(MOSTRANDO_HORA);
			} else if (modo == AJUSTANDO_MINUTOS_ALARMA) {
				SwitchMode(AJUSTANDO_HORAS_ALARMA);
			} else if (modo == AJUSTANDO_HORAS_ALARMA) {
				AlarmSetTime(reloj, entrada, sizeof(entrada));
				SwitchMode(MOSTRANDO_HORA);
			}
		}

		if (DigitalInputHasActivated(board->cancel)) {
			tiempo_muerto = TIME_TO_CLEAN;

			if (modo == MOSTRANDO_HORA) {
				if (AlarmGetTime(reloj, entrada, sizeof(entrada)))
					DeactivateAlarm(reloj);
			} else {
				if (ClockGetTime(reloj, entrada, sizeof(entrada))) {
					SwitchMode(MOSTRANDO_HORA);
				} else {
					SwitchMode(HORA_SIN_CONFIGURAR);
				}
			}
		}

		if (DigitalInputRead(board->set_time)) {
			tiempo_muerto = TIME_TO_CLEAN;

			if (contador_set_config == 0) {
				SwitchMode(AJUSTANDO_MINUTOS_ACTUAL);
				ClockGetTime(reloj, entrada, sizeof(entrada));
				DisplayWriteBCD(board->display, entrada, sizeof(entrada));
			}
		}

		if (DigitalInputRead(board->set_alarm)) {
			tiempo_muerto = TIME_TO_CLEAN;

			if (contador_set_config == 0) {
				SwitchMode(AJUSTANDO_MINUTOS_ALARMA);
				AlarmGetTime(reloj, entrada, sizeof(entrada));
				DisplayWriteBCD(board->display, entrada, sizeof(entrada));
				DisplayToggleDots(board->display, 0, 3);
			}
		}

		if (DigitalInputHasActivated(board->decrement)) {
			tiempo_muerto = TIME_TO_CLEAN;

			if ((modo == AJUSTANDO_MINUTOS_ACTUAL) || (modo == AJUSTANDO_MINUTOS_ALARMA)) {
				DecrementBCD(&entrada[2], LIMITE_MINUTOS);
			} else if ((modo == AJUSTANDO_HORAS_ACTUAL) || (modo == AJUSTANDO_HORAS_ALARMA)) {
				DecrementBCD(&entrada[0], LIMITE_HORAS);
			}

			if ((modo == AJUSTANDO_MINUTOS_ACTUAL) || (modo == AJUSTANDO_HORAS_ACTUAL)) {
				DisplayWriteBCD(board->display, entrada, sizeof(entrada));
			} else if ((modo == AJUSTANDO_HORAS_ALARMA) || (modo == AJUSTANDO_MINUTOS_ALARMA)) {
				DisplayWriteBCD(board->display, entrada, sizeof(entrada));
				DisplayToggleDots(board->display, 0, 3);
			}
		}

		if (DigitalInputHasActivated(board->increment)) {
			tiempo_muerto = TIME_TO_CLEAN;

			if ((modo == AJUSTANDO_MINUTOS_ACTUAL) || (modo == AJUSTANDO_MINUTOS_ALARMA)) {
				IncrementBCD(&entrada[2], LIMITE_MINUTOS);
			} else if ((modo == AJUSTANDO_HORAS_ACTUAL) || (modo == AJUSTANDO_HORAS_ALARMA)) {
				IncrementBCD(&entrada[0], LIMITE_HORAS);
			}

			if ((modo == AJUSTANDO_MINUTOS_ACTUAL) || (modo == AJUSTANDO_HORAS_ACTUAL)) {
				DisplayWriteBCD(board->display, entrada, sizeof(entrada));
			} else if ((modo == AJUSTANDO_HORAS_ALARMA) || (modo == AJUSTANDO_MINUTOS_ALARMA)) {
				DisplayWriteBCD(board->display, entrada, sizeof(entrada));
				DisplayToggleDots(board->display, 0, 3);
			}
		}

		// Retardo de tiempo
		for (int index = 0; index < 100; index++) {
			for (int delay = 0; delay < 5000; delay++) {
				__asm("NOP");
			}
		}
	}
}

void SysTick_Handler(void) {
	static uint16_t contador = 0;
	uint8_t hora[CLOCK_SIZE];

	DisplayRefresh(board->display);
	ClockRefresh(reloj, CLOCK_SIZE);

	contador = (contador + 1) % 1000;
	CounterSetRefresh(DigitalInputRead(board->set_time) || DigitalInputRead(board->set_alarm), TIME_TO_SET);

	if (modo <= MOSTRANDO_HORA) {
		ClockGetTime(reloj, hora, CLOCK_SIZE);
		DisplayWriteBCD(board->display, hora, CLOCK_SIZE);

		if (contador > 500)
			DisplayToggleDots(board->display, 1, 1);

		if (AlarmGetTime(reloj, hora, sizeof(hora)))
			DisplayToggleDots(board->display, 3, 3);
	} else {
		if (tiempo_muerto == 0) {
			SwitchMode(HORA_SIN_CONFIGURAR);
		}
	}
}

// genero pruebas por error en git graph

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
