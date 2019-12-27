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
	
}