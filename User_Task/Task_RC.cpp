//
// Created by seeya on 2024/5/24.
//
#include "main.h"
#include "cmsis_os2.h"
#include "Driver_BinarySem.h"
#include "Driver_RC.h"

RC MyRC;
void RCTaskFun(void *argument)
{
    /* USER CODE BEGIN RCTaskFun */
    osSemaphoreAcquire(RCBinarySemHandle, 0);

    /* Infinite loop */
    for(;;)

    {
        MyRC.RCStart();
        osStatus_t ret = osSemaphoreAcquire(RCBinarySemHandle, 21);
            if (ret == osOK) {
                if (MyRC.RCisLegal(MyRC.RCRxBuffer)) {
                    MyRC.RCCommandRecive(&MyRC.rcTranslation);
                }
            }
        osDelay(1);
    }
    /* USER CODE END RCTaskFun */
}
