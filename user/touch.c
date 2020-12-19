#include "touch.h"

XPT2046_Calibration cal_value = {0};


/**
  * 函数功能: us 级别延时，不是很精确
  * 输入参数: cnt：延时时间
  * 返 回 值: 无
  * 说    明：无
  */
static void XPT2046_DelayUS(__IO uint32_t ulCount)
{
    uint32_t i;
    for (i = 0; i < ulCount; i++)
    {
        uint8_t uc = 12; //设置值为12，大约延1微秒
        while (uc--)
            ; //延1微秒
    }
}

/**
  * 函数功能: 写命令
  * 输入参数: CHX 	0x90 	//通道Y+的选择控制字 
  *           CHY   0xd0	//通道X+的选择控制字
  * 返 回 值: 无
  * 说    明：无
  */
static void XPT2046_WriteCMD(uint8_t ucCmd)
{
    uint8_t i;

    XPT2046_MOSI_LOW();
    XPT2046_CLK_LOW();

    for (i = 0; i < 8; i++)
    {
        ((ucCmd >> (7 - i)) & 0x01) ? XPT2046_MOSI_HIGH() : XPT2046_MOSI_LOW();
        XPT2046_DelayUS(5);
        XPT2046_CLK_HIGH();
        XPT2046_DelayUS(5);
        XPT2046_CLK_LOW();
    }
}

/**
  * 函数功能: 读数据
  * 输入参数: 无
  * 返 回 值: short：读到的数据
  * 说    明：无
  */
static uint16_t XPT2046_ReadCMD(void)
{
    uint8_t i;
    uint16_t usBuf = 0, usTemp;

    XPT2046_MOSI_LOW();
    XPT2046_CLK_HIGH();
    for (i = 0; i < 12; i++)
    {
        XPT2046_CLK_LOW();
        usTemp = XPT2046_MISO_READ();
        usBuf |= usTemp << (11 - i);
        XPT2046_CLK_HIGH();
    }
    return usBuf;
}

/**
  * 函数功能: 选择一个模拟通道，启动ADC，并返回ADC采样结果
  * 输入参数: _ucCh = 0x90 表示Y通道；
  *                   0xd0 表示X通道
  * 返 回 值: 无
  * 说    明：无
  */
uint16_t XPT2046_ReadAdc(uint8_t _ucCh)
{
    XPT2046_WriteCMD(_ucCh);
    return XPT2046_ReadCMD();
}

#define SAMP_CNT 4      // 定义采集次数
#define SAMP_CNT_DIV2 2 // 采集次数/2
/**
  * 函数功能: 选择一个模拟通道，启动ADC，并返回ADC采样结果
  * 输入参数: channel ：通道选择
  *           参数值：0x90 :通道Y
  *           参数值：0xd0 :通道X
  * 返 回 值: 滤波后的12位ADC值
  * 说    明：无
  */
uint16_t XPT2046_ReadAdc_Fliter(uint8_t channel)
{
    uint8_t i, j, min;
    uint16_t temp;
    uint16_t tempXY[SAMP_CNT];

    static uint16_t adc_x = 0, adc_y = 0;

    /* 如果检查到触摸屏被按下，才进行触摸屏通道采集，否则直接退出函数 */
    /* 通过触摸屏IRQ引脚可以判断触摸屏是否被触摸，有被触摸时为低电平，否则为高电平 */
    if (XPT2046_EXTI_Read() == 0)
    {
        /* 连续采样SAMP_CNT次数的数据 */
        for (i = 0; i < SAMP_CNT; i++)
        {
            XPT2046_WriteCMD(channel);
            tempXY[i] = XPT2046_ReadCMD();
        }
        /* 降序排列 */
        for (i = 0; i < SAMP_CNT - 1; i++)
        {
            min = i;
            for (j = i + 1; j < SAMP_CNT; j++)
            {
                if (tempXY[min] > tempXY[j])
                    min = j;
            }
            temp = tempXY[i];
            tempXY[i] = tempXY[min];
            tempXY[min] = temp;
        }

        // 设定阈值
        if ((tempXY[SAMP_CNT_DIV2] - tempXY[SAMP_CNT_DIV2 - 1]) > 5)
        {
            /* 若两个中间值相差太远，则舍弃这个新数据，返回上一次的触摸数据*/
            if (channel == XPT2046_CHANNEL_Y)
                return adc_x; //x通道
            else
                return adc_y; //y通道
        }

        // 求中间值的均值
        if (channel == XPT2046_CHANNEL_Y)
        {
            adc_x = (tempXY[SAMP_CNT_DIV2] + tempXY[SAMP_CNT_DIV2 - 1]) / 2;
            //printf("x->%d \n",adc_x);
            return adc_x;
        }
        else
        {
            adc_y = (tempXY[SAMP_CNT_DIV2] + tempXY[SAMP_CNT_DIV2 - 1]) / 2;
            //printf("y->%d ",adc_y);
            return adc_y;
        }
    }
    else
    {
        return 0; //没有触摸，返回0
    }
}
