/*---  Code Information ------------------------------------------------------------------------ */
// Autor: Jassan, Joel
// Date:
//
// Project: Hardware Abstraction Layer Creation
/*---------------------------------------------------------------------------------------------- */

/*---  Includes  ------------------------------------------------------------------------------- */
#include "bsp.h"

/*---  Macros and Definitions  ----------------------------------------------------------------- */

// Control de logica invertida.
// Creo que deberia ir dentro de "digital".
#ifndef inverted_logic
#define inverted_logic 0
#endif

static struct board_s board = {0};

/*---  Private Data Declaration  --------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

//! Funcion de configuracion del hardware de la edu-ciaa
board_t MainBoardInit(void);

//! Funcion de configuracion del hardware de los digitos de pantalla
void DigitsInit(void);

//! Funcion de configuracion del hardware de los segmentos
void SegmentsInit(void);

//! Funcion de configuracion del hardware del buzzer
void BuzzerInit(void);

//! Funcion de configuracion del hardware de las teclas
void KeysInit(void);

//! Funcion para apagar todos los segmentos y digitos
void ScreenTurnOff(void);

/**
 * @brief Funcion para encender ciertos segmentos de un display
 *
 * @param segments mascara con los segmentos a encender
 */
void SegmentsTurnOn(uint8_t segments);

/**
 * @brief Funcion para encender solo un digito de una pantalla multiplexada
 *
 * @param digit Numero de digito a encender
 */
void DigitTurnOn(uint8_t digit);

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------- */

/*---  Private Function Implementation  -------------------------------------------------------- */

board_t MainBoardInit(void) {
	// Chip_SCU_PinMuxSet(LED_R_PORT, LED_R_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_R_FUNC);
	// board.led_RGB_rojo = DigitalOutputCreate(LED_R_GPIO, LED_R_BIT, inverted_logic);

	// Chip_SCU_PinMuxSet(LED_G_PORT, LED_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_G_FUNC);
	// board.led_RGB_verde = DigitalOutputCreate(LED_G_GPIO, LED_G_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(LED_B_PORT, LED_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_B_FUNC);
	board.led_RGB_azul = DigitalOutputCreate(LED_B_GPIO, LED_B_BIT, inverted_logic);

	/******************/

	// Chip_SCU_PinMuxSet(LED_1_PORT, LED_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_1_FUNC);
	// board.led_rojo = DigitalOutputCreate(LED_1_GPIO, LED_1_BIT, inverted_logic);

	// Chip_SCU_PinMuxSet(LED_2_PORT, LED_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_2_FUNC);
	// board.led_amarillo = DigitalOutputCreate(LED_2_GPIO, LED_2_BIT, inverted_logic);

	// Chip_SCU_PinMuxSet(LED_3_PORT, LED_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_3_FUNC);
	// board.led_verde = DigitalOutputCreate(LED_3_GPIO, LED_3_BIT, inverted_logic);

	/******************/
	// Chip_SCU_PinMuxSet(TEC_1_PORT, TEC_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_1_FUNC);
	// board.tec_1 = DigitalInputCreate(TEC_1_GPIO, TEC_1_BIT, inverted_logic);

	// Chip_SCU_PinMuxSet(TEC_2_PORT, TEC_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_2_FUNC);
	// board.tec_2 = DigitalInputCreate(TEC_2_GPIO, TEC_2_BIT, inverted_logic);

	// Chip_SCU_PinMuxSet(TEC_3_PORT, TEC_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_3_FUNC);
	// board.tec_3 = DigitalInputCreate(TEC_3_GPIO, TEC_3_BIT, inverted_logic);

	// Chip_SCU_PinMuxSet(TEC_4_PORT, TEC_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_4_FUNC);
	// board.tec_4 = DigitalInputCreate(TEC_4_GPIO, TEC_4_BIT, inverted_logic);

	return &board;
}

void DigitsInit(void) {
	Chip_SCU_PinMuxSet(DIGIT_1_PORT, DIGIT_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_1_FUNC);
	board.dig_1 = DigitalOutputCreate(DIGIT_1_GPIO, DIGIT_1_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(DIGIT_2_PORT, DIGIT_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_2_FUNC);
	board.dig_2 = DigitalOutputCreate(DIGIT_2_GPIO, DIGIT_2_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(DIGIT_3_PORT, DIGIT_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_3_FUNC);
	board.dig_3 = DigitalOutputCreate(DIGIT_3_GPIO, DIGIT_3_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(DIGIT_4_PORT, DIGIT_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_4_FUNC);
	board.dig_4 = DigitalOutputCreate(DIGIT_4_GPIO, DIGIT_4_BIT, inverted_logic);
}

void SegmentsInit(void) {

	Chip_SCU_PinMuxSet(SEGMENT_A_PORT, SEGMENT_A_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_A_FUNC);
	board.seg_A = DigitalOutputCreate(SEGMENT_A_GPIO, SEGMENT_A_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(SEGMENT_B_PORT, SEGMENT_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_B_FUNC);
	board.seg_B = DigitalOutputCreate(SEGMENT_B_GPIO, SEGMENT_B_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(SEGMENT_C_PORT, SEGMENT_C_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_C_FUNC);
	board.seg_C = DigitalOutputCreate(SEGMENT_C_GPIO, SEGMENT_C_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(SEGMENT_D_PORT, SEGMENT_D_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_D_FUNC);
	board.seg_D = DigitalOutputCreate(SEGMENT_D_GPIO, SEGMENT_D_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(SEGMENT_E_PORT, SEGMENT_E_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_E_FUNC);
	board.seg_E = DigitalOutputCreate(SEGMENT_E_GPIO, SEGMENT_E_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(SEGMENT_F_PORT, SEGMENT_F_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_F_FUNC);
	board.seg_F = DigitalOutputCreate(SEGMENT_F_GPIO, SEGMENT_F_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(SEGMENT_G_PORT, SEGMENT_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_G_FUNC);
	board.seg_G = DigitalOutputCreate(SEGMENT_G_GPIO, SEGMENT_G_BIT, inverted_logic);

	Chip_SCU_PinMuxSet(SEGMENT_P_PORT, SEGMENT_P_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_P_FUNC);
	board.seg_P = DigitalOutputCreate(SEGMENT_P_GPIO, SEGMENT_P_BIT, inverted_logic);
}

void BuzzerInit(void) {
	Chip_SCU_PinMuxSet(BUZZER_PORT, BUZZER_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | BUZZER_FUNC);
	board.buzzer = DigitalOutputCreate(BUZZER_GPIO, BUZZER_BIT, inverted_logic);
}

void KeysInit(void) {
	Chip_SCU_PinMuxSet(KEY_ACCEPT_PORT, KEY_ACCEPT_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_ACCEPT_FUNC);
	board.accept = DigitalInputCreate(KEY_ACCEPT_GPIO, KEY_ACCEPT_BIT, false);

	Chip_SCU_PinMuxSet(KEY_CANCEL_PORT, KEY_CANCEL_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_CANCEL_FUNC);
	board.cancel = DigitalInputCreate(KEY_CANCEL_GPIO, KEY_CANCEL_BIT, false);

	Chip_SCU_PinMuxSet(KEY_F1_PORT, KEY_F1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F1_FUNC);
	board.set_time = DigitalInputCreate(KEY_F1_GPIO, KEY_F1_BIT, false);

	Chip_SCU_PinMuxSet(KEY_F2_PORT, KEY_F2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F2_FUNC);
	board.set_alarm = DigitalInputCreate(KEY_F2_GPIO, KEY_F2_BIT, false);

	Chip_SCU_PinMuxSet(KEY_F3_PORT, KEY_F3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F3_FUNC);
	board.increment = DigitalInputCreate(KEY_F3_GPIO, KEY_F3_BIT, false);

	Chip_SCU_PinMuxSet(KEY_F4_PORT, KEY_F4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F4_FUNC);
	board.decrement = DigitalInputCreate(KEY_F4_GPIO, KEY_F4_BIT, false);
}

void ScreenTurnOff(void) {
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, DIGITS_GPIO, DIGITS_MASK);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEGMENTS_GPIO, SEGMENTS_MASK);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, false);
}

void SegmentsTurnOn(uint8_t segments) {
	Chip_GPIO_SetValue(LPC_GPIO_PORT, SEGMENTS_GPIO, (segments)&SEGMENTS_MASK);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, (segments & SEGMENT_P));
}

void DigitTurnOn(uint8_t digit) {
	Chip_GPIO_SetValue(LPC_GPIO_PORT, DIGITS_GPIO, ((1 << (3 - digit)) & DIGITS_MASK));
}

/*---  Public Function Implementation  --------------------------------------------------------- */

board_t BoardCreate(void) {

	// Inicializo los pines de la edu-ciaa (no compatible con el poncho)
	MainBoardInit();

	// Inicializo el poncho.
	DigitsInit();
	SegmentsInit();
	BuzzerInit();
	KeysInit();

	board.display = DisplayCreate(4, &(struct display_driver_s){
										 .ScreenTurnOff = ScreenTurnOff,
										 .SegmentsTurnOn = SegmentsTurnOn,
										 .DigitTurnOn = DigitTurnOn,
									 });

	return &board;
}

void SisTick_Init(uint16_t ticks) {
	__asm volatile("cpsid i");

	/* Activate SysTick */
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / ticks);

	/* Update priority set by Systick_Config */
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

	__asm volatile("cpsie i");
}

/*---  End of File  ---------------------------------------------------------------------------- */