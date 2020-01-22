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
	++current_byte;
	if(24 == current_byte){
		current_byte = 0;
		//GetData = 1; //set flag of data prepare
	}
}
void transmit_byte(){
	if(1 == get_byte_value(current_byte)){
		transmit_1();
	}
	else{
		transmit_0();
	}
}

//uint16_t ii =0;


void PIT_IRQHandler(void)										//PIT interrupt handler function
{
	static uint8_t i = transmit;
	if(transmit == i){	
		transmit_byte();	
	}
	if(return_zero == i){ 
		return_to_zero();
		i = 0;
	}
	i++;
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;						//Clear PIT0 falg
	/*
	i++;
	if (1000 == i)
	{PTB -> PSOR |= (1UL << transmit_pin);
	}
	else if (2000 == i)
	{PTB -> PCOR |= (1UL << transmit_pin);
	i=0;}*/
	
}
