
#ifndef __PHAT2_SENSOR_H
#define __PHAT2_SENSOR_H

#include <stddef.h>
#include <stdint.h>

#include <stdbool.h>

#include "stm32f4xx_hal.h" //__FPU_PRESENT=1
#include "arm_math.h"

// temperature
#define KELVIN_TO_CELSIUS -273.15
#define	TH_PULL_UP 10000
#define INLINE_RESISTOR 0
#define TEMP_SCALE 10
// adc 
#define ADC_CHANNELS 4 // channels actively used
#define ADC_RANGE 4096
// pwm
#define PWM_CHANNELS 5 // channels actively used
#define PWM_RANGE 65535

// internal temperature sensor
// pag 110, https://www.st.com/resource/en/datasheet/stm32f401cc.pdf
#define V25 0.76
#define VSENSE 3.3/4096
#define AVG_SLOPE .0025

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


extern ADC_HandleTypeDef  hadc1;
extern TIM_HandleTypeDef  htim3, htim4;
extern uint32_t           adc[ADC_CHANNELS]; 

typedef struct {
  TIM_HandleTypeDef *tim;
  uint32_t channel;
  GPIO_TypeDef *port;
  uint16_t pin;
  bool enabled;
} PWMOutTypeDef;

void phat2_io_init();

// sensors
int32_t phat2_io_th0();
int32_t phat2_io_th1();
int32_t phat2_io_th2();
uint32_t phat2_io_mcu_temp();

// loads
void phat2_io_set_pwm(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse);

void phat2_io_pwm_enable(PWMOutTypeDef *pwmout, bool value);
void phat2_io_pwm_pwr(PWMOutTypeDef *pwmout, uint16_t level);
//void phat2_io_h1_pwr(uint16_t level);
//void phat2_io_h2_pwr(uint16_t level);
//void phat2_io_f0_pwr(uint16_t level);
//void phat2_io_f1_pwr(uint16_t level);
void phat2_tim_callback(TIM_HandleTypeDef *htim);
void phat2_pwm_callback(TIM_HandleTypeDef *htim);

#endif


