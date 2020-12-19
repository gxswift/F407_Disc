#ifndef _TOUCH_H
#define _TOUCH_H

#include "stm32f4xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
typedef struct
{
    int32_t cal_flag;
    int32_t lcd_x[5];
    int32_t lcd_y[5];
    int32_t touch_x[5];
    int32_t touch_y[5];
    int32_t adjust[7];
} XPT2046_Calibration;



//#define TCS  		PCout(13)  	
#define XPT2046_CS_HIGT() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)
#define XPT2046_CS_LOW() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
//#define TCLK 		PBout(0)  	
#define XPT2046_CLK_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
#define XPT2046_CLK_LOW() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)
//#define TDIN 		PFout(11)  
#define XPT2046_MOSI_HIGH() HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET)
#define XPT2046_MOSI_LOW() HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET)
//#define DOUT 		PBin(2)   
#define XPT2046_MISO_READ() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)
//#define PEN  		PBin(1) 
#define XPT2046_EXTI_Read() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)
/******************************* XPT2046 触摸屏参数定义 ***************************/
#define XPT2046_CHANNEL_X 0x90 //驱动YN YP，测量X+
#define XPT2046_CHANNEL_Y 0xd0 //驱动XN XP，测量Y+

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void Touch_Init_GPIO(void);
uint16_t XPT2046_ReadAdc_Fliter(uint8_t channel);

#endif
