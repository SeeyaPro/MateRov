//
// Created by seeya on 2024/5/24.
//

#include "Driver_RC.h"

void RC::RCStart() {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, RCRxBuffer, RC_INFO_LEN);
    __HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);
}

void RC::RCCommandChange(RC::RCTranslation_t *rcTranslation) {
    if( RC_DEADBAND_DOWN <= rcCommand.rudder && rcCommand.rudder <=  RC_DEADBAND_UP)
        rcTranslation->yaw = 0;
    else
        rcTranslation->yaw = (rcCommand.rudder-RC_ROCKER_MEDIAN) * RC_PWM_VALUE_TRANS/2;
    if(RC_DEADBAND_DOWN <= rcCommand.throttle && rcCommand.throttle <= RC_DEADBAND_UP)
        rcTranslation->z = 0;
    else
        rcTranslation->z = (rcCommand.throttle-RC_ROCKER_MEDIAN) * RC_PWM_VALUE_TRANS;
    if(RC_DEADBAND_DOWN <= rcCommand.ailevenom && rcCommand.ailevenom <= RC_DEADBAND_UP)
        rcTranslation->y = 0;
    else
        rcTranslation->y = (rcCommand.ailevenom-RC_ROCKER_MEDIAN) * RC_PWM_VALUE_TRANS;
    if(RC_DEADBAND_DOWN <= rcCommand.elevator && rcCommand.elevator <= RC_DEADBAND_UP)
        rcTranslation->x = 0;
    else
        rcTranslation->x = (rcCommand.elevator-RC_ROCKER_MEDIAN) * RC_PWM_VALUE_TRANS;
}

void RC::RCCommandRecive(RC::RCTranslation_t *rcTranslation)
    {
    //摇杆做了限制
        rcCommand.ailevenom = ascii_dictionary[GetRcCommandTemp(AIL_HIGH)]*16+ascii_dictionary[GetRcCommandTemp(AIL_LOW)];
        rcCommand.elevator = ascii_dictionary[GetRcCommandTemp(ELE_HIGH)]*16+ascii_dictionary[GetRcCommandTemp(ELE_LOW)];
        rcCommand.throttle = ascii_dictionary[GetRcCommandTemp(THR_HIGH)]*16+ascii_dictionary[GetRcCommandTemp(THR_LOW)];
        rcCommand.rudder = ascii_dictionary[GetRcCommandTemp(RUD_HIGH)]*16+ascii_dictionary[GetRcCommandTemp(RUD_LOW)];
        //按键值和轮值
        rcTranslation->button = ascii_dictionary[GetRcCommandTemp(BOTTON_HIGH)]*16+ascii_dictionary[GetRcCommandTemp(BOTTON_LOW)];
        rcTranslation->wheel = ascii_dictionary[RCRxBuffer[WHEEL_HIGH]]*16+ascii_dictionary[RCRxBuffer[WHEEL_LOW]];
        RCCommandChange(rcTranslation);
        RCButtonGet();
    }

void RC::RCButtonGet() {
    uint8_t SBTemp = 0;
    uint8_t SCTemp = 0;

    rcButton.SA = ((rcTranslation.button & 0x40) == 0x40);
    rcButton.SE = ((rcTranslation.button & 0x01) == 1);
    rcButton.SD = ((rcTranslation.button & 0x02) == 0x02);
    SBTemp = (rcTranslation.button & 0x10) + (rcTranslation.button & 0x04);
    SCTemp = (rcTranslation.button & 0x20) + (rcTranslation.button & 0x08);
    switch (SBTemp) {
        case 0b10000:
            rcButton.SB = BTDOWN;
            break;
        case 0b100:
            rcButton.SB = BTUP;
            break;
        case 0:
            rcButton.SB = BTMID;
            break;
    }
            switch (SCTemp) {
                case 0b100000:
                    rcButton.SC = BTDOWN;
                    break;
                case 0b1000:
                    rcButton.SC = BTUP;
                    break;
                case 0:
                    rcButton.SC = BTMID;
                    break;
            }


}
bool RC::RCisLegal(uint8_t *buf) {
    if(buf[0] == 0x66 && buf[1] == 0x66)    return true;
    return false;
}
uint8_t RC::GetRcCommandTemp(int point) {
    return RCRxBuffer[point];
}