
#include "main.h"   // gpio defiines
#include "phat2_io.h"
#include "phat_thermistor.h"

uint32_t adc[ADC_CHANNELS]; 

static ThermistorTypeDef TH0, TH1, TH2;
static ThermistorTypeDef *sensors[ADC_CHANNELS] = { &TH0, &TH1, &TH2 };

static PWMOutTypeDef H0, H1, H2, F0, F1;
static PWMOutTypeDef *loads[PWM_CHANNELS] = { &H0, &H1, &H2, &F0, &F1 };

extern uint32_t cnt, cnt2;

// private declarations
void phat2_setup_coeff(ThermistorTypeDef *th);
void phat2_setup_coeff_beta(ThermistorTypeDef *th);
void phat2_io_init_loads();
void test_io_pwm();


void phat2_io_init() {

    // USER: change this according to the sensors used 
    TH0 = EPCOS_100K_B57560G104F;
    TH1 = EPCOS_100K_B57560G104F;
    TH2 = EPCOS_100K_B57560G104F;

    phat2_setup_coeff(&TH0);
    phat2_setup_coeff(&TH1);
    phat2_setup_coeff(&TH2);

    // start adc in DMA mode (incl. calibration)
    //HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, &adc[0], 4);

    phat2_io_init_loads();

    // start pwm (init called in main and done via hal autocode)
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);
    
    test_io_pwm();
}

void phat2_io_init_loads() {
    // H
    H0.tim = &htim3;
    H0.channel = TIM_CHANNEL_1;
    H0.enabled = false;
    H0.port = H0_GPIO_Port;
    H0.pin = H0_Pin;
    H1.tim = &htim3;
    H1.channel = TIM_CHANNEL_2;
    H1.enabled = false;
    H1.port = H1_GPIO_Port;
    H1.pin = H1_Pin;
    H2.tim = &htim3;
    H2.channel = TIM_CHANNEL_3;
    H2.enabled = false;
    H2.port = H2_GPIO_Port;
    H2.pin = H2_Pin;
    // F
    F0.tim = &htim4;
    F0.channel = TIM_CHANNEL_1;
    F0.enabled = false;
    F0.port = F0_GPIO_Port;
    F0.pin = F0_Pin;
    F1.tim = &htim4;
    F1.channel = TIM_CHANNEL_2;
    F1.enabled = false;
    F1.port = F1_GPIO_Port;
    F1.pin = F1_Pin;
}

void phat2_setup_coeff(ThermistorTypeDef *th) {
    // Calculate Steinhart-Hart coefficents from temp measurements.
    // Arrange samples as 3 linear equations and solve for c1, c2, and c3.
    float inv_t1 = 1. / (th->t1 - KELVIN_TO_CELSIUS);
    float inv_t2 = 1. / (th->t2 - KELVIN_TO_CELSIUS);
    float inv_t3 = 1. / (th->t3 - KELVIN_TO_CELSIUS);
    float ln_r1 = log(th->r1);
    float ln_r2 = log(th->r2);
    float ln_r3 = log(th->r3);
    float ln3_r1 = pow(ln_r1,3);
    float ln3_r2 = pow(ln_r2,3);
    float ln3_r3 = pow(ln_r3,3);

    float inv_t12 = inv_t1 - inv_t2;
    float inv_t13 = inv_t1 - inv_t3;
    float ln_r12 = ln_r1 - ln_r2;
    float ln_r13 = ln_r1 - ln_r3;
    float ln3_r12 = ln3_r1 - ln3_r2;
    float ln3_r13 = ln3_r1 - ln3_r3;

    th->c3 = ((inv_t12 - inv_t13 * ln_r12 / ln_r13) / (ln3_r12 - ln3_r13 * ln_r12 / ln_r13));
    if(th->c3 <= 0) {
        th->beta = ln_r13 / inv_t13;
        phat2_setup_coeff_beta(th);
        return;
    }
    th->c2 = (inv_t12 - th->c3 * ln3_r12) / ln_r12;
    th->c1 = inv_t1 - th->c2 * ln_r1 - th->c3 * ln3_r1;
}

void phat2_setup_coeff_beta(ThermistorTypeDef *th) {
        // Calculate equivalent Steinhart-Hart coefficents from beta
        float inv_t1 = 1. / (th->t1 - KELVIN_TO_CELSIUS);
        float ln_r1 = log(th->r1);
        th->c3 = 0.0;
        th->c2 = 1.0 / th->beta;
        th->c1 = inv_t1 - th->c2 * ln_r1;
}

float calc_temp(uint8_t ch) {

    ThermistorTypeDef *th = sensors[ch];
    
    float adc_val = (float)adc[ch] / ADC_RANGE;
    //adc_val = max(.00001, min(.99999, adc_val));

    float r = TH_PULL_UP * adc_val / (1.0 - adc_val);
    float ln_r = log(r - INLINE_RESISTOR);
    float inv_t = th->c1 + th->c2 * ln_r + th->c3 * pow(ln_r,3);
    return 1.0 / inv_t + KELVIN_TO_CELSIUS;
    
}

int32_t phat2_io_th0() {
    return calc_temp(0) * TEMP_SCALE;
}
int32_t phat2_io_th1() {
    return calc_temp(1) * TEMP_SCALE;
}
int32_t phat2_io_th2() {
    return calc_temp(2) * TEMP_SCALE;
}
uint32_t phat2_io_mcu_temp() {
    return (((V25 - (adc[3]*VSENSE))/AVG_SLOPE) + 25) * TEMP_SCALE; 
}

// pwm loads
// phat2_io_set_pwm(htim3, TIM_CHANNEL_1, 255, i); 
void phat2_io_pwm_enable(PWMOutTypeDef *pwmout, bool value) {
    value ? 
        HAL_TIM_PWM_Start_IT(pwmout->tim, pwmout->channel) :
        HAL_TIM_PWM_Stop_IT(pwmout->tim, pwmout->channel);
    pwmout->enabled = value;
}

void phat2_io_pwm_pwr(PWMOutTypeDef *pwmout, uint16_t level) {
    switch(pwmout->channel) {
        case TIM_CHANNEL_1:  pwmout->tim->Instance->CCR1 = level; break;
        case TIM_CHANNEL_2:  pwmout->tim->Instance->CCR2 = level; break;
        case TIM_CHANNEL_3:  pwmout->tim->Instance->CCR3 = level; break;
        case TIM_CHANNEL_4:  pwmout->tim->Instance->CCR4 = level; break;
    }
    
}

// magic happens here
void phat2_pwm_callback(TIM_HandleTypeDef *htim) {
    for(uint8_t i=0; i<PWM_CHANNELS; i++) {
        if(loads[i]->tim == htim) {
            if(loads[i]->channel == TIM_CHANNEL_1 && (htim->Channel&HAL_TIM_ACTIVE_CHANNEL_1)) {
                if(loads[i]->enabled) 
                    HAL_GPIO_WritePin(loads[i]->port, loads[i]->pin, RESET);
            } else if((loads[i]->channel>>1) & htim->Channel ) {
                if(loads[i]->enabled) 
                    HAL_GPIO_WritePin(loads[i]->port, loads[i]->pin, RESET);
            }
        }
    }
}
void phat2_tim_callback(TIM_HandleTypeDef *htim) {
    for(uint8_t i=0; i<PWM_CHANNELS; i++) {
        if(loads[i]->tim == htim && loads[i]->enabled)
            HAL_GPIO_WritePin(loads[i]->port, loads[i]->pin, SET);
    }
}
// magic is over


void test_io_pwm() {
    phat2_io_pwm_enable(&H0, true);
    phat2_io_pwm_enable(&H1, true);
    phat2_io_pwm_enable(&H2, true);
    phat2_io_pwm_enable(&F0, true);
    phat2_io_pwm_enable(&F1, true);
    phat2_io_pwm_pwr(&H0, 1000);
    phat2_io_pwm_pwr(&H1, 10000);
    phat2_io_pwm_pwr(&H2, 50000);
    phat2_io_pwm_pwr(&F0, 1000);
    phat2_io_pwm_pwr(&F1, 10000);
}


