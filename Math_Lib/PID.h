//
// Created by 12427 on 2023/9/9.
//
#ifdef __cplusplus
extern "C" {
#endif
#ifndef PID_H
#define PID_H

#include "main.h"

enum {
    LAST = 0,
    NOW = 1,
};

class PID {
public:
    // 构造函数

    float kP, kI, kD;
    float set[2], get[2], err[2];
    float pOut, iOut, dOut;
    float outPut;
    float lastOutput;
    float maxOut;
    float maxIntegral;
    uint32_t pidMode;
    PID(float kP, float kI, float kD, float maxOut, float maxIntegral);
    void DeadBand(float upper, float lower);
    // 初始化PID参数
    void Init(float kP, float kI, float kD, float maxOut, float maxIntegral);

    // 计算PID输出
    void Calc(float get, float set);

    // 清除PID积分部分
    void Clear();

private:
    // 限幅函数
    void AbsLimit(float& x, float limit);

    // PID参数和变量
};
#endif //_PID_H
#ifdef __cplusplus
}
#endif