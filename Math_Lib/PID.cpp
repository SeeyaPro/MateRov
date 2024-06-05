//
// Created by 12427 on 2023/9/9.
//

#include "pid.h"

pid_typedef moto_pitch_pid_s;
pid_typedef moto_pitch_pid_p;
pid_typedef moto_shoot_pid_s;
pid_typedef moto_shoot_pid_p;
pid_typedef moto_yaw_pid_s;
pid_typedef moto_yaw_pid_p;

//初始化
void pid_init(pid_typedef *pid, float kp, float ki, float kd, float max_out, float max_intergral) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->max_out_put = max_out;
    pid->max_intergral = max_intergral;
}

//限幅
void abs_limit(float *x, float limit) {
    if (*x > limit) *x = limit;
    if (*x < -limit) *x = -limit;
}

void pid_calc(pid_typedef *pid, float get, float set) {
    pid->get[NOW] = get;
    pid->set[NOW] = set;            //set - measure
    pid->err[NOW] = set - get;
    //位置式
    pid->p_out = pid->kp * pid->err[NOW];
    pid->i_out += pid->ki * pid->err[NOW];
    pid->d_out = pid->kd * (pid->err[NOW] - pid->err[LAST]);

    abs_limit(&(pid->i_out), pid->max_intergral);        //积分限幅
    pid->out_put = pid->p_out + pid->i_out + pid->d_out;    //位置式PID
    abs_limit(&(pid->out_put), pid->max_out_put);        //输出限幅
    pid->last_output = pid->out_put; //update last time

    pid->err[LAST] = pid->err[NOW];
    pid->get[LAST] = pid->get[NOW];
    pid->set[LAST] = pid->set[NOW];
}

void pid_clear(pid_typedef *pid) {
    pid->i_out = 0;
}