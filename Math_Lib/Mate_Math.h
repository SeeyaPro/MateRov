//
// Created by seeya on 2024/5/23.
//
#ifdef __cplusplus
extern "C" {
#endif
#ifndef MATE_MATH_H
#define MATE_MATH_H


#include "math.h"
#include "stdio.h"
#include "stdint.h"

extern uint8_t ascii_dictionary[128];

int constrain(int amt, int low, int high);
float constrainf(float amt, float low, float high);
void Ascii_ChangeFuc_Init(void);
float YAW_ErroLimit(float data,float expect_data);



#endif //MATE_MATH_H
#ifdef __cplusplus
}
#endif