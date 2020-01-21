#include "MKL25Z4.h"                    // Device header
#include "I2C.h" 
#include "UART_0.h" 
#include "MMA8451Q.h"
#include "433MHz.h"
#include "PIT_timer.h"
#include "transmision.h"

int ii = 0xaffff;// delay value
volatile uint8_t GetData = 1;		//get data flag
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
	PIT_init();
	transmision_init();
	
	while(1){
		if(GetData){
			GetData = 0;
			prepare_data();
			prepare_data_frame();
			print_word("L-motor power: ");
			print_num(get_L_motor_power());
			print_word("	");
			print_word("R-motor power: ");
			print_num(get_R_motor_power());
			print_word("	");
			print_word("X: ");
			print_num(X_axis());
			print_word("	");
			print_word("Y: ");
			print_num(Y_axis());
			print_word("\r");			
		}
			ii = 0xbffff;
		while(ii){
			--ii;
		}
		GetData = 1;
	}
	
};


/*void PORTA_IRQHandler()
{
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;			// Clear the interrupt flag 
	print_word("\rInterroupt");
	DataReady = 1;	
}*/

