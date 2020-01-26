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
	if(1 == get_byte_value(current_byte)){
	FPTB -> PCOR |= (1 << transmit_pin);}	
	else{	FPTB -> PSOR |= (1 << transmit_pin);}
	++current_byte;
	if(18 == current_byte){
		current_byte = 0;
		GetData = 1; //set flag of data prepare
	}
}


void transmit_byte(){
	if(1 == get_byte_value(current_byte-4)){
		transmit_1();
	}
	else{
		transmit_0();
	}
}


uint8_t get_GetData(){
	return GetData;
}


void clear_GetData(){
	GetData = 0;
}


void start_transmision(){
	FPTB -> PCOR |= (1 << transmit_pin);
	current_byte++;
}


void PIT_IRQHandler(void)										//PIT interrupt handler function
{
	if(current_byte < 4){start_transmision();}
	else{
		static uint8_t i = transmit;
		if(transmit == i){	
			transmit_byte();	
		}
		if(return_zero == i){ 
			return_to_zero();
			i = 0;
		}
		i++;
	}
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;						//Clear PIT0 falg
}
