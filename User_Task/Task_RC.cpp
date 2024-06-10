//
// Created by seeya on 2024/5/24.
//
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#include "cmsis_os2.h"
#include "Driver_BinarySem.h"
#include "Driver_RC.h"

RC MyRC;
void RCTaskFun(void *argument)
{
    /* USER CODE BEGIN RCTaskFun */
    osSemaphoreAcquire(RCBinarySemHandle, 0);
    Ascii_ChangeFuc_Init();
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
#ifdef __cplusplus
}
#endif