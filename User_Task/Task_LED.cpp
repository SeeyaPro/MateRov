//
// Created by seeya on 2024/5/21.
//
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#include "cmsis_os2.h"
#include "Driver_LED_E.h"
void LEDTaskFun(void *argument)
{
    /* USER CODE BEGIN LEDTaskFun */
    /* Infinite loop */
    for(;;)
    {
        LEDBlink(200);
        osDelay(1);
    }
    /* USER CODE END LEDTaskFun */
}
#ifdef __cplusplus
}
#endif