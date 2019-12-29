#include "MMA8451Q.h"


void ACCEL_init(void){
	I2C_init();
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;				//Turn on PortA for MMA interrupt
	PORTA -> PCR[14] |= PORT_PCR_MUX(1)				//
										| PORT_PCR_ISF_MASK			//Clear interrupt falg
										| PORT_PCR_IRQC(0xA);		//Config for fallin edge
	
	NVIC_ClearPendingIRQ(I2C0_IRQn);				/* Clear NVIC any pending interrupts on PORTA14 */
	NVIC_EnableIRQ(I2C0_IRQn);							/* Enable NVIC interrupts source for PORTA14 */
	NVIC_SetPriority (I2C0_IRQn, 0);				/* PORTA14 interrupt priority level  */ 
	
	uint8_t reg_val = 1;
	
	I2C_write(MMA_addr, CTRL_REG2, 0x40);
	while(reg_val){
		reg_val = I2C_read(CTRL_REG2, CTRL_REG2) & 0x40;
	}
	I2C_write(MMA_addr, XYZ_DATA_CFG, 0x00);
	I2C_write(MMA_addr, CTRL_REG2, 0x02);
	I2C_write(MMA_addr, CTRL_REG2, 0x3D);
	
	I2C_write(MMA_addr, CTRL_REG3, 0x40);
	I2C_write(MMA_addr, CTRL_REG4, 0x20);
	I2C_write(MMA_addr, CTRL_REG5, 0x20);
	I2C_write(MMA_addr, ASLP_COUNT_REG, 0x03);
	I2C_write(MMA_addr, CTRL_REG2, 0x1C);
	I2C_write(MMA_addr, CTRL_REG1, 0x61);
}

uint16_t MMA_DATA(uint8_t* DATA_S){
	I2C_multiRegRead(MMA_addr, OUT_X_MSB_REG, 6, DATA_S);
}

