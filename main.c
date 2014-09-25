//Se limpio el main.c para que sea solo aplicacion y abstraerlo del hardware.
#include<stdint.h> //librería standar de definiciones para poder usar los nombres mas entendibles (uint32_t) en vez de short, int, float, etc.
#include "bsp.h"

/* Simple funcion de delay */

//prototipos de funciones a emplear en el main
void Delay(volatile uint32_t nCount); //se deja ya que es un NOP. Es decir hacer nada por software.

void secuencia_leds(int led, int contador);

int main(void) {

	int contador = 0x1FFF;
	int numero_de_led;

	bsp_init(); //llamamos para inicializar hardware

	while (1) {

		if (sw_get_state() == 1) {
			contador = contador + contador / 25; //contador+=contador/25

		}

//		for (numero_de_led = 0; numero_de_led < 4; numero_de_led++)
//			secuencia_leds(numero_de_led, contador);

		for (numero_de_led = 0; numero_de_led < 4; numero_de_led++)
					secuencia_leds(numero_de_led, contador);


	}

}

void Delay(volatile uint32_t nCount) { //notar que es pasar tiempo haciendo nada. Se usaó un lazo while para que quede desconatdo el ncount hasta que se haga cero y recien ahi salirse.
	while (nCount--) {
	}
}
void secuencia_leds(int led, int tiempo) {

	led_on(led);
	Delay(tiempo);
	led_off(led);
}

