/**
 * @file reloj.h
 * @author Joel Jassan <joeljassan@hotmail.com>
 * @brief  Archivos de cabecera para reloj.c
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023. All rights reserved.
 *
 */
/* --------------------------------------------------------------------------------------------- */

/*---  Includes  ------------------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* ---  Macros definitions  -------------------------------------------------------------------- */

#define CLOCK_SIZE 6
#define ALARM_SIZE 4

// Puntero a la estructura de tipo clock_s
typedef struct clock_s * clock_t;

// Puntero a la estructura de tipo alarm_s
typedef struct alarm_s * alarm_t;

// Funcion
typedef void (*clock_event_t)();

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

/**
 * @brief Metodo para crear un reloj despertador.
 *
 * @param tics_per_second Cantidad de pulsos de reloj para aumentar una cuenta.
 * @return clock_t Puntero al descriptor del reloj
 */
clock_t ClockCreate(int tics_per_second, clock_event_t event_handler);

/**
 * @brief Metodo para mostrar la hora del reloj.
 *
 * @param reloj Puntero al descriptor del reloj que se debe leer
 * @param hora Puntero donde se carga la hora del reloj
 * @param size Tamaño del reloj
 * @return true La hora mostrada es valida
 * @return false La hora mostrada es invalida
 */
bool ClockGetTime(clock_t reloj, uint8_t * hora, int size);

/**
 * @brief Metodo para setear una hora en el reloj
 *
 * @param reloj Puntero al descriptor del reloj
 * @param hora Puntero que guarda la hora del reloj a setear.
 * @param size Tamaño del reloj
 * @return true Se seteo la hora del reloj
 * @return false No se seteo la hora del reloj
 */
bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size);

/**
 * @brief Metodo para sumar +1 en la unidad de segundos (falta la referencia de tics de ClkCreate)
 *
 * @param reloj Puntero al descriptor del reloj
 * @param size Tamaño del reloj
 */
bool ClockRefresh(clock_t reloj, int size);

/**
 * @brief Metodo para mostrar la hora de la alarma
 *
 * @param reloj Puntero al descriptor del reloj
 * @param alarm_time Puntero donde se carga la alarma para mostrarla
 * @param size Tamaño del reloj de alarma
 * @return true Alarma activa
 * @return false Alarma inactiva
 */
bool AlarmGetTime(clock_t reloj, uint8_t * alarm_time, int size);

/**
 * @brief Metodo para setear la hora de la alarma
 *
 * @param reloj Puntero al descriptor del reloj
 * @param alarm_time Puntero que almacena la hora de la alarma
 * @param size Tamaño del reloj de la alarma
 * @return true Alarma activa
 * @return false Alarma inactiva
 */
bool AlarmSetTime(clock_t reloj, const uint8_t * alarm_time, int size);

/**
 * @brief Metodo para activar la alarma
 *
 * @param reloj Puntero al descriptor del reloj
 * @return true Alarma Activa
 * @return false Alarma Inactiva
 */
bool ActivateAlarm(clock_t reloj);

/**
 * @brief Metodo para desactivar la alarma
 *
 * @param reloj Puntero al descriptor del reloj
 * @return true Alarma Activa
 * @return false Alarma Inactiva
 */
bool DeactivateAlarm(clock_t reloj);

/**
 * @brief Metodo para disparar la alarma (hacerla sonar)
 *
 * @param reloj Puntero al descriptor del reloj
 * @return true Alarma sonando
 * @return false Alarma sin sonar
 */
void TriggerAlarm(clock_t reloj);

/**
 * @brief Metodo para posponer la alarma 5 minutos
 *
 * @param reloj Puntero al descriptor del reloj
 * @param time Tiempo que se posterga la alarma
 * @return true Alarma sonando
 * @return false Alarma sin sonar
 */
bool SnoozeAlarm(clock_t reloj, int time);

/**
 * @brief Metodo para mostrar si la alarma esta sonando
 *
 * @param reloj Puntero al descriptor del reloj
 * @return true Alarma sonando
 * @return false Alarma sin sonar
 */
bool IsAlarmRinging(clock_t reloj);

/**
 * @brief Metodo para cancelar la alarma hasta el dia siguiente
 *
 * @param reloj Puntero al descriptor del reloj
 * @return true Alarma cancelada
 * @return false Alarma no cancelada
 */
bool CancelAlarm(clock_t reloj);

/*---  End of File  ---------------------------------------------------------------------------- */
