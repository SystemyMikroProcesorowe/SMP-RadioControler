#include "MKL25Z4.h"                    // Device header
#include "I2C.h" 
#include "UART_0.h" 
#include "leds.h"
#include "MMA8451Q.h"

int ii = 0xaffff;// delay value
volatile uint8_t DataReady = 1;
volatile uint8_t RAW_DATA[6];
uint16_t A_DATA = 0;

void main(void){
	UART_init(9600);
	print_char('U');
	I2C_init();
	print_char('F');
	ACCEL_init(); 
	print_word("\n\rInit Uart, I2C, Accel done \n\r");
	A_DATA = I2C_read(MMA_addr, WHO_AM_I);
	print_word("Who I am: \n\r");
	print_num(A_DATA);
	print_word("\n\rI2C 1st read done \n\r");
	I2C_multiRegRead(MMA_addr, OUT_X_MSB_REG, 6, RAW_DATA);
//	print_word(RAW_DATA[0]);
	print_word("I2C 2nd read done \n\r");

	while(1){
		if(DataReady){
			DataReady = 0;
			print_word("X-axis: ");
			print_num(X_axis());
			print_word("\n\r");
			print_word("\rY-axis: ");
			print_num(Y_axis());
			print_word("\n\r");
		}
			ii = 0xbffff;
		while(ii){
			--ii;
		}
		//print_word("\rData ready");
		DataReady = 1;
	}
	
};


void PORTA_IRQHandler()
{
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;			// Clear the interrupt flag 
	print_word("\rInterroupt");
	DataReady = 1;	
}

