
#ifndef __PHAT2_MOTOR_H
#define __PHAT2_MOTOR_H

#include <stddef.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"

#include "usart.h"

#include "tmc/ic/TMC2209/TMC2209.h"

// uart config
#define BUFFER_SIZE         32
#define INTR_PRI            6
#define UART_TIMEOUT_VALUE  10
#define WRITE_READ_DELAY    10

static volatile uint8_t
	rxBuffer[BUFFER_SIZE],
	txBuffer[BUFFER_SIZE];

typedef struct {
	GPIO_TypeDef    *port;
	uint16_t 		pin;
} IOPinTypeDef;

// inspired by TMC-Eval
typedef struct {
	IOPinTypeDef  *ENN;
	//IOPinTypeDef  *SPREAD;  // NC on phat2
	IOPinTypeDef  *STEP;
	IOPinTypeDef  *DIR;
	//IOPinTypeDef  *MS1_AD0;
	//IOPinTypeDef  *MS2_AD1;
	IOPinTypeDef  *DIAG;    
	//IOPinTypeDef  *INDEX;   // NC on phat2
	//IOPinTypeDef  *UC_PWM;  // ????
	//IOPinTypeDef  *STDBY;   // wired to GND on phat2
} PinsTypeDef;

// phat2 motor drivers
static TMC2209TypeDef   TMC2209_S1, 
                        TMC2209_S2, 
                        TMC2209_S3, 
                        TMC2209_S4, 
                        TMC2209_S5;

void phat2_motors_init();
void phat2_motors_enable(bool enn);

#endif