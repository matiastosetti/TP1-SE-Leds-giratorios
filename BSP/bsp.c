//system.h suele crearse para incluir las librerias de recursos de hardware empleados.
//no es una librer�a es para que aca no haya una lista larga de include y
//para que en cualquier archivo que se necesite verlas, el programador sepa directamente que
//incluyendo este archivo est�n declaradas.
#include <stdint.h>
#include "stm32f4xx.h"			// Header del micro Librer�as de Hadrware.
#include "stm32f4xx_gpio.h"		// Perifericos de E/S. Aca se encuentran los servicios (funciones) de manejo
//de pines como PIO_SetBits
#include "stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
#include "bsp.h"   //notar que tanto en el main como en el bsp.c incluyen al .h. El main de esta manera,
//no llega a ver m�s el bcp.c

// Asociaci�n de pines con leds (mapeo de hardware). Definiciones de nombres para reconocerlos mejor.
//Nombres m�s representativos.
#define LED_V GPIO_Pin_12 //GPIO: General Propose input/output
#define LED_N GPIO_Pin_13
#define LED_R GPIO_Pin_14
#define LED_A GPIO_Pin_15

#define BOTON GPIO_Pin_0 //idem comentarios anterior pero para boton.
const int leds_port[4] = { GPIOD, GPIOD, GPIOD, GPIOD }; //Arrays. Conjunto de palabras consecutivas en
// memoria que se pueden ir apuntando para ver
//su contenido.
const int leds[4] = { LED_A, LED_R, LED_N, LED_V };

//Declaraci�n de Punteros. Apuntan en primera instancia a la direcci�n del primer array.
//Luego con el contador led se va recorriendo los elementos del array.

int *punteroSeleccionLed = &leds[0];
int *punteroSeleccionPuerto = &leds_port[0];

//implementaciones de funciones

void led_on(uint8_t led) {
	GPIO_SetBits(*(punteroSeleccionPuerto + led), *(punteroSeleccionLed + led)); //funci�n Setbits
	//tiene como argumentos el contenido de la direcci�n donde apuntan los punteros + el contador led

}

void led_off(uint8_t led) {
	GPIO_ResetBits(*(punteroSeleccionPuerto + led),
			*(punteroSeleccionLed + led));
}

uint8_t sw_get_state(void) {

	return (GPIO_ReadInputDataBit(GPIOA, BOTON));

}

//Implementaci�n de la estructura para inicialiar hardware.

void bsp_init() { //funci�n que no necesita ning�n par�metro de entrada ni devuelve ning�n valor.
	//simplemente prepara los pines para que funcionen.

	GPIO_InitTypeDef GPIO_InitStruct; //definici�n variable

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); /*se incluye en el bs_init el manejo del clock.
	 b�sicamente es una funci�n que lo prende.
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
			| GPIO_Pin_12; //esto son estrictamente los n�meros de pines que est�n conectados a los leds.
	//ac� se aplica un OR para crear una m�scara que incluye a todos los pines
	//poniendo a 1 dentro de la palabra los bits correspondientes.

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //seteado pines como salida
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //seteado de la velocidad
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // (Push/Pull)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; //resistencia de pull up o pull down
	GPIO_Init(GPIOD, &GPIO_InitStruct); //inicializa la estructura creada

	// Arranco el clock del periferico
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; //selecciono el n�mero de pin correspondiente al bot�n.
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //seteado como de entrada
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //seteado d evelocidad
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; //resistencia de pull up o pull down
	GPIO_Init(GPIOA, &GPIO_InitStruct); //inicializa la estructura creada

}

