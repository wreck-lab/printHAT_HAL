
#include "phat2_motor.h"
#include "string.h"

// Helper macro - index is always 1 here (channel 1 <-> index 0, channel 2 <-> index 1)
#define TMC2209_CRC(data, length) tmc_CRC8(data, length, 1)



//static UART_Config *TMC2209_UARTChannel;
static UART_HandleTypeDef *TMC2209_UARTChannel;

// phat2 motor drivers
TMC2209TypeDef 	TMC2209_S1, 
                        TMC2209_S2, 
                        TMC2209_S3, 
                        TMC2209_S4, 
                        TMC2209_S5;

static ConfigurationTypeDef *TMC2209_S1_cfg,
                            *TMC2209_S2_cfg,
                            *TMC2209_S3_cfg,
                            *TMC2209_S4_cfg,
                            *TMC2209_S5_cfg;

/*static PinsTypeDef TMC2209_S1_pin = {
	ENN: { X_EN_GPIO_Port, pin: X_EN_Pin },
    STEP: { X_STEP_GPIO_Port, X_STEP_Pin },
    DIR: { X_DIR_GPIO_Port, X_DIR_Pin },
    DIAG: { X_DIAG1_GPIO_Port, X_DIAG1_Pin }
};*/


void phat2_motors_enable(bool enn) {
    HAL_GPIO_WritePin(X_EN_GPIO_Port, X_EN_Pin, enn);
 //   HAL_GPIO_WritePin(Y_EN_GPIO_Port, Y_EN_Pin, enn);
    HAL_GPIO_WritePin(Z_EN_GPIO_Port, Z_EN_Pin, enn);
}

void phat2_motors_init() {

    // init CRC
    tmc_fillCRC8Table(0x07, true, 1);

    // init all motors (both UART channels) 
    tmc2209_init(&TMC2209_S1, 0, 0, TMC2209_S1_cfg, &tmc2209_defaultRegisterResetState[0]);
    tmc2209_init(&TMC2209_S2, 0, 1, TMC2209_S2_cfg, &tmc2209_defaultRegisterResetState[0]);
    tmc2209_init(&TMC2209_S3, 0, 2, TMC2209_S3_cfg, &tmc2209_defaultRegisterResetState[0]);
    tmc2209_init(&TMC2209_S4, 1, 0, TMC2209_S4_cfg, &tmc2209_defaultRegisterResetState[0]);
    tmc2209_init(&TMC2209_S5, 1, 1, TMC2209_S5_cfg, &tmc2209_defaultRegisterResetState[0]);

    tmc2209_reset(&TMC2209_S1);
    tmc2209_reset(&TMC2209_S2);
    tmc2209_reset(&TMC2209_S3);
    tmc2209_reset(&TMC2209_S4);
    tmc2209_reset(&TMC2209_S5);

    // enable uart on TMC
    tmc2209_writeInt(&TMC2209_S1, TMC2209_GCONF, 0x000000C0);
    tmc2209_writeInt(&TMC2209_S2, TMC2209_GCONF, 0x000000C0);
    tmc2209_writeInt(&TMC2209_S3, TMC2209_GCONF, 0x000000C0);
    tmc2209_writeInt(&TMC2209_S4, TMC2209_GCONF, 0x000000C0);
    tmc2209_writeInt(&TMC2209_S5, TMC2209_GCONF, 0x000000C0);
    
    // set current
    //TMC2209_FIELD_UPDATE(&TMC2209_S1, TMC2209_IHOLD_IRUN, TMC2209_IHOLD_MASK, TMC2209_IHOLD_SHIFT, 1);
    //HAL_Delay(200);
    TMC2209_FIELD_UPDATE(&TMC2209_S1, TMC2209_IHOLD_IRUN, TMC2209_IRUN_MASK, TMC2209_IRUN_SHIFT, 1);
    HAL_Delay(200);
    tmc2209_writeInt(&TMC2209_S1, TMC2209_VACTUAL, 50000);
    HAL_Delay(200);

    TMC2209_FIELD_UPDATE(&TMC2209_S2, TMC2209_IHOLD_IRUN, TMC2209_IRUN_MASK, TMC2209_IRUN_SHIFT, 1);
    HAL_Delay(200);
    tmc2209_writeInt(&TMC2209_S2, TMC2209_VACTUAL, 50000);
    HAL_Delay(200);

}

void tmc2209_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength) {

    // TODO: add selection of uart based on ....channel (i.e. which UART)

    // working ONLY at 9600bit/s (and with timeout long on RCV to allow all the data to come in
    HAL_UART_Transmit(&huart2, data, writeLength, 100);
    HAL_Delay(5);
    if(readLength>0) {
        HAL_UART_Receive(&huart2, data, readLength, 100);
        HAL_Delay(10);
    }

}

uint8_t tmc2209_CRC8(uint8_t* data, size_t length) {

    // TODO: consider using STM32 hardware CRC
    return tmc_CRC8(data, length, 1);

}

static uint32_t rotate(uint8_t motor, int32_t velocity) {

	StepDir_rotate(motor, velocity);
	return TMC_ERROR_NONE;
}
