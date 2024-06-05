//
// Created by seeya on 2024/5/21.
//
#ifdef __cplusplus
extern "C" {
#endif
#ifndef DRIVER_HI229_H
#define DRIVER_HI229_H


#include "main.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "stdbool.h"
#include <string.h>
#define GYR_INFO_LEN        41
/**
 * AT指令集
 */
const char mode_cmd_91[] = "AT+SETPTL=91\r\n";
const char mode_cmd_90[] = "AT+SETPTL=90,A0,B0,C0,D0,F0\r\n";
const char mode_cmd_rst[] = "AT+RST\r\n";
const char mode_cmd_baud[] = "AT+BAUD=921600\r\n";
const char mode_cmd_mode[] = "AT+MODE=0\r\n";
const char mode_cmd_odr[] = "AT+ODR=100\r\n";
const char mode_cmd_setyaw[] = "AT+SETYAW=0\r\n";

const char dir_cmd_00[] = "AT+URFR=1,0,0,0,1,0,0,0,1\r\n";//陀螺仪坐标系
const char dir_cmd_01[] = "AT+URFR=1,0,0,0,0,1,0,-1,0\r\n";//x 90
const char dir_cmd_02[] = "AT+URFR=1,0,0,0,0,-1,0,1,0\r\n";//x -90
const char dir_cmd_03[] = "AT+URFR=1,0,0,0,-1,0,0,0,-1\r\n";//x 180
const char dir_cmd_04[] = "AT+URFR=0,0,-1,0,1,0,1,0,0\r\n";//y 90
const char dir_cmd_05[] = "AT+URFR=0,0,1,0,1,0,-1,0,0\r\n";//y -90
const char dir_cmd_06[] = "AT+URFR=-1,0,0,0,1,0,0,0,-1\r\n";//y 180
const char dir_cmd_07[] = "AT+URFR=0,1,0,-1,0,0,0,0,1\r\n";//z 90
const char dir_cmd_08[] = "AT+URFR=0,-1,0,1,0,0,0,0,1\r\n";//z -90
const char dir_cmd_09[] = "AT+URFR=-1,0,0,0,-1,0,0,0,1\r\n";//z 180

class HI229 {
public:
    uint8_t hi229RxBuffer[GYR_INFO_LEN];

    struct hi229Info_t{
        uint8_t ID[2];
        struct {
            int16_t x;
            int16_t y;
            int16_t z;
        } Acc;
        struct {
            int16_t x;
            int16_t y;
            int16_t z;
        } Agu;
        struct {
            int16_t pitch;
            int16_t roll;
            int16_t yaw;
        } Evl;
    };
    hi229Info_t hi229Info;
#pragma pack(1)
    struct  hi229Temp_t{
        uint8_t ID[2];
        uint8_t Acc_Id;
        int16_t Acc[3];
        uint8_t Agu_Id;
        int16_t Agu[3];
        uint8_t Mag_Id;
        int16_t Mag[3];
        uint8_t Evl_Id;
        int16_t Evl[3];
        uint8_t Ap_Id;
        float Ap;
    };
#pragma pack()
    hi229Temp_t hi229Temp;


    void Hi229Init();
    void Hi229Start();
    void Hi229Update(uint8_t *buf, hi229Temp_t *hi229Struct_temp, hi229Info_t *hi229Struct);
    bool Hi229isLegal(uint8_t *buf);

private:

    static void Crc16Check(uint16_t *currectCrc, const uint8_t *src, uint32_t lengthInBytes);
    static void Hi229ModeSet(struct __UART_HandleTypeDef *huart, const char *mode);
    static void Hi229DirSet(struct __UART_HandleTypeDef *huart, const char *dir);


};

#endif //DRIVER_HI229_H
#ifdef __cplusplus
}
#endif