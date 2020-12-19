#include "touch.h"

XPT2046_Calibration cal_value = {0};


/**
  * ��������: us ������ʱ�����Ǻܾ�ȷ
  * �������: cnt����ʱʱ��
  * �� �� ֵ: ��
  * ˵    ������
  */
static void XPT2046_DelayUS(__IO uint32_t ulCount)
{
    uint32_t i;
    for (i = 0; i < ulCount; i++)
    {
        uint8_t uc = 12; //����ֵΪ12����Լ��1΢��
        while (uc--)
            ; //��1΢��
    }
}

/**
  * ��������: д����
  * �������: CHX 	0x90 	//ͨ��Y+��ѡ������� 
  *           CHY   0xd0	//ͨ��X+��ѡ�������
  * �� �� ֵ: ��
  * ˵    ������
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
  * ��������: ������
  * �������: ��
  * �� �� ֵ: short������������
  * ˵    ������
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
  * ��������: ѡ��һ��ģ��ͨ��������ADC��������ADC�������
  * �������: _ucCh = 0x90 ��ʾYͨ����
  *                   0xd0 ��ʾXͨ��
  * �� �� ֵ: ��
  * ˵    ������
  */
uint16_t XPT2046_ReadAdc(uint8_t _ucCh)
{
    XPT2046_WriteCMD(_ucCh);
    return XPT2046_ReadCMD();
}

#define SAMP_CNT 4      // ����ɼ�����
#define SAMP_CNT_DIV2 2 // �ɼ�����/2
/**
  * ��������: ѡ��һ��ģ��ͨ��������ADC��������ADC�������
  * �������: channel ��ͨ��ѡ��
  *           ����ֵ��0x90 :ͨ��Y
  *           ����ֵ��0xd0 :ͨ��X
  * �� �� ֵ: �˲����12λADCֵ
  * ˵    ������
  */
uint16_t XPT2046_ReadAdc_Fliter(uint8_t channel)
{
    uint8_t i, j, min;
    uint16_t temp;
    uint16_t tempXY[SAMP_CNT];

    static uint16_t adc_x = 0, adc_y = 0;

    /* �����鵽�����������£��Ž��д�����ͨ���ɼ�������ֱ���˳����� */
    /* ͨ��������IRQ���ſ����жϴ������Ƿ񱻴������б�����ʱΪ�͵�ƽ������Ϊ�ߵ�ƽ */
    if (XPT2046_EXTI_Read() == 0)
    {
        /* ��������SAMP_CNT���������� */
        for (i = 0; i < SAMP_CNT; i++)
        {
            XPT2046_WriteCMD(channel);
            tempXY[i] = XPT2046_ReadCMD();
        }
        /* �������� */
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

        // �趨��ֵ
        if ((tempXY[SAMP_CNT_DIV2] - tempXY[SAMP_CNT_DIV2 - 1]) > 5)
        {
            /* �������м�ֵ���̫Զ����������������ݣ�������һ�εĴ�������*/
            if (channel == XPT2046_CHANNEL_Y)
                return adc_x; //xͨ��
            else
                return adc_y; //yͨ��
        }

        // ���м�ֵ�ľ�ֵ
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
        return 0; //û�д���������0
    }
}
