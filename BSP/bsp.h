#ifndef __BSP_H__
#define __BSP_H__//Enclavamiento para evitar que se incluya muchas veces


//s�lo prototipos de las funciones a implementar en el .c

void led_on(uint8_t led); //prender led
void led_off(uint8_t led); //apagar led

void bsp_init(); //inicializar harware

uint8_t sw_get_state(); //funci�n que devuelve el estado del switch. No pasa argumento
//ya que no hay que decirle cual es ya que en al placa hay uno solo.

#endif

