//system.h suele crearse para incluir las librerias de recursos de hardware empleados.
//no es una librería es para que aca no haya una lista larga de include y para que en cualquier archivo que necesite verlas sepa directamente que incluyendo este archivo estén declaradas.
#include <stdint.h>
#include "stm32f4xx.h"			// Header del micro Librerías de Hadrware.
#include "stm32f4xx_gpio.h"		// Perifericos de E/S. Aca se encuentran los servicios de manejo de pines como PIO_SetBits
#include "stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
#include "bsp.h"

// Asociación de pines con leds (mapeo de hardware). Definiciones de nombres para reconocerlos mejor.
#define LED_V GPIO_Pin_12
#define LED_N GPIO_Pin_13
#define LED_R GPIO_Pin_14
#define LED_A GPIO_Pin_15

#define BOTON GPIO_Pin_0 //idem comentarios anterior pero para boton.
const int leds_port[4] = { GPIOD, GPIOD, GPIOD, GPIOD }; //Arrays. Conjunto de palabras
														//que se pueden ir apuntando para ver su contenido.
const int leds[4] = { LED_A, LED_R, LED_N, LED_V };

int *puntero=&leds[0];

//implementaciones de funciones

void led_on(uint8_t led) {
	GPIO_SetBits(leds_port[led], *(puntero+led)); //notar cambio de argumento del array leds_port.
	//Notar lo siguiente: el nombre del puerto (GPIOD) como no es genérico, se genera un array
	//previamente para poder seleccionar un puerto como se hizo con los pines. En este caso todos
	//están en el puerto D.
}



void led_off(uint8_t led) {
	GPIO_ResetBits(leds_port[led], leds[led]);
}

uint8_t sw_get_state(void) {

	return (GPIO_ReadInputDataBit(GPIOA, BOTON));

}

void bsp_init() {

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //se incluye en el bs_init el manejo del clock.

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

