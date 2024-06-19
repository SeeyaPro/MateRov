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

RC myRc;
uint32_t RcCount = 11;
void RCTaskFun(void *argument)
{
    /* USER CODE BEGIN RCTaskFun */
    osSemaphoreAcquire(RCBinarySemHandle, 0);
    Ascii_ChangeFuc_Init();
    /* Infinite loop */
    for(;;)

    {
        RcCount++;
        myRc.RCStart();
        osStatus_t ret = osSemaphoreAcquire(RCBinarySemHandle, 21);
            if (ret == osOK) {
                if (myRc.RCisLegal(myRc.RCRxBuffer)) {
                    myRc.RCCommandRecive(&myRc.rcTranslation);
                    RcCount = 0;
                }
            }
        osDelay(1);
    }
    /* USER CODE END RCTaskFun */
}
#ifdef __cplusplus
}
#endif