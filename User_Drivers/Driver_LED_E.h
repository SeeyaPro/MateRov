//
// Created by seeya on 2024/6/3.
//
#ifdef __cplusplus
extern "C" {
#endif
#ifndef DRIVER_LED_E_H
#define DRIVER_LED_E_H
#include "main.h"
void LEDBlink(uint32_t ms);
void RobLightOn();
void RobLightOff();
void LedCmd();

#endif //DRIVER_LED_E_H
#ifdef __cplusplus
}
#endif