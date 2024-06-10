//
// Created by seeya on 2024/6/3.
//
#ifdef __cplusplus
extern "C" {
#endif
#ifndef DRIVER_CONTROL_H
#define DRIVER_CONTROL_H
#include "main.h"
#include "Driver_RC.h"
#include "Driver_HI229.h"
#include "PID.h"
#include "tim.h"

class ROV {
    public:
    struct rovPID_t {
        pid_typedef pitchPid;
        pid_typedef pitchRatePid;
        pid_typedef yawPid;
        pid_typedef yawRatePid;
        pid_typedef rollPid;
        pid_typedef rollRatePid;
    } rovPid;
    struct rovMotor_t{
        uint32_t m1CCR;
        uint32_t m2CCR;
        uint32_t m3CCR;
        uint32_t m4CCR;
        uint32_t m5CCR;
        uint32_t m6CCR;
        uint32_t m7CCR;
        uint32_t m8CCR;
    } rovMotor;



    uint32_t gimbalCCR[2];

    void MotorLostProtect();    //丢失保护
    void RovInit();
/////八推进/////////
    void RovMotorSet();
    void RovAngleControl(decltype(HI229::hi229Info)* hi229Info, decltype(RC::rcTranslation)* rcInfo);
    void RovManualControl(decltype(RC::rcTranslation)* rcInfo);
/////坤械臂//////
    void ArmServoSet(decltype(RC::rcButton)* button);
    /////云台/////
    void GimbalServoSet(decltype(RC::rcTranslation)* rcInfo);
private:
    static uint32_t MotorConstrain(uint32_t motor);  //限速
};
    void ServoLimit(int16_t *servoTemp, int16_t max, int16_t mini);

#endif //DRIVER_CONTROL_H
#ifdef __cplusplus
}
#endif