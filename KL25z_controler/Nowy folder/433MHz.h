#include "MKL25Z4.h"                    // Device header

uint8_t strat_frame = 0b11111011;
uint8_t current_bit = 0;
uint8_t tx_buff[24] = {};
uint8_t LR_power = 0;
uint8_t LR_dir = 0;				//L=0, R=1
uint8_t FR_power = 0;
uint8_t FR_dir = 0;				//F=0, R=1
int L_motor_power = 0;
int R_motor_power = 0;
uint8_t L_motor_dir = 0;	//0 - front 1 - back
uint8_t R_motor_dir = 0;	//0 - front 1 - back
/*left right calculation*/
uint8_t get_LR_power();
uint8_t get_LR_dir();
void set_LR_power(uint16_t power);
void set_LR_dir(uint8_t dir);
/*front rear calculation*/
uint8_t get_FR_power();
uint8_t get_FR_dir();
void set_FR_power(uint16_t power);
void set_FR_dir(uint8_t dir);
/*engin power*/
void calcuate_motor_power();//uint8_t x_axis, uint8_t x_dir, uint8_t y_axis, uint8_t y_dir);
uint8_t get_L_motor_power();
uint8_t get_R_motor_power();
uint8_t get_L_motor_dir();
uint8_t get_R_motor_dir();
/*transmision*/	
void prepare_data();
void prepare_data_frame();
void transmit();
	