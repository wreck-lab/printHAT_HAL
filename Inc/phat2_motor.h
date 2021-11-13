
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
