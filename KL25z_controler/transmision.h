#include "MKL25Z4.h"                    // Device header
#include "433MHz.h"

#define transmit_pin 0 //PORTB 3
#define transmit 1
#define return_zero 2
static uint8_t current_byte = 0;	//range 0:17
static uint8_t GetData = 1;		//get data flag

void transmit_0();		//send 0 to 1 change
void transmit_1();		//send 1 to 0 change
void return_to_zero();//transmit second part of byte
void transmision_init();
void start_transmision();//violation (send LOW 4-times)
void transmit_byte();
uint8_t get_GetData();	//return value of GetData flag
void clear_GetData();		//set GetData flag