//
// Created by seeya on 2024/6/3.
//

#include "Driver_Control.h"
////////////rov电机部分 ps：直接copy的未修改////////////
uint32_t ROV::MotorConstrain(uint32_t rovMotor) {
    if(rovMotor > MAXTHROTTLE_LIMIT) return MAXTHROTTLE_LIMIT;
    if(rovMotor < MAXTHROTTLE_LIMIT_INV) return MAXTHROTTLE_LIMIT_INV;
    else return rovMotor;
}

void ROV::MotorLostProtect() {
    htim12.Instance->CCR1 = MINTHROTTLE;
    htim12.Instance->CCR2 = MINTHROTTLE;

    htim3.Instance->CCR4 = MINTHROTTLE;
    htim3.Instance->CCR3= MINTHROTTLE;


    htim3.Instance->CCR2= MINTHROTTLE;
    htim3.Instance->CCR1= MINTHROTTLE;

    htim2.Instance->CCR3= MINTHROTTLE;
    htim2.Instance->CCR4= MINTHROTTLE;
}
void ROV::RovInit()  {
    pid_init(&rovPid.pitchPid, 0,0,0,0,0);
    pid_init(&rovPid.pitchRatePid, 0,0,0,0,0);
    pid_init(&rovPid.yawPid, 0,0,0,0,0);
    pid_init(&rovPid.yawRatePid, 0,0,0,0,0);
    pid_init(&rovPid.rollPid, 0,0,0,0,0);
    pid_init(&rovPid.rollRatePid, 0,0,0,0,0);
}

void ROV::RovMotorSet() {
    htim12.Instance->CCR1 = rovMotor.m6CCR;
    htim12.Instance->CCR2 = rovMotor.m5CCR;

    htim3.Instance->CCR4 = rovMotor.m7CCR;
    htim3.Instance->CCR3= rovMotor.m8CCR;

    htim3.Instance->CCR2= rovMotor.m1CCR;
    htim3.Instance->CCR1= rovMotor.m2CCR;

    htim2.Instance->CCR3= rovMotor.m4CCR;
    htim2.Instance->CCR4= rovMotor.m3CCR;
}

void ServoLimit(int16_t *servoTemp, int16_t max, int16_t mini){
    *servoTemp = *servoTemp >= max ? max : *servoTemp;
    *servoTemp = *servoTemp <= mini ? mini : *servoTemp;
}
int16_t roll = 0;
int16_t pitch1 = 0;
int16_t pitch2 = 0;

void ROV::ArmServoSet(decltype(RC::rcButton) *button) {
    static int16_t rollTemp = 0;
    static int16_t pitchTemp = 0;
    static int16_t crawTemp = 0;


    if(button->SE == 1){

        switch (button->SB) {
            case RC::BTMID:
                break;
            case RC::BTUP:
                rollTemp += 1;
                break;
            case RC::BTDOWN:
                rollTemp -= 1;
                break;
        }
    }
    ServoLimit(&rollTemp ,1000, -1000);
    switch (button->SC) {
        case RC::BTMID:
            break;
        case RC::BTUP:
            pitchTemp += 1;
            break;
        case RC::BTDOWN:
            pitchTemp -= 1;
            break;
    }
    //pitch小限幅
    ServoLimit(&pitchTemp ,1000, 0);
    //roll
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1500 - rollTemp);
    roll = 1500 - rollTemp;
    //pitch
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 2000 - pitchTemp);
    pitch1 = 2000 - pitchTemp;

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 950  + pitchTemp);
    pitch2 = 950 + pitchTemp;

//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 950  + );


}
void ROV::GimbalServoSet(decltype(RC::rcTranslation) *rcInfo) {}


void ROV::RovManualControl(decltype(RC::rcTranslation)* rcInfo) {
    rovMotor.m1CCR = rcInfo->z + MINTHROTTLE;
    rovMotor.m2CCR = rcInfo->z + MINTHROTTLE;
    rovMotor.m3CCR = rcInfo->z + MINTHROTTLE;
    rovMotor.m4CCR = rcInfo->z + MINTHROTTLE;
    rovMotor.m5CCR = -rcInfo->x - rcInfo->y - rcInfo->yaw + MINTHROTTLE ;
    rovMotor.m6CCR = rcInfo->x - rcInfo->y +  rcInfo->yaw + MINTHROTTLE;
    rovMotor.m7CCR = rcInfo->x + rcInfo->y - rcInfo->yaw + MINTHROTTLE;
    rovMotor.m8CCR = -rcInfo->x + rcInfo->y + rcInfo->yaw + MINTHROTTLE;

    //1-8号电机限速
    rovMotor.m1CCR = MotorConstrain(rovMotor.m1CCR);
    rovMotor.m2CCR= MotorConstrain(rovMotor.m2CCR);
    rovMotor.m3CCR = MotorConstrain(rovMotor.m3CCR);
    rovMotor.m4CCR = MotorConstrain(rovMotor.m4CCR);
    rovMotor.m5CCR = MotorConstrain(rovMotor.m5CCR);
    rovMotor.m6CCR = MotorConstrain(rovMotor.m6CCR);
    rovMotor.m7CCR= MotorConstrain(rovMotor.m7CCR);
    rovMotor.m8CCR = MotorConstrain(rovMotor.m8CCR);
}
void ROV::RovAngleControl(decltype(HI229::hi229Info) *hi229Info, decltype(RC::rcTranslation) *rcInfo) {

}
