#ifndef __SGP30_H
#define __SGP30_H

#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SGP30_I2C_ADDRESS  (0x58 << 1)

// 保留为 const 指针数组定义，不变
static const uint8_t SGP30_CMD_INIT_AIR_QUALITY[]    = { 0x20, 0x03 };
static const uint8_t SGP30_CMD_MEASURE_AIR_QUALITY[] = { 0x20, 0x08 };
static const uint8_t SGP30_CMD_GET_BASELINE[]        = { 0x20, 0x15 };
static const uint8_t SGP30_CMD_SET_BASELINE[]        = { 0x20, 0x1E };
static const uint8_t SGP30_CMD_SET_HUMIDITY[]        = { 0x20, 0x61 };
static const uint8_t SGP30_CMD_GET_FEATURE_SET[]     = { 0x20, 0x2F };
static const uint8_t SGP30_CMD_MEASURE_TEST[]        = { 0x20, 0x32 };
static const uint8_t SGP30_CMD_GET_SERIAL_ID[]       = { 0x36, 0x82 };

typedef struct {
    I2C_HandleTypeDef *i2c;
    uint16_t CO2;
    uint16_t TVOC;
} SGP30_t;

void SGP30_Init(SGP30_t *sgp, I2C_HandleTypeDef *hi2c);
uint8_t SGP30_ReadData(SGP30_t *sgp);
void SGP30_SendData_UART(SGP30_t *sgp, UART_HandleTypeDef *huart);

void SGP30_OLED_ShowData_UART(SGP30_t *sgp, UART_HandleTypeDef *huart);
#ifdef __cplusplus
}
#endif

#endif  // __SGP30_H
