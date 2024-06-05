//
// Created by seeya on 2024/6/3.
//

#include "Driver_LED_E.h"
#include "cmsis_os2.h"
void LEDBlink(uint32_t ms) {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
    osDelay(ms);
}

void RobLightOn()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}

void RobLightOff()
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
}
