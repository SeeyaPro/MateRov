//
// Created by seeya on 2024/5/21.
//

#include "Driver_HI229.h"
#include "usart.h"

void HI229::Hi229Start() {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart6, hi229RxBuffer, GYR_INFO_LEN);
    __HAL_DMA_DISABLE_IT(huart6.hdmarx, DMA_IT_HT);
}
/**
 * crc校验
 */
void HI229::Crc16Check(uint16_t *currectCrc, const uint8_t *src, uint32_t lengthInBytes) {
    uint32_t crc = *currectCrc;
    uint32_t j;
    for (j = 0; j < lengthInBytes; ++j) {
        uint32_t i;
        uint32_t byte = src[j];
        crc ^= byte << 8;
        for (i = 0; i < 8; ++i) {
            uint32_t temp = crc << 1;
            if (crc & 0x8000) {
                temp ^= 0x1021;
            }
            crc = temp;
        }
    }
    *currectCrc = crc;
}

bool HI229::Hi229isLegal(uint8_t *buf) {
    uint16_t payload_len;
    uint16_t crc = 0;
    uint16_t temp = (buf[5] << 8) + buf[4];
    payload_len = buf[2] + (buf[3] << 8);
    /* calulate 5A A5 and LEN filed crc */
    Crc16Check(&crc, buf, 4);
    /* calulate payload crc */
    Crc16Check(&crc, buf + 6, payload_len);
    if (crc != temp)
        return false;
    else
        return true;
}



void HI229::Hi229ModeSet(struct __UART_HandleTypeDef *huart, const char *mode) {
    for (int j = 0; j < 3; j++) {
        HAL_UART_Transmit(huart, (uint8_t *)mode, strlen(mode), 10);
    }
}

void HI229::Hi229DirSet(struct __UART_HandleTypeDef *huart, const char *dir) {
    for (int j = 0; j < 3; j++) {
        HAL_UART_Transmit(huart, (uint8_t *)dir, strlen(dir), 10);
    }
}

/**
 * AT指令设置陀螺仪数据包模式和坐标系
 */
void HI229::Hi229Init() {
    Hi229ModeSet(&huart6, mode_cmd_mode);
    Hi229ModeSet(&huart6, mode_cmd_odr);
    Hi229ModeSet(&huart6, mode_cmd_90);



    //Hi229DirSet(&huart6, dir_cmd_00);
}



void HI229::Hi229Update(uint8_t *buf, HI229::hi229Temp_t *hi229Struct_temp, HI229::hi229Info_t *hi229Struct) {
    memcpy(hi229Struct_temp, &buf[6], sizeof(hi229Temp_t));

    hi229Struct->ID[0] = hi229Struct_temp->ID[0];
    hi229Struct->ID[1] = hi229Struct_temp->ID[1];
    hi229Struct->Acc.x = hi229Struct_temp->Acc[0];
    hi229Struct->Acc.y = hi229Struct_temp->Acc[1];
    hi229Struct->Acc.z = hi229Struct_temp->Acc[2];

    hi229Struct->Agu.x = hi229Struct_temp->Agu[0];
    hi229Struct->Agu.y = hi229Struct_temp->Agu[1];
    hi229Struct->Agu.z = hi229Struct_temp->Agu[2];

    hi229Struct->Evl.pitch = hi229Struct_temp->Evl[1] / 100;
    hi229Struct->Evl.yaw = hi229Struct_temp->Evl[2] / 10;
    hi229Struct->Evl.roll = hi229Struct_temp->Evl[0] / 100;


}
