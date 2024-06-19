//
// Created by 12427 on 2023/9/9.
//

#include "PID.h"

// 构造函数
PID::PID(float kp, float ki, float kd, float maxOut, float maxIntegral) {
    Init(kp, ki, kd, maxOut, maxIntegral);
}

// 初始化PID参数
void PID::Init(float kp, float ki, float kd, float maxOut, float maxIntegral) {
    this->kP = kp;
    this->kI = ki;
    this->kD = kd;
    this->maxOut = maxOut;
    this->maxIntegral = maxIntegral;
    Clear();
}

// 限幅函数
void PID::AbsLimit(float& x, float limit) {
    if (x > limit) x = limit;
    if (x < -limit) x = -limit;
}

// 计算PID输出
void PID::Calc(float get, float set) {
    this->get[NOW] = get;
    this->set[NOW] = set;
    this->err[NOW] = set - get;

    // 位置式
    this->pOut = this->kP * this->err[NOW];
    this->iOut += this->kI * this->err[NOW];
    this->dOut = this->kD * (this->err[NOW] - this->err[LAST]);

    AbsLimit(this->iOut, this->maxIntegral);   // 积分限幅
    this->outPut = this->pOut + this->iOut + this->dOut; // 位置式PID
    AbsLimit(this->outPut, this->maxOut);  // 输出限幅
    this->lastOutput = this->outPut;           // 更新上次输出

    this->err[LAST] = this->err[NOW];
    this->get[LAST] = this->get[NOW];
    this->set[LAST] = this->set[NOW];
}
void PID::DeadBand(float upper, float lower) {

}
// 清除PID积分部分
void PID::Clear() {
    this->iOut = 0;
}