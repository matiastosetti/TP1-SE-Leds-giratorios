#include "stm32f4xx.h"			// Header del micro
#include "stm32f4xx_gpio.h"		// Perifericos de E/S
#include "stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
/* Simple funcion de delay */
void Delay(__IO uint32_t nCount);

/* Inicializa los puertos E/S */
void ES_Init();

// Definiciones de hardware
#define LED_V GPIO_Pin_12
#define LED_N GPIO_Pin_13
#define LED_R GPIO_Pin_14
#define LED_A GPIO_Pin_15

#define BOTON GPIO_Pin_0

const int leds[4] = { LED_A, LED_R, LED_N, LED_V };

void secuencia_leds(int const leds_de_color, int contador);

int main(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// configuro GPIO
	ES_Init();

	//int pepe = 0;

	int contador = 0x1FFF;
	int numero_de_led;

	while (1) {

		if (GPIO_ReadInputDataBit(GPIOA, BOTON) == 1) {
			contador = contador + contador / 25; //contador+=contador/25

		}

		for (numero_de_led = 0; numero_de_led < 4; numero_de_led++)
			secuencia_leds(numero_de_led, contador);

//		Para secuencia de leds en círculo. Programa no optimizado.
//		GPIO_SetBits(GPIOD, LED_A);
//				Delay(contador);
//				GPIO_ResetBits(GPIOD, LED_A);
//		GPIO_SetBits(GPIOD, LED_V);
//				Delay(contador);
//				GPIO_ResetBits(GPIOD, LED_V);
//		GPIO_SetBits(GPIOD, LED_N);
//				Delay(contador);
//				GPIO_ResetBits(GPIOD, LED_N);
//		GPIO_SetBits(GPIOD, LED_R);
//				Delay(contador);
//				GPIO_ResetBits(GPIOD, LED_R);

		/*	Se prende y apaga el led azul cada cierto tiempo definido.

		 GPIO_SetBits(GPIOD, LED_A);
		 Delay(0x1FFFFF);
		 GPIO_ResetBits(GPIOD, LED_A);
		 Delay(0x1FFFFF);
		 */

		//Led naranja sigue pulsador: por estado. Led azul detecta flanco
		//y se enciende o se apaga.
//		if (GPIO_ReadInputDataBit(GPIOA, BOTON) == 1) {
//			GPIO_SetBits(GPIOD, LED_N);
//			if (!pepe) {
//				Delay(0xFFF);
//				GPIO_ToggleBits(GPIOD, LED_A);
//				pepe = 1;
//			}
//
//		} else {
//			GPIO_ResetBits(GPIOD, LED_N);
//			pepe = 0;
//		}
		/*
		 El led azul parpadea y se prende el naranja sólo cuando se pulsa el botón.
		 GPIO_SetBits(GPIOD, LED_A);
		 Delay(0x1FFFFF);
		 GPIO_ResetBits(GPIOD, LED_A);
		 Delay(0x1FFFFF);

		 if (GPIO_ReadInputDataBit(GPIOA, BOTON) == 1) {
		 GPIO_SetBits(GPIOD, LED_N);
		 }
		 */

	}
}

void secuencia_leds(int leds_de_color, int contador) {

	GPIO_SetBits(GPIOD, leds[leds_de_color]);
	Delay(contador);
	GPIO_ResetBits(GPIOD, leds[leds_de_color]);
}

void ES_Init() {
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
			| GPIO_Pin_12;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // (Push/Pull)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	// Arranco el clock del periferico
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Delay(__IO uint32_t nCount) {
	while (nCount--) {
	}
}
