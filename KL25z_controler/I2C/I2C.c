#include "I2C.h"

//macros for i2c (pooling)
#define I2C_start 	I2C0 -> C1 |= I2C_C1_MST_MASK;
#define I2C_STOP 		I2C0 -> C1 ~I2C_C1_MST_MASK;
#define I2C_RESTART I2C0 -> C1 |= I2C_C1_RSTA_MASK;

#define I2C_TRAN 		I2C0 -> C1 |= I2C_C1_TX_MASK;
#define I2C_REC 		I2C0 -> C1 |= I2C_C1_TX_MASK;

#define BUSY_ACK 		while(I2C0 -> S & 0x01)
#define TRANS_COMP 	while(!(I2C0 -> S & IC2_S_TCF_MASK))
#define I2C_WAIT 		while(I2C0 -> S & I2C_S_ICIF_MASK)==0){}\
													I2C0 -> S |= I2C_S_IICIF_MASK;

#define NACK 				I2C0 -> C1 |= I2C_C1_TXAK_MASK;
#define ACK 				I2C0 -> C1 &= ~I2C_C1_TXAK_MASK;
///
	
void I2C_init(){
	SIM -> SCGC4 |= SIM_SCGC4_I2C0_MASK;		/*Enable clock for I2C module*/
	SIM -> SCGC5 |= SIM_SCGC5_PORTE_MASK;		/*Enable clock for PORTB module*/
	
	I2C0 -> F		|= I2C_F_MULT(2)
							|  I2C_F_ICR(7);
	I2C0 -> C1 	|= I2C_C1_IICEN_MASK
							|  I2C_C1_IICIE_MASK;

	NVIC_ClearPendingIRQ(I2C0_IRQn);				/* Clear NVIC any pending interrupts on I2C */
	NVIC_EnableIRQ(I2C0_IRQn);							/* Enable NVIC interrupts source for I2C */
	NVIC_SetPriority (I2C0_IRQn, 0);			/* ToDo 7.2a: Set I2C interrupt priority level  */ 
	
	PORTE -> PCR[24] |= PORT_PCR_MUX(5);
	PORTE -> PCR[25] |= PORT_PCR_MUX(5);
}

void I2C0_IRQHandler(){
	
}