/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for LEDTask */
osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes = {
  .name = "LEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for HI229Task */
osThreadId_t HI229TaskHandle;
const osThreadAttr_t HI229Task_attributes = {
  .name = "HI229Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RCTask */
osThreadId_t RCTaskHandle;
const osThreadAttr_t RCTask_attributes = {
  .name = "RCTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for RovTask */
osThreadId_t RovTaskHandle;
const osThreadAttr_t RovTask_attributes = {
  .name = "RovTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for HI229BinarySem */
osSemaphoreId_t HI229BinarySemHandle;
const osSemaphoreAttr_t HI229BinarySem_attributes = {
  .name = "HI229BinarySem"
};
/* Definitions for RCBinarySem */
osSemaphoreId_t RCBinarySemHandle;
const osSemaphoreAttr_t RCBinarySem_attributes = {
  .name = "RCBinarySem"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LEDTaskFun(void *argument);
void HI229TaskFun(void *argument);
void RCTaskFun(void *argument);
void RovTaskFun(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of HI229BinarySem */
  HI229BinarySemHandle = osSemaphoreNew(1, 0, &HI229BinarySem_attributes);

  /* creation of RCBinarySem */
  RCBinarySemHandle = osSemaphoreNew(1, 0, &RCBinarySem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of LEDTask */
  LEDTaskHandle = osThreadNew(LEDTaskFun, NULL, &LEDTask_attributes);

  /* creation of HI229Task */
  HI229TaskHandle = osThreadNew(HI229TaskFun, NULL, &HI229Task_attributes);

  /* creation of RCTask */
  RCTaskHandle = osThreadNew(RCTaskFun, NULL, &RCTask_attributes);

  /* creation of RovTask */
  RovTaskHandle = osThreadNew(RovTaskFun, NULL, &RovTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_LEDTaskFun */
/**
  * @brief  Function implementing the LEDTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LEDTaskFun */
__weak void LEDTaskFun(void *argument)
{
  /* USER CODE BEGIN LEDTaskFun */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LEDTaskFun */
}

/* USER CODE BEGIN Header_HI229TaskFun */
/**
* @brief Function implementing the HI229Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_HI229TaskFun */
__weak void HI229TaskFun(void *argument)
{
  /* USER CODE BEGIN HI229TaskFun */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END HI229TaskFun */
}

/* USER CODE BEGIN Header_RCTaskFun */
/**
* @brief Function implementing the RCTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RCTaskFun */
__weak void RCTaskFun(void *argument)
{
  /* USER CODE BEGIN RCTaskFun */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END RCTaskFun */
}

/* USER CODE BEGIN Header_RovTaskFun */
/**
* @brief Function implementing the RovTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RovTaskFun */
__weak void RovTaskFun(void *argument)
{
  /* USER CODE BEGIN RovTaskFun */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END RovTaskFun */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

