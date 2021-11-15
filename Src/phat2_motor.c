
#include "phat2_motor.h"

// Helper macro - index is always 1 here (channel 1 <-> index 0, channel 2 <-> index 1)
#define TMC2209_CRC(data, length) tmc_CRC8(data, length, 1)



//static UART_Config *TMC2209_UARTChannel;
static UART_HandleTypeDef *TMC2209_UARTChannel;



                        
static ConfigurationTypeDef *TMC2209_S1_cfg,
                            *TMC2209_S2_cfg,
                            *TMC2209_S3_cfg,
                            *TMC2209_S4_cfg,
                            *TMC2209_S5_cfg;

/*static PinsTypeDef TMC2209_S1_pins = {
	ENN: { X_EN_GPIO_Port, X_EN_Pin },
    STEP: { X_STEP_GPIO_Port, X_STEP_Pin },
    DIR: { X_DIR_GPIO_Port, X_DIR_Pin },
    DIAG: { X_DIAG1_GPIO_Port, X_DIAG1_Pin }
};*/


void phat2_motors_init() {

    // init all motors
    tmc2209_init(&TMC2209_S1, 0, 0, TMC2209_S1_cfg, tmc2209_defaultRegisterResetState);
    
    tmc2209_reset(&TMC2209_S1);

    /*tmc2209_init(&TMC2209_S2, 0, 1, TMC2209_S2_cfg, tmc2209_defaultRegisterResetState);
    tmc2209_init(&TMC2209_S3, 0, 2, TMC2209_S3_cfg, tmc2209_defaultRegisterResetState);

    tmc2209_init(&TMC2209_S4, 1, 0, TMC2209_S4_cfg, tmc2209_defaultRegisterResetState);
    tmc2209_init(&TMC2209_S5, 1, 1, TMC2209_S5_cfg, tmc2209_defaultRegisterResetState);
    */
}



// Write [writeLength] bytes from the [data] array.
// If [readLength] is greater than zero, read [readLength] bytes from the [data] array.
void tmc2209_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength) {

    // read write using HAL
    //HAL_UART_Transmit_DMA(&huart2, data, writeLength);
    HAL_UART_Transmit(&huart2, data, writeLength, 100);

    if(readLength>0)
        HAL_UART_Receive(&huart2, data, readLength, 100);
        //HAL_UART_Receive_DMA(&huart2, data, readLength);

}

// from datasheet pag.17 
uint8_t tmc2209_CRC8(uint8_t* data, size_t length) {
    int i,j;
    uint8_t *crc = data + (length-1); // CRC located in last byte of message
    uint8_t currentByte;
    
    *crc = 0;
    for (i=0; i<(length-1); i++) { // Execute for all bytes of a message
        currentByte = data[i]; // Retrieve a byte to be sent from Array
        for (j=0; j<8; j++) {
            if ((*crc >> 7) ^ (currentByte&0x01)) // update CRC based result of XOR operation
                *crc = (*crc << 1) ^ 0x07;
            else
                *crc = (*crc << 1);
            currentByte = currentByte >> 1;
        } // for CRC bit
    } // for message byte

    return crc;
}

