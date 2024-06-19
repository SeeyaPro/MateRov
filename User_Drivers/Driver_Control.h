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

class ImuPID : public PID{
public:
    ImuPID(float kp, float ki, float kd, float maxOut, float maxIntegral, float delta)
            : PID(kp, ki, kd, maxOut, maxIntegral), delta(delta) {}

    struct imuCount_t{
        float now;         // 当前陀螺仪的yaw角度
        float last;// 上一次陀螺仪的yaw角度
        float delta;   // 角度变化量
        float res1;        // 临时变量1
        float res2;        // 临时变量2
        float sum;     // 角度总和
    } imuCount;
    void ImuCount();


private:
    float delta;

};

class ROV {
    public:

    float yawTarget;
    float pitchTarget;
    float rollTarget;

    ROV(float yawKp, float yawKi, float yawKd, float yawMaxOut, float yawMaxIntegral, float yawDelta,
        float pitchKp, float pitchKi, float pitchKd, float pitchMaxOut, float pitchMaxIntegral, float pitchDelta,
        float rollKp, float rollKi, float rollKd, float rollMaxOut, float rollMaxIntegral, float rollDelta);

    struct rovPID_t{
        ImuPID yawPID;
        ImuPID pitchPID;
        ImuPID rollPID;
        rovPID_t(float yawKp, float yawKi, float yawKd, float yawMaxOut, float yawMaxIntegral,float yawDelta,
                 float pitchKp, float pitchKi, float pitchKd, float pitchMaxOut, float pitchMaxIntegral,float pitchDelta,
                 float rollKp, float rollKi, float rollKd, float rollMaxOut, float rollMaxIntegral, float rollDelta)
                : yawPID(yawKp, yawKi, yawKd, yawMaxOut, yawMaxIntegral, yawDelta),
                  pitchPID(pitchKp, pitchKi, pitchKd, pitchMaxOut, pitchMaxIntegral, pitchDelta),
                  rollPID(rollKp, rollKi, rollKd, rollMaxOut, rollMaxIntegral, rollDelta) {}
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
    void RovAngleInit();
    void MotorLostProtect();    //丢失保护
/////八推进/////////
    void RovMotorSet(decltype(RC::rcButton)* button);
    void RovAngleControl(decltype(HI229::hi229Info)* hi229Info, decltype(RC::rcTranslation)* rcInfo);
    void RovManualControl(decltype(RC::rcTranslation)* rcInfo);
/////坤械臂//////
    void ArmServoSet(decltype(RC::rcButton)* button, decltype(RC::rcTranslation)* rcInfo);
    /////云台/////
    void GimbalServoSet(decltype(RC::rcButton)* button);

private:
    static uint32_t MotorConstrain(uint32_t rovMotor, uint32_t max ,uint32_t mini);  //限速
    void ServoLimit(int16_t *servoTemp, int16_t max, int16_t mini);

};


#endif //DRIVER_CONTROL_H
#ifdef __cplusplus
}
#endif