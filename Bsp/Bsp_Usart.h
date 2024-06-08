//
// Created by 12427 on 2023/9/8.
//

#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "main.h"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif //_BSP_USART_H
