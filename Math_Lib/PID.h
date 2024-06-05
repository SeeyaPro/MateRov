//
// Created by 12427 on 2023/9/9.
//

#ifndef _PID_H
#define _PID_H

#include "main.h"

enum {
    LAST = 0,
    NOW = 1,
};


typedef struct {

    float kp, ki, kd;
    float set[2], get[2], err[2];

    float p_out, i_out, d_out;
    float out_put_u;
    float out_put;
    float last_output;

    float max_out_put;
    float max_intergral;

    uint32_t pid_mode;

} pid_typedef;


void pid_init(pid_typedef *pid, float kp, float ki, float kd, float max_out, float max_intergral);

void pid_clear(pid_typedef *pid);

void pid_calc(pid_typedef *pid, float get, float set);

#endif //_PID_H
