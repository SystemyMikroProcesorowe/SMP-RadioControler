#include "MKL25Z4.h"                    // Device header
#include "I2C.h" 
#include "UART_0.h" 
#include "leds.h"
#include "MMA8451Q.h"

uint8_t DataReady = 1;
uint8_t RAW_DATA[6];
uint16_t A_DATA = 0;
void main(void){
	UART_init(9600);
	print_char('U');
	I2C_init();
	print_char('F');
	ACCEL_init(); 
	print_word("Init done \n\r");
	A_DATA = I2C_read(MMA_addr, WHO_AM_I);
	print_word(A_DATA);
	print_word("I2C 1st read done \n\r");
	//I2C_multiRegRead(MMA_addr, OUT_X_MSB_REG, 2, RAW_DATA);
//	print_word(RAW_DATA[0]);
	print_word("I2C 2nd read done \n\r");
	
	while(1){
		if(DataReady){
			DataReady = 0;
			MMA_DATA(RAW_DATA);
			
			A_DATA = (RAW_DATA[0]<<8 | RAW_DATA[1]>>2);
			print_word("X-axis: ");
			print_num(A_DATA);
			print_char('\n');
			A_DATA = (RAW_DATA[2]<<8 | RAW_DATA[3]>>2);
			print_word("Y-axis: ");
			print_num(A_DATA);
			print_char('\n');
			A_DATA = (RAW_DATA[4]<<8 | RAW_DATA[5]>>2);
			print_word("Z-axis: ");
			print_num(A_DATA);
			print_char('\n');
		}
	}
	
};


void PORTA_IRQHandler()
{
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;			// Clear the interrupt flag 
	DataReady = 1;	
}

