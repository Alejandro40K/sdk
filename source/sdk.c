
/*
 * Nombre de la tarea: SDK (Tarea 4)
 * Materia: Diseño de Microcontroldores
 * Autor: Alejandro Orozco Romo
 * Descripcion:
 * 	Programa en C para la K64 tal cada vez que se presione
   	el SW2 el led RGB cambia de color con la siguiente secuencia:
 		• Amarillo
		• Rojo
		• Morado
		• Azul
		• Verde
	Y cuando se presiona el SW3 el LED RGB cambia de color con la
	siguiente secuencia:
		• Verde
		• Azul
		• Morado
		• Rojo
		• Amarillo
 * Fecha de Creacion: 30/04/2024
 */


/*BIBLIOTECAS*/
#include <stdio.h>
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

/*DIRECTIVAS MACRO*/

//Led RGB
#define PIN26        26u //GREEN
#define PIN22        22u //RED
#define PIN21        21u //BLUE
//Push Button Switches
#define PIN06        6u
#define PIN04		 4u
//Frecuencia del reloj 21 Mhz de la K64
#define CLOCK_K64 (21000000U)
#define DELAY     (1000000U)

/*DECLARACION DE ESTRUCTURAS*/


gpio_pin_config_t led_config = {
		//establece el pin actual como salida
        kGPIO_DigitalOutput,
        1,
    };

//configuracion para el pin del interruptor
gpio_pin_config_t sw_config = {
		//establece el pin actual como entrada
        kGPIO_DigitalInput,
        0,
    };

int main(void) {


	//Inicializamos el reloj del Led RGB
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortE);
	//Inicializamos el reloj de lo SW
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortC);

	//Definimos las funcionalidades de cada pin

	//Led RGB
	PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio);
	//SW2 y SW3
	PORT_SetPinMux(PORTC, PIN06, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTA, PIN04, kPORT_MuxAsGpio);

	//nos ayuda a configurar el GPIO
	GPIO_PinInit(GPIOB, PIN22, &led_config);
	GPIO_PinInit(GPIOB, PIN21, &led_config);
	GPIO_PinInit(GPIOE, PIN26, &led_config);

	GPIO_PinInit(GPIOA, PIN04, &sw_config);
	GPIO_PinInit(GPIOC, PIN06, &sw_config);


    while(1)
    {

    	//Cuando precionamos el SW2
    	if (! GPIO_PinRead(GPIOC, PIN06))
    	{
    			/* NOTA: Como el Led RGB es de anodo Comun,
    			 * primero tenemos que establecer el pin
    			 * de salida en bajo y luego en alto.
    			 */

    			//Amarillo
    			GPIO_PortClear(GPIOB, 1u << PIN22); //establecemos la salida en bajo
    			GPIO_PortClear(GPIOE, 1u << PIN26);
    			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
    			GPIO_PortSet(GPIOB, 1u << PIN22);//establecemos la salida en alto
    			GPIO_PortSet(GPIOE, 1u << PIN26);

    			//Rojo
    			GPIO_PortClear(GPIOB, 1u << PIN22);
				SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
				GPIO_PortSet(GPIOB, 1u << PIN22);

				//Morado
				GPIO_PortClear(GPIOB, 1u << PIN21);
				GPIO_PortClear(GPIOB, 1u << PIN22);
				SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
				GPIO_PortSet(GPIOB, 1u << PIN21);
				GPIO_PortSet(GPIOB, 1u << PIN22);

				//Azul
				GPIO_PortClear(GPIOB, 1u << PIN21);
				SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
				GPIO_PortSet(GPIOB, 1u << PIN21);

				//Verde
				GPIO_PortClear(GPIOE, 1u << PIN26);
				SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
				GPIO_PortSet(GPIOE, 1u << PIN26);


    	}
    	//Cuando precionamos el SW3
    	else if(! GPIO_PinRead(GPIOA, PIN04))
		{
    			//Verde
    			GPIO_PortClear(GPIOE, 1u << PIN26);
    			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
    			GPIO_PortSet(GPIOE, 1u << PIN26);

    			//Azul
    			GPIO_PortClear(GPIOB, 1u << PIN21);
    			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
    			GPIO_PortSet(GPIOB, 1u << PIN21);

    			//Morado
    			GPIO_PortClear(GPIOB, 1u << PIN21);
    			GPIO_PortClear(GPIOB, 1u << PIN22);
    			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
    			GPIO_PortSet(GPIOB, 1u << PIN21);
    			GPIO_PortSet(GPIOB, 1u << PIN22);

    			//Rojo
    			GPIO_PortClear(GPIOB, 1u << PIN22);
    			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
    			GPIO_PortSet(GPIOB, 1u << PIN22);

    			//Amarillo
    			GPIO_PortClear(GPIOB, 1u << PIN22);
    			GPIO_PortClear(GPIOE, 1u << PIN26);
    			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
    			GPIO_PortSet(GPIOB, 1u << PIN22);
    			GPIO_PortSet(GPIOE, 1u << PIN26);
		}
    }
    return 0 ;
}

