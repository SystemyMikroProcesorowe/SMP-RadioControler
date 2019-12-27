#include "MKL25Z4.h"                    // Device header
#include "I2C.h" 
#include "UART_0.h" 
#include "leds.h"

void main(void){
	I2C_init();
	UART_init(9600);
	
	while(1){
		
	}
	
};
