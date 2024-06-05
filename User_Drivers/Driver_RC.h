//
// Created by seeya on 2024/5/24.
//
#ifdef __cplusplus
extern "C" {
#endif
#ifndef DRIVER_RC_H
#define DRIVER_RC_H

#include "stdint.h"
#include "Mate_Math.h"
#include "stm32f4xx_it.h"
#include "main.h"
#include "usart.h"

#define MINTHROTTLE						2250 //电机停转值
#define MAXTHROTTLE_LIMIT				2750 //限制70%正向油门最大值
#define MAXTHROTTLE_LIMIT_INV 			1750 //限制70%反向油门最大值
#define COMMANDER_MINCHECK 				2325 //正向怠速值
#define COMMANDER_MINCHECK_INV 			2175 //反向怠速值
#define COMMANDER_MINCHECK_RELATIVE 	75   //正向油门怠速值相对值
#define COMMANDER_MINCHECK_RELATIVE_INV -75  //反向油门怠速相对值
#define MATE_AUTO                            0    //自稳模式
#define MATE_MANUAL                          1    //手动模式

#define RC_INFO_LEN     24
#define RC_DEADBAND_UP      132  //摇杆上死区
#define RC_DEADBAND_DOWN    122  //摇杆下死区
#define RC_ROCKER_MEDIAN    127  //摇杆中值
#define RC_ROCKER_MAX       255  //摇杆最大值
#define RC_PWM_VALUE_TRANS  (int)((MAXTHROTTLE_LIMIT-MINTHROTTLE)/(RC_ROCKER_MAX-RC_ROCKER_MEDIAN))   //遥控器油门值转化为绝对pwm值的放大倍数


#define AIL_HIGH            2
#define AIL_LOW             3
#define ELE_HIGH            4
#define ELE_LOW             5
#define THR_HIGH            6
#define THR_LOW             7
#define RUD_HIGH            8
#define RUD_LOW             9
#define WHEEL_HIGH          10
#define WHEEL_LOW           11
#define BOTTON_HIGH		    12
#define BOTTON_LOW          13



class RC{
public:
    uint8_t RCRxBuffer[RC_INFO_LEN];
    struct RCTranslation_t
    {
        int16_t y;
        int16_t x;
        int16_t yaw;
        int16_t z;
        int16_t botton;
    };
    RCTranslation_t rcTranslation;
    struct RCCommand_t
    {
        int16_t ailevenom; //平移
        int16_t elevator;  //前进后退
        int16_t throttle;  //油门
        int16_t rudder;    //偏航
    };
    uint8_t armControl[2];
    static RCCommand_t rcCommand;

    void RCCommandRecive(RCTranslation_t *rc_Translation);
    bool RCisLegal(uint8_t *buf);
    void RCStart();

private:


    static void RCCommandChange(RCTranslation_t *rc_Translation);
    uint8_t GetRcCommandTemp(int point);
};
extern RC MyRC;
#endif //DRIVER_RC_H
#ifdef __cplusplus
}
#endif