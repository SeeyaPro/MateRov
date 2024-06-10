//
// Created by seeya on 2024/5/21.
//
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#include "cmsis_os2.h"
#include "Driver_BinarySem.h"
#include "Driver_HI229.h"
#include "gpio.h"
#include "gpio.h"
HI229 myHI229;

void HI229TaskFun(void *argument)
{
    /* USER CODE BEGIN HI229TaskFun */
    osSemaphoreAcquire(HI229BinarySemHandle, 0);
//    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
//    myHI229.Hi229Init();


    /* Infinite loop */
    for(;;)
    {
        myHI229.Hi229Start();
        osStatus_t ret = osSemaphoreAcquire(HI229BinarySemHandle, 21);
        if (ret == osOK) {
            if (myHI229.Hi229isLegal(myHI229.hi229RxBuffer)) {
                myHI229.Hi229Update(myHI229.hi229RxBuffer, &myHI229.hi229Temp, &myHI229.hi229Info);
            }
        }
        osDelay(1);
    }
    /* USER CODE END HI229TaskFun */
}
#ifdef __cplusplus
}
#endif