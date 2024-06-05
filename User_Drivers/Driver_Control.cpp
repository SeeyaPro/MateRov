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


void ROV::ArmServoSet(decltype(RC::rcTranslation) *rcInfo) {}
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
