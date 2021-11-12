/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define E0_DIAG1_Pin GPIO_PIN_13
#define E0_DIAG1_GPIO_Port GPIOC
#define E1_DIAG1_Pin GPIO_PIN_14
#define E1_DIAG1_GPIO_Port GPIOC
#define H0_Pin GPIO_PIN_0
#define H0_GPIO_Port GPIOC
#define H1_Pin GPIO_PIN_1
#define H1_GPIO_Port GPIOC
#define H2_Pin GPIO_PIN_2
#define H2_GPIO_Port GPIOC
#define F0_Pin GPIO_PIN_3
#define F0_GPIO_Port GPIOC
#define GP2_Pin GPIO_PIN_0
#define GP2_GPIO_Port GPIOA
#define TH2_Pin GPIO_PIN_1
#define TH2_GPIO_Port GPIOA
#define UART1_TX_Pin GPIO_PIN_2
#define UART1_TX_GPIO_Port GPIOA
#define UART1_RX_Pin GPIO_PIN_3
#define UART1_RX_GPIO_Port GPIOA
#define GP4_Pin GPIO_PIN_4
#define GP4_GPIO_Port GPIOA
#define GP5_Pin GPIO_PIN_5
#define GP5_GPIO_Port GPIOA
#define GP6_Pin GPIO_PIN_6
#define GP6_GPIO_Port GPIOA
#define GP7_Pin GPIO_PIN_7
#define GP7_GPIO_Port GPIOA
#define F1_Pin GPIO_PIN_4
#define F1_GPIO_Port GPIOC
#define TH0_Pin GPIO_PIN_0
#define TH0_GPIO_Port GPIOB
#define TH1_Pin GPIO_PIN_1
#define TH1_GPIO_Port GPIOB
#define Z_STEP_Pin GPIO_PIN_10
#define Z_STEP_GPIO_Port GPIOB
#define Z_DIR_Pin GPIO_PIN_12
#define Z_DIR_GPIO_Port GPIOB
#define E1_EN_Pin GPIO_PIN_13
#define E1_EN_GPIO_Port GPIOB
#define E1_STEP_Pin GPIO_PIN_14
#define E1_STEP_GPIO_Port GPIOB
#define E1_DIR_Pin GPIO_PIN_15
#define E1_DIR_GPIO_Port GPIOB
#define UART2_TX_Pin GPIO_PIN_6
#define UART2_TX_GPIO_Port GPIOC
#define UART2_RX_Pin GPIO_PIN_7
#define UART2_RX_GPIO_Port GPIOC
#define GP0_Pin GPIO_PIN_8
#define GP0_GPIO_Port GPIOC
#define GP1_Pin GPIO_PIN_9
#define GP1_GPIO_Port GPIOC
#define GP3_Pin GPIO_PIN_8
#define GP3_GPIO_Port GPIOA
#define RPI_RX_Pin GPIO_PIN_9
#define RPI_RX_GPIO_Port GPIOA
#define RPI_TX_Pin GPIO_PIN_10
#define RPI_TX_GPIO_Port GPIOA
#define USBDM_Pin GPIO_PIN_11
#define USBDM_GPIO_Port GPIOA
#define USBDP_Pin GPIO_PIN_12
#define USBDP_GPIO_Port GPIOA
#define Y_EN_Pin GPIO_PIN_13
#define Y_EN_GPIO_Port GPIOA
#define Y_STEP_Pin GPIO_PIN_14
#define Y_STEP_GPIO_Port GPIOA
#define Y_DIR_Pin GPIO_PIN_15
#define Y_DIR_GPIO_Port GPIOA
#define X_DIAG1_Pin GPIO_PIN_10
#define X_DIAG1_GPIO_Port GPIOC
#define Y_DIAG1_Pin GPIO_PIN_11
#define Y_DIAG1_GPIO_Port GPIOC
#define Z_DIAG1_Pin GPIO_PIN_12
#define Z_DIAG1_GPIO_Port GPIOC
#define X_EN_Pin GPIO_PIN_3
#define X_EN_GPIO_Port GPIOB
#define X_STEP_Pin GPIO_PIN_4
#define X_STEP_GPIO_Port GPIOB
#define X_DIR_Pin GPIO_PIN_5
#define X_DIR_GPIO_Port GPIOB
#define E0_EN_Pin GPIO_PIN_6
#define E0_EN_GPIO_Port GPIOB
#define E0_STEP_Pin GPIO_PIN_7
#define E0_STEP_GPIO_Port GPIOB
#define E0_DIR_Pin GPIO_PIN_8
#define E0_DIR_GPIO_Port GPIOB
#define Z_EN_Pin GPIO_PIN_9
#define Z_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
