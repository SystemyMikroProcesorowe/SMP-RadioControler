#include "MKL25Z4.h"                    // Device header
#include "433MHz.h"

#define transmit_pin 0 //PORTB 3
#define transmit 1
#define return_zero 2
static uint8_t current_byte = 0;	//range 0:23
<<<<<<< Updated upstream

=======
static uint8_t GetData = 1;		//get data flag
static uint8_t byte=0;
	
>>>>>>> Stashed changes
void transmit_0();
void transmit_1();
void return_to_zero();
void transmision_init();
void start_transmision();
void transmit_byte();