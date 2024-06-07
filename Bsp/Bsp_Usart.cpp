//
// Created by seeya on 2024/5/21.
//

#include "Bsp_Usart.h"

#include "Driver_BinarySem.h"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == huart6.Instance) {

        osSemaphoreRelease(HI229BinarySemHandle);
        return;

    } else if(huart->Instance == huart1.Instance) {

        osSemaphoreRelease(RCBinarySemHandle);
        return;
    }
}