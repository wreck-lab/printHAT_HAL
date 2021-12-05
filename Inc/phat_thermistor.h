#ifndef __PHAT2_THERMISTOR_H
#define __PHAT2_THERMISTOR_H

// refs:
// thermistor: https://download.lulzbot.com/retail_parts/Completed_Parts/100k_Semitech_GT2_Thermistor_KT-EL0059/GT-2-glass-thermistors.pdf
// ADC DMA : https://controllerstech.com/stm32-adc-multiple-channels/

typedef struct {
    float t1, r1;
    float t2, r2;
    float t3, r3;
	float c1, c2, c3, beta;
} ThermistorTypeDef;

static ThermistorTypeDef ATC_104GT2 = {
    .t1 = 20,   .r1 = 126800,
    .t2 = 150,  .r2 = 1360,
    .t3 = 300,  .r3 = 80.65
};

static ThermistorTypeDef EPCOS_100K_B57560G104F = {
    .t1 = 25, .r1 = 100000,
    .t2 = 150, .r2 = 1641.9,
    .t3 = 250, .r3 = 226.1
};

#endif