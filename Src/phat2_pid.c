
#include "phat2_pid.h"

/* PID error */
float32_t pid_error;
/* Duty cycle for PWM */
float32_t duty = 0;
/* ARM PID Instance, float_32 format */
arm_pid_instance_f32 PID = {
    .Kp = PID_PARAM_KP,        
    .Ki = PID_PARAM_KI,
    .Kd = PID_PARAM_KD
};

PIDTypeDef T1 = {
    .instance = &PID
};

void phat2_pid_init() {
    
    /* Initialize PID system, float32_t format */
    T1.target = 300;
    arm_pid_init_f32(T1.instance, 1);

}

float32_t phat2_pid_update(PIDTypeDef *pid,float32_t value) {

    pid->error = value - pid->target;
    
    float32_t duty = arm_pid_f32(pid->instance, pid->error);
    
    if(duty > 100)      duty = 100;
    else if(duty < 0)   duty = 0;

    return duty;

}