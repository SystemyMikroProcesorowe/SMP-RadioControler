#include "433MHz.h"

uint8_t get_LR_power(){
	return LR_power;
}

uint8_t get_LR_dir(){
	return LR_dir;
}

void set_LR_power(uint16_t power){
	if(power > 8000){set_LR_dir(0);}
	else{set_LR_dir(1);}
	LR_power = power;
}

void set_LR_dir(uint8_t dir){
	LR_dir = dir;
}

uint8_t get_FR_power(){
	return FR_power;
}

uint8_t get_FR_dir(){
	return LR_dir;
}

void set_FR_power(uint16_t power){
	if(power > 8000){set_FR_dir(0);}
	else{set_FR_dir(1);}
	FR_power = power;
}

void set_FR_dir(uint8_t dir){
		FR_dir = dir;
}
void calculate_motor_power(uint8_t x_axis, uint8_t x_dir, uint8_t y_axis, uint8_t y_dir){	
	L_motor_power = R_motor_power = FR_power;
	if(LR_dir == 0){
		L_motor_power -= LR_power;
		L_motor_dir = 0;
		if(L_motor_power < 0){		
			L_motor_dir = 1;
			L_motor_power *=(-1);
			}
		}
	else if(LR_dir == 1){
		R_motor_power -= LR_power;
		R_motor_dir = 0;			
		if(R_motor_power < 0){		
			R_motor_dir = 1;
			R_motor_power *=(-1);
			}
		}
	if(FR_dir == 1){//jazda do przodu
		L_motor_dir ^= 1;
		R_motor_dir ^= 1;
	}
}

void prepare(){
	set_FR_power(X_axis());
	set_LR_power(Y_axis());
	
}
