#include "transmision.h"


void transmision_init(){
	SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB -> PCR[transmit_pin] |= PORT_PCR_MUX(1);
	FPTB -> PDDR |= (1 << transmit_pin);
}
void transmit_0(){
	FPTB -> PCOR |= (1 << transmit_pin);
}
void transmit_1(){
	FPTB -> PSOR |= (1 << transmit_pin);
}
void return_to_zero(){
	FPTB -> PCOR |= (1 << transmit_pin);	
}
void transmit_byte(uint8_t Tr){
	
	if(1 == Tr){
		if(0 == get_byte_value(current_byte)){
			transmit_1();
		}
		else{
			transmit_0();
		}
	}
	else if(2 == Tr){
		++current_byte;
		return_to_zero();
		if(24 == current_byte){
			current_byte = 0;
			//GetData = 1; //set flag of data prepare
		}
	}
}









uint16_t i =0;
uint16_t num =0;

void PIT_IRQHandler(void)										//PIT interrupt handler function
{
	i++;
	if (1000 == i)
	{PTB -> PSOR |= (1UL << transmit_pin);
	}
	else if (2000 == i)
	{PTB -> PCOR |= (1UL << transmit_pin);
	i=0;}
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;						//Clear PIT0 falg
}