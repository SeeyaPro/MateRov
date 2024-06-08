//
// Created by 12427 on 2023/9/8.
//

#include "Bsp_Usart.h"
#include "cmsis_os2.h"
#include "usart.h"
#include "Driver_BinarySem.h"


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == huart1.Instance) {
        osSemaphoreRelease(RCBinarySemHandle);

        return;
    } else if (huart->Instance == huart6.Instance) {
        osSemaphoreRelease(HI229BinarySemHandle);

        return;
    }
}