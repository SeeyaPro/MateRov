//
// Created by seeya on 2024/6/3.
//

#include "Driver_Control.h"
////////////rov电机部分 ps：直接copy的未修改////////////
//rov构造函数
ROV::ROV(float yawKp, float yawKi, float yawKd, float yawMaxOut, float yawMaxIntegral, float yawDelta,
         float pitchKp, float pitchKi, float pitchKd, float pitchMaxOut, float pitchMaxIntegral, float pitchDelta,
         float rollKp, float rollKi, float rollKd, float rollMaxOut, float rollMaxIntegral, float rollDelta)
        : rovPid(yawKp, yawKi, yawKd, yawMaxOut, yawMaxIntegral, yawDelta,
                         pitchKp, pitchKi, pitchKd, pitchMaxOut, pitchMaxIntegral, pitchDelta,
                         rollKp, rollKi, rollKd, rollMaxOut, rollMaxIntegral, rollDelta) {}


uint32_t ROV::MotorConstrain(uint32_t rovMotor, uint32_t max ,uint32_t mini) {
    if(rovMotor > max) return max;
    if(rovMotor < mini) return mini;
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

void ROV::RovMotorSet(decltype(RC::rcButton)* button) {

//    switch (button->SE) {
//        case 1:
//            rovMotor.m1CCR = MotorConstrain(rovMotor.m1CCR, 3000, 1500);
//            rovMotor.m2CCR= MotorConstrain(rovMotor.m2CCR,3000, 1500);
//            rovMotor.m3CCR = MotorConstrain(rovMotor.m3CCR,3000, 1500);
//            rovMotor.m4CCR = MotorConstrain(rovMotor.m4CCR,3000, 1500);
//            //功率限制
//            rovMotor.m5CCR = MotorConstrain(rovMotor.m5CCR,2500, 2000);
//            rovMotor.m6CCR = MotorConstrain(rovMotor.m6CCR,2500, 2000);
//            rovMotor.m7CCR= MotorConstrain(rovMotor.m7CCR,2500, 2000);
//            rovMotor.m8CCR = MotorConstrain(rovMotor.m8CCR,2500, 2000);
//            return;
//        case 0:
    this->rovMotor.m1CCR = MotorConstrain(this->rovMotor.m1CCR, 2750, 1750);
    this->rovMotor.m2CCR= MotorConstrain(this->rovMotor.m2CCR,2750, 1750);
    this->rovMotor.m3CCR = MotorConstrain(this->rovMotor.m3CCR,2750, 1750);
    this->rovMotor.m4CCR = MotorConstrain(this->rovMotor.m4CCR,2750, 1750);
    this->rovMotor.m5CCR = MotorConstrain(this->rovMotor.m5CCR,2750, 1750);
    this->rovMotor.m6CCR = MotorConstrain(this->rovMotor.m6CCR,2750, 1750);
    this->rovMotor.m7CCR= MotorConstrain(this->rovMotor.m7CCR,2750, 1750);
    this->rovMotor.m8CCR = MotorConstrain(this->rovMotor.m8CCR,2750, 1750);
//    }

    //左纵
    htim12.Instance->CCR1 = rovMotor.m1CCR;
    htim12.Instance->CCR2 = rovMotor.m2CCR;
    //右纵
    htim2.Instance->CCR3= rovMotor.m4CCR;
    htim2.Instance->CCR4= rovMotor.m3CCR;
//    右横
    htim3.Instance->CCR2= rovMotor.m6CCR;//右2
    htim3.Instance->CCR1= rovMotor.m8CCR;//右1
    //左横
    //左2
    htim3.Instance->CCR4 = rovMotor.m7CCR;
    //左1
    htim3.Instance->CCR3= rovMotor.m5CCR;




}

void ROV::ServoLimit(int16_t *servoTemp, int16_t max, int16_t mini){
    *servoTemp = *servoTemp >= max ? max : *servoTemp;
    *servoTemp = *servoTemp <= mini ? mini : *servoTemp;
}


void ROV::ArmServoSet(decltype(RC::rcButton) *button, decltype(RC::rcTranslation)* rcInfo) {
    static int16_t rollTemp = 0;
    static int16_t pitchTemp = 0;
    static int16_t crawTemp = 0;
    if (button->SE) {
        switch (button->SB) {
            case RC::BTMID:
                if(rollTemp > 0) rollTemp-=4;
                if(rollTemp < 0) rollTemp+=4;
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
    ServoLimit(&pitchTemp ,1020, -20);
    //roll
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1500 - rollTemp);
    //pitch
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 2020 - pitchTemp);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 930  + pitchTemp);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500  + (rcInfo->wheel * 7) );


}
void ROV::GimbalServoSet(decltype(RC::rcButton)* button) {
    if (button->SD){
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 600);

    } else  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 800);


}


void ROV::RovManualControl(decltype(RC::rcTranslation)* rcInfo) {
    this->rovMotor.m1CCR = rcInfo->z + MINTHROTTLE; //左1
    this->rovMotor.m2CCR = -rcInfo->z + MINTHROTTLE;//左2
    this->rovMotor.m3CCR = rcInfo->z + MINTHROTTLE;//右1
    this->rovMotor.m4CCR = -rcInfo->z + MINTHROTTLE;//右2

    this->rovMotor.m8CCR = rcInfo->x - rcInfo->y - rcInfo->yaw + MINTHROTTLE ;//右1
    this->rovMotor.m7CCR = rcInfo->x - rcInfo->y +  rcInfo->yaw + MINTHROTTLE;//左2
    this->rovMotor.m5CCR = rcInfo->x + rcInfo->y + rcInfo->yaw + MINTHROTTLE;//左1
    this->rovMotor.m6CCR = rcInfo->x + rcInfo->y - rcInfo->yaw + MINTHROTTLE;//右2
}
void ROV::RovAngleInit() {
    this->pitchTarget = 8;
    this->rollTarget = myHI229.hi229Info.Evl.roll;
    this->yawTarget = myHI229.hi229Info.Evl.yaw;
}

void ROV::RovAngleControl(decltype(HI229::hi229Info) *hi229Info, decltype(RC::rcTranslation) *rcInfo) {
    yawTarget = rcInfo->yaw == 0 ? yawTarget : rovPid.yawPID.imuCount.sum;

//    if (rcInfo->z == 0) rovPid.pitchPID.iOut = 0;
//    if (rcInfo->x == 0) rovPid.rollPID.iOut = 0;
    this->rovPid.yawPID.imuCount.now = hi229Info->Evl.yaw;
    this->rovPid.pitchPID.imuCount.now = hi229Info->Evl.pitch;
    this->rovPid.rollPID.imuCount.now = hi229Info->Evl.roll;

    rovPid.yawPID.ImuCount();
    rovPid.pitchPID.ImuCount();
    rovPid.rollPID.ImuCount();

    rovPid.yawPID.Calc(rovPid.yawPID.imuCount.sum, yawTarget);
    rovPid.pitchPID.Calc(rovPid.pitchPID.imuCount.sum, pitchTarget);
    rovPid.rollPID.Calc(rovPid.rollPID.imuCount.sum, rollTarget);


    rovMotor.m1CCR = rcInfo->z + rovPid.pitchPID.outPut + rovPid.rollPID.outPut + MINTHROTTLE; //左1
    rovMotor.m2CCR = -rcInfo->z - rovPid.pitchPID.outPut - rovPid.rollPID.outPut + MINTHROTTLE;//左2
    rovMotor.m3CCR = rcInfo->z + rovPid.pitchPID.outPut - rovPid.rollPID.outPut + MINTHROTTLE;//右1
    rovMotor.m4CCR = -rcInfo->z - rovPid.pitchPID.outPut + rovPid.rollPID.outPut + MINTHROTTLE;//右2

    this->rovMotor.m8CCR = rcInfo->x - rcInfo->y  - rcInfo->yaw + rovPid.yawPID.outPut + MINTHROTTLE ;//右1
    this->rovMotor.m7CCR = rcInfo->x - rcInfo->y + rcInfo->yaw - rovPid.yawPID.outPut + MINTHROTTLE;//左2
    this->rovMotor.m5CCR = rcInfo->x + rcInfo->y  + rcInfo->yaw - rovPid.yawPID.outPut + MINTHROTTLE;//左1
    this->rovMotor.m6CCR = rcInfo->x + rcInfo->y - rcInfo->yaw + rovPid.yawPID.outPut + MINTHROTTLE;//右2


}
/////////////////////////////////////////
void ImuPID::ImuCount() {
  imuCount.delta = imuCount.now - imuCount.last;
  if(imuCount.delta > 0) {
      imuCount.res1 = imuCount.delta - delta;
      imuCount.res2 = imuCount.delta;
  }else{
      imuCount.res1 = imuCount.delta + delta;
      imuCount.res2 = imuCount.delta;

  }
    if (fabsf(imuCount.res1) > fabsf(imuCount.res2)){
        imuCount.sum += imuCount.res2;

    }else{
        imuCount.sum += imuCount.res1;
    }
    imuCount.last = imuCount.now;

}