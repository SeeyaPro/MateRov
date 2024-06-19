//
// Created by seeya on 2024/5/24.
//
#ifdef __cplusplus
extern "C" {
#endif
#include "cmsis_os2.h"
#include "Bsp_Tim.h"
#include "Driver_Control.h"
#include "Driver_LED_E.h"
//todo 关键加入陀螺仪丢失之后自动转手动 遥控器丢失直接保护开启双闪进行重连 功率环试着写一下
ROV myRov(8,0,0,350,0,360,
          13,0,0,350,0,360,
          13,0,0,350,0,180);
//500 中间
//-500 最下
//2000 950 最下



void RovTaskFun(void *argument)
{
    /* USER CODE BEGIN RovTaskFun */
    BspTimPwmInit();
    //myRov.RovInit();

    ///等待一下别的任务///
    osDelay(10);
    myRov.RovAngleInit();
    /* Infinite loop */
    for(;;)

    {
        //myRov.RovManualControl(&myRc.rcTranslation);
        if (HI229Count <= 10) myRov.RovAngleControl(&myHI229.hi229Info, &myRc.rcTranslation);
        else myRov.RovManualControl(&myRc.rcTranslation);
        if (RcCount <= 10) {
            myRov.ArmServoSet(&myRc.rcButton, &myRc.rcTranslation);
            myRov.GimbalServoSet(&myRc.rcButton);
            myRov.RovMotorSet(&myRc.rcButton);
            LedCmd();
        }

            osDelay(1);
    }
    /* USER CODE END RovTaskFun */
}
#ifdef __cplusplus
}
#endif