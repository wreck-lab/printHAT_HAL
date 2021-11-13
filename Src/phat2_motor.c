
#include "phat2_motor.h"

// Helper macro - index is always 1 here (channel 1 <-> index 0, channel 2 <-> index 1)
#define TMC2209_CRC(data, length) tmc_CRC8(data, length, 1)

// inspired by TMC-Eval
typedef struct {
	IOPinTypeDef  *ENN;
	IOPinTypeDef  *SPREAD;  // NC on phat2
	IOPinTypeDef  *STEP;
	IOPinTypeDef  *DIR;
	IOPinTypeDef  *MS1_AD0;
	IOPinTypeDef  *MS2_AD1;
	IOPinTypeDef  *DIAG;    
	IOPinTypeDef  *INDEX;   // NC on phat2
	IOPinTypeDef  *UC_PWM;  // ????
	IOPinTypeDef  *STDBY;   // wired to GND on phat2
} PinsTypeDef;

typedef struct {
	uint16_t 		pin;
	GPIO_TypeDef    *port;
} IOPinTypeDef;

//static UART_Config *TMC2209_UARTChannel;
static UART_HandleTypeDef *TMC2209_UARTChannel;


// phat2 motor drivers
static TMC2209TypeDef   TMC2209_S1, 
                        TMC2209_S2, 
                        TMC2209_S3, 
                        TMC2209_S4, 
                        TMC2209_S5;
                        
static ConfigurationTypeDef *TMC2209_S1_cfg,
                            *TMC2209_S2_cfg,
                            *TMC2209_S3_cfg,
                            *TMC2209_S4_cfg,
                            *TMC2209_S5_cfg;

static PinsTypeDef TMC2209_S1_pins = {
	ENN: { X_EN_GPIO_Port, X_EN_Pin },
    STEP: { X_STEP_GPIO_Port, X_STEP_Pin },
    DIR: { X_DIR_GPIO_Port, X_DIR_Pin },

    // TODO
    
};


void phat2_motors_init() {

    // init all motors
    tmc2209_init(&TMC2209_S1, 0, 0, TMC2209_S1_cfg, tmc2209_defaultRegisterResetState);
    tmc2209_init(&TMC2209_S2, 0, 1, TMC2209_S2_cfg, tmc2209_defaultRegisterResetState);
    tmc2209_init(&TMC2209_S3, 0, 2, TMC2209_S3_cfg, tmc2209_defaultRegisterResetState);

    tmc2209_init(&TMC2209_S4, 1, 0, TMC2209_S4_cfg, tmc2209_defaultRegisterResetState);
    tmc2209_init(&TMC2209_S5, 1, 1, TMC2209_S5_cfg, tmc2209_defaultRegisterResetState);

}



// Write [writeLength] bytes from the [data] array.
// If [readLength] is greater than zero, read [readLength] bytes from the [data] array.
void tmc2209_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength) {

    // read write using HAL
    HAL_UART_Transmit(&huart2, data, writeLength, 100);
    
    HAL_UART_Receive(&huart2, data, readLength, 100);

}

uint8_t tmc2209_CRC8(uint8_t *data, size_t length) {

}

static inline TMC2209TypeDef *motorToIC(uint8_t motor) {

	UNUSED(motor);

	return &TMC2209_S1;

}

void tmc2209_writeRegister(uint8_t motor, uint8_t address, int32_t value) {

	tmc2209_writeInt(motorToIC(motor), address, value);

}

void tmc2209_readRegister(uint8_t motor, uint8_t address, int32_t *value) {
	*value = tmc2209_readInt(motorToIC(motor), address);
}

