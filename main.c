//Se limpio el main.c para que sea solo aplicacion y abstraerlo del hardware.
#include<stdint.h> //librería standar de definiciones para poder usar los nombres
//mas entendibles (uint32_t) en vez de short, int, float, etc.
#include "bsp.h" //se debe incluir ya que en el mismo se encuentran los prototipos de
//funciones que se usan en la implementación de la función secuencia_leds (...)

//prototipos de funciones a emplear en el main.c

void Delay(volatile uint32_t nCount); // Simple funcion de delay. Se deja ya que es un NOP.
//Es decir hacer nada por software. Lo más preciso y conveniente es usar un timer con Interrupción

void secuencia_leds(int led, int contador);

int main(void) {

	int contador = 0x1FFF; //Declacración de variables locales a la función main.
	int numero_de_led;

	bsp_init(); //llamamos para inicializar hardware. Estructura con máscaras que
	//tocan bits de los registros de los periféricos para configurarlos.

	while (1) { //bucle infinito

		if (sw_get_state() == 1) {
			contador = contador + contador / 25; //contador+=contador/25

		}

		for (numero_de_led = 0; numero_de_led < 4; numero_de_led++)
			secuencia_leds(numero_de_led, contador);

	}

}

void Delay(volatile uint32_t nCount) { //notar que es pasar tiempo haciendo nada.
	//Se usó un lazo while para que quede desconatdo el ncount hasta que se haga cero
	//y recien ahi salga debido a que cero es falso..
	while (nCount--) {
	}
}
void secuencia_leds(int led, int tiempo) {

	led_on(led);
	Delay(tiempo);
	led_off(led);
}
/* TODO AQUELLO REFERIDO AL HARDWARE SE INCLUYE EN EL .C. Desde su inicialización hasta el manejo del mismo*/
