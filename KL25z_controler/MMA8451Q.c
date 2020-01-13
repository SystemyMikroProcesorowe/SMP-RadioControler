#include "MMA8451Q.h"
#include "UART_0.h" 

uint8_t AccData[6];

void ACCEL_init(void){
    I2C_write(MMA_addr, CTRL_REG1, 0x01);
    
    
    
    /*
    I2C_init();
    
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;              //Turn on PortA for MMA interrupt
    PORTA -> PCR[14] |= PORT_PCR_MUX(1)             //
                                        | PORT_PCR_ISF_MASK         //Clear interrupt falg
                                        | PORT_PCR_IRQC(0xB);       //Config for fallin edge
    
    NVIC_ClearPendingIRQ(I2C0_IRQn);                /* Clear NVIC any pending interrupts on PORTA14 */
    //NVIC_EnableIRQ(I2C0_IRQn);                          /* Enable NVIC interrupts source for PORTA14 */
    //NVIC_SetPriority (I2C0_IRQn, 0);                /* PORTA14 interrupt priority level  */ 
    
/*
    I2C_write(MMA_addr, XYZ_DATA_CFG, 0x00); // max 2g
    I2C_write(MMA_addr, CTRL_REG2, 0x02); // high resolution enabled (oversampling)
    I2C_write(MMA_addr, CTRL_REG1, 0x3D);//   1,56hz,lownoise,,active
    
    I2C_write(MMA_addr, CTRL_REG3, 0x40);// fifo
    I2C_write(MMA_addr, CTRL_REG4, 0x20);// fifo interrupt enable
    I2C_write(MMA_addr, CTRL_REG5, 0x20);//  Interrupt is routed to INT1 pin ???
    I2C_write(MMA_addr, ASLP_COUNT_REG, 0x03); //time ???
    I2C_write(MMA_addr, CTRL_REG2, 0x1C); // sleep mode: low power, auto sleep enabled
    I2C_write(MMA_addr, CTRL_REG1, 0x61); // 1,56hz in auto sleep mode //It is important to note that when the device is auto-sleep mode, the system ODR and the data rate for all the system functional
                                                                       //blocks are overridden by the data rate set by the ASLP_RATE field.
    */
    
    /*I2C_write(MMA_addr, CTRL_REG1, 0x00);             // Standby mode to allow writing to the offset registers 
    I2C_write(MMA_addr, CTRL_REG3, 0x00);             // Push-pull, active low interrupt
    I2C_write(MMA_addr, CTRL_REG4, 0x21);             // Enable DRDY interrupt
    I2C_write(MMA_addr, CTRL_REG5, 0x21);             // DRDY interrupt routed to INT1 - PTA14
    I2C_write(MMA_addr, CTRL_REG1, 0x3D);             // ODR = 1.56Hz, Reduced noise, Active mode */
    }

uint16_t MMA_DATA(uint8_t* DATA_S){
    I2C_multiRegRead(MMA_addr, OUT_X_MSB_REG, 6, DATA_S);
}