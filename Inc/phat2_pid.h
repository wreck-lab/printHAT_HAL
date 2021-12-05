#ifndef __PHAT2_PID_H
#define __PHAT2_PID_H

#include "stm32f4xx_hal.h"
#include "arm_math.h"

#define TEMP_CURRENT        temps[1]    /* Temperature we actually have */
#define TEMP_WANT            temps[0]    /* Temperature we want to have */
 
/* Choose PID parameters */
#define PID_PARAM_KP        100            /* Proporcional */
#define PID_PARAM_KI        0.025        /* Integral */
#define PID_PARAM_KD        20            /* Derivative */


typedef struct {
    arm_pid_instance_f32 *instance;
	float error;
    float target;    
} PIDTypeDef;


#endif